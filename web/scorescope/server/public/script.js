const state = { file: null, id: null, event: null }

const zone = document.querySelector('.drag')
const upload = document.querySelector('button')
const output = document.querySelector('.output')

const updateFiles = () => {
    const { file } = state

    if (file) {
        zone.classList.remove('drag')
        zone.textContent = ''

        const a = document.createElement('a')
        a.textContent = file.name
        a.classList.add('file')
        a.addEventListener('click', (e) => {
            e.preventDefault()
            e.stopPropagation()
            state.file = null
            updateFiles()
        })

        zone.appendChild(a)
    } else {
        const strong = document.createElement('strong')
        strong.textContent = 'Drag & Drop'

        const inner = document.createElement('div')
        inner.appendChild(strong)

        const div = document.createElement('div')
        div.appendChild(inner)
        div.appendChild(document.createTextNode(
            'Any Python file. Click to browse.'
        ))

        zone.classList.add('drag')
        zone.textContent = ''
        zone.appendChild(div)
    }
}

zone.addEventListener('dragover', (e) => e.preventDefault())
zone.addEventListener('drop', (e) => {
    e.preventDefault()
    if (!e.dataTransfer.files.length) return
    const file = e.dataTransfer.files[0]
    if (file.size > 1e6) return
    state.file = file
    updateFiles()
})
zone.addEventListener('click', (e) => {
    e.preventDefault()
    const input = document.createElement('input')
    input.type = 'file'
    input.accept = '.py'
    input.max = 1e6
    input.addEventListener('change', () => {
        if (!input.files.length) return
        const file = input.files[0]
        state.file = file
        updateFiles()
    })
    input.click()
})

upload.addEventListener('click', async () => {
    const { file } = state
    if (!file) return
    state.file = null

    const response = await fetch('/api/submit', {
        method: 'POST',
        body: file,
    })
    const data = await response.json()
    updateFiles()

    if (!data.success) return

    state.id = data.session

    output.textContent = 'Grading...'

    state.event?.close()
    state.event = new EventSource(`/api/stream/${state.id}`)
    state.event.addEventListener('result', (e) => {
        const { message, cases } = JSON.parse(e.data)

        output.textContent = message
        for (const { name, status, message } of cases) {
            const div = document.createElement('div')
            div.classList.add('case')
            div.classList.add(`case-${status}`)

            const header = document.createElement('div')
            header.classList.add('case-header')
            header.textContent = `${name} - ${status}`
            div.appendChild(header)

            if (message) {
                const output = document.createElement('div')
                output.classList.add('case-message')

                const pre = document.createElement('pre')
                pre.textContent = message

                output.appendChild(pre)
                div.appendChild(output)
            }

            output.appendChild(div)
        }
    })
    state.event.addEventListener('error', (e) => {
        output.textContent = e.data
    })
})

updateFiles()
