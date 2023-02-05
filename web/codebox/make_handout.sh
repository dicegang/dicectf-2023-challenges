cp -r challenge codebox
echo "dice{test_flag}" > codebox/flag.txt
tar --owner="ehhthing" --group="ehhthing" -H v7 --no-xattr --mtime=1970-01-01T00:00Z -czvf codebox.tar.gz codebox
rm -rf codebox
