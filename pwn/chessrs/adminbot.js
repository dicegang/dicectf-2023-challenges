import flag from './flag.txt'

function sleep(time) {
  return new Promise(resolve => {
    setTimeout(resolve, time)
  })
}

export default {
  name: 'chess.rs admin bot',
  urlRegex: /^https?:\/\/.*\//,
  timeout: 10000,
  handler: async (url, ctx) => {
    const page = await ctx.newPage();
    await page.goto('https://chessrs.mc.ax', { timeout: 3000, waitUntil: 'domcontentloaded' });
    await page.evaluate(flag => {
        document.cookie = `flag=${flag}`;
    }, flag);
    await page.goto(url, { timeout: 3000, waitUntil: 'domcontentloaded' });
    await sleep(3000);
  }
}
