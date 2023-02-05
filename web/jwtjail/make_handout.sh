cp -r challenge jwtjail
echo -n "dice{test_flag}" > jwtjail/flag.txt
tar --owner="strell" --group="strell" -H v7 --no-xattr --mtime=1970-01-01T00:00Z -czvf jwtjail.tar.gz jwtjail
rm -rf jwtjail
