tar --owner="arx" --group="arx" \
    --exclude challenge/app/flag.txt \
    --transform 's|challenge|geminiblog|' \
    -czvf handout.tar.gz challenge
