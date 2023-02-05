const request = async (method, endpoint, data) => {
    const response = await fetch(endpoint, {
        headers: { 'content-type': 'application/json' },
        method,
        body: JSON.stringify(data),
    })
    const json = await response.json()
    if (response.ok) { return json }
    else { alert(json.error) }
}

const template = (values) => {
    const body = document.body
    body.innerHTML = body.innerHTML.replace(
        /:([a-z]+)/g,
        (_, key) => values[key] ?? `:${key}`
    )
}

const listen = (query, callback) => {
    const form = document.querySelector(query)
    form.addEventListener('submit', (e) => {
        e.preventDefault()
        callback(new Map(new FormData(form)))
    })
}

const info = async () => template(await request('GET', '/api/info'))
