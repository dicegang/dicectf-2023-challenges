import flag from './challenge/flag.txt'

function sleep(time) {
  return new Promise(resolve => {
    setTimeout(resolve, time)
  })
}

export default {
  name: 'codebox admin bot',
  urlRegex: /^https:\/\/codebox\.mc\.ax\/\?code=.*$/,
  timeout: 10000,
  handler: async (url, ctx) => {
    const page = await ctx.newPage();
    await page.goto('https://codebox.mc.ax', { timeout: 3000, waitUntil: 'domcontentloaded' });
    await page.evaluate(flag => {
        localStorage.setItem('flag', flag);
    }, flag);
    await page.goto(url, { timeout: 3000, waitUntil: 'domcontentloaded' });
    await sleep(3000);
  }
}
