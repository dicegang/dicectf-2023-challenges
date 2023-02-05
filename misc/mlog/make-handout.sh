#!/bin/sh
set -e
cd "$(dirname "$0")"
git ls-files -z chall | xargs -0 tar --owner="dicegang" --group="dicegang" -H ustar --no-xattr --mtime=1970-01-01T00:00Z -czvf mlog.tar.gz --transform s/chall/mlog/
