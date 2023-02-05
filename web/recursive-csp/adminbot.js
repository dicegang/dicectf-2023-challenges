import flag from './flag.txt'

function sleep(time) {
  return new Promise(resolve => {
    setTimeout(resolve, time)
  })
}

export default {
  name: 'recursive-csp admin bot',
  urlRegex: /^https:\/\/recursive-csp\.mc\.ax\//,
  timeout: 10000,
  handler: async (url, ctx) => {
    const page = await ctx.newPage();
    await page.goto('https://recursive-csp.mc.ax', { timeout: 3000, waitUntil: 'domcontentloaded' });
    await page.evaluate(flag => {
        document.cookie = `flag=${flag}`;
    }, flag);
    await page.goto(url, { timeout: 3000, waitUntil: 'domcontentloaded' });
    await sleep(3000);
  }
}
