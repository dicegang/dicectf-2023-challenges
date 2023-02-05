const data = JSON.parse(
    document.querySelector('meta[name=data]')?.content ?? '{}'
)

const load = (async () => {
    template({
        ...await request('GET', '/api/info'),
        gift: data.public,
        origin,
    })
})()
