# Pike

just write an exploit for CVE-2019-16328 (RCE in rpyc 4.1.0), afaik no poc exists as the author fixed and reported it with little details

the protocol doesn't sanitise comparison properties, allowing arbritrary `getattr` on remote objects

we can use this to reach and import subprocess, then execute commands to read the flag

patched in: https://github.com/tomerfiliba-org/rpyc/commit/d818ecc83a92548994db75a0e9c419c7bce680d6

## infra

should start up an instance and expose the rpyc tcp port to a user

## download

provide server/server.py 
