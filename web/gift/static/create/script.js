void (async () => {
    await load

    const counter = document.querySelector('#count')
    const set = async (value) => {
        const response = await request('POST', `/api/config/${data.public}`, {
            limit: value,
            private: data.private,
        })
        if (response) counter.innerHTML = value
    }
    const update = (delta) => set(+counter.innerHTML + delta)

    set(0)

    document.querySelector('#up').addEventListener('click', () => update(1))
    document.querySelector('#down').addEventListener('click', () => update(-1))
})()
