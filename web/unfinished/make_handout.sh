cp -r challenge unfinished
tar --owner="strell" --group="strell" -H v7 --no-xattr --mtime=1970-01-01T00:00Z -czvf unfinished.tar.gz unfinished
rm -rf unfinished
