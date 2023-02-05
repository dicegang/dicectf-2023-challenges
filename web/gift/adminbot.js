import token from './admin.txt'

const sleep = (t) => new Promise((r) => setTimeout(r, t))

export default {
    name: 'gift admin bot',
    timeout: 10000,
    handler: async (url, ctx) => {
        const page = await ctx.newPage()
        await page.goto('https://gift.mc.ax/login/', {
            timeout: 3000,
            waitUntil: 'domcontentloaded'
        })
        await page.evaluate(async (token) => {
            await fetch('/api/login', {
                method: 'POST',
                body: JSON.stringify({
                    name: crypto.randomUUID(),
                    admin: token.trim(),
                }),
            })
        }, token)

        await page.goto(url, { timeout: 3000, waitUntil: 'domcontentloaded' })
        await sleep(3000)
    },
}
