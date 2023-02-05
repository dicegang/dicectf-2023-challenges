void (async () => {
    await load

    listen('form', (data) => {
        const amount = data.get('amount')
        location = `/create/${amount}`
    })
})()
