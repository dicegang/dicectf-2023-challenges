tar --owner="arx" --group="arx" \
    --exclude challenge/jnotes/target \
    --transform 's|challenge|jnotes|' \
    -cvf handout.tar challenge

tar --append --file=handout.tar challenge/jnotes/target/app.jar --transform 's|challenge/jnotes/target/app.jar|jnotes/jnotes/target/app.jar|'
tar --append --file handout.tar adminbot-handout.js --transform 's|adminbot|jnotes/adminbot-handout.js|'
