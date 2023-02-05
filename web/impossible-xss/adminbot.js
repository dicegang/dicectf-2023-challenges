import flag from './flag.txt'

function sleep(time) {
  return new Promise(resolve => {
    setTimeout(resolve, time)
  })
}

export default {
  name: 'impossible-xss admin bot',
  urlRegex: /^https:\/\/impossible-xss.mc.ax\//,
  timeout: 10000,
  handler: async (url, ctx) => {
    const page = await ctx.newPage();
    await page.goto('https://impossible-xss.mc.ax', { timeout: 3000, waitUntil: 'domcontentloaded' });

    // you wish it was that easy
    await page.setCookie({
        "name": "FLAG",
        "value": flag,
        "domain": "impossible-xss.mc.ax",
        "path": "/",
        "httpOnly": true,
        "secure": true,
        "sameSite": "Strict"
    });
    await page.setJavaScriptEnabled(false);

    await page.goto(url, { timeout: 3000, waitUntil: 'domcontentloaded' });
    await sleep(3000);
  }
}
