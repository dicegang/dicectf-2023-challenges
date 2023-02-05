import flag from './flag.txt'

function sleep(time) {
  return new Promise(resolve => {
    setTimeout(resolve, time)
  })
}

export default {
  name: 'jnotes admin bot',
  urlRegex: /^https?:\/\/.*\//,
  timeout: 10000,
  handler: async (url, ctx) => {
    const page = await ctx.newPage();
    await page.goto('https://jnotes.mc.ax', { timeout: 3000, waitUntil: 'domcontentloaded' });
    await page.setCookie({
      name: "FLAG",
      value: flag,
      domain: "jnotes.mc.ax",
      path: "/",
      secure: true,
      httpOnly: true
    });

    await page.goto(url, { timeout: 3000, waitUntil: 'domcontentloaded' });
    await sleep(3000);
  }
}
