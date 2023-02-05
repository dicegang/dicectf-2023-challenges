listen('form', async (data) => {
    const name = data.get('name')
    const response = await request('POST', '/api/login', { name })
    if (response) { location = '/' }
})
