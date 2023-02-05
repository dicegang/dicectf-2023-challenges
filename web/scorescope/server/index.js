import crypto from 'crypto'
import net from 'net'
import readline from 'readline'

import express from 'express'

const PORT = process.env.PORT ?? 3000

const app = express()

app.use(express.static('public'))

const sessions = new Map()

app.post('/api/submit', async (req, res) => {
    const body = { data: [], size: 0 }
    req.on('data', (chunk) => {
        if (body.size > 1e6) {
            res.json({
                success: false,
                error: 'too big',
            })
            return req.socket.destroy()
        }

        body.data.push(chunk)
        body.size += chunk.length
    })
    await new Promise((r) => req.on('end', r))

    const session = crypto.randomBytes(8).toString('hex')

    res.json({ success: true, session })

    const client = net.createConnection(5000, 'grader', async () => {
        client.write(JSON.stringify({
            file: Buffer.concat(body.data).toString(),
        }) + '\n')
    })

    const reader = readline.createInterface({ input: client })
    const promise = new Promise((resolve, reject) => {
        reader.once('line', resolve)
        client.once('close', reject)
        client.on('error', reject)
    })
    promise.catch(() => {})
    sessions.set(session, promise)
})

app.get('/api/stream/:session', async (req, res) => {
    res.type('text/event-stream')

    const send = (event, data) => {
        res.write([
            `event: ${event}`,
            `data: ${data}`,
        ].join('\n') + '\n\n')
    }

    if (!sessions.has(req.params.session)) {
        send('error', 'Session not found!')
        return res.end()
    }

    const session = req.params.session

    try {
        const data = await sessions.get(session)
        const cases = JSON.parse(data.toString())

        const total = 22
        const successes = cases.filter((r) => r.status === 'success')
        const failures = cases.filter((r) => r.status === 'failure')
        const errors = cases.filter((r) => r.status === 'error')

        const result = { cases }
        if (
            successes.length === total &&
            failures.length === 0 &&
            errors.length === 0
        ) result.message = `All test cases passed! Flag: ${process.env.FLAG}`
        else result.message = `Passed ${successes.length} of ${total} cases.`

        send('result', JSON.stringify(result))
    } catch (e) {
        send('error', [
            'There was a problem grading your submission. Make sure your',
            'submission does not open files, import extra modules, run',
            'shell commands, or do anything too fancy.',
        ].join(' '))
    }
})

app.listen(PORT, () => console.log(`listening on ${PORT}`))
