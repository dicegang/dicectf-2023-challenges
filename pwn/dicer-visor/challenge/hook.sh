#!/bin/sh

mount -o remount,rw none /srv/dev
chmod 777 /srv/dev/kvm
mount -o rwmount,ro none /srv/dev
echo 'clone_newnet: false' >> $nsjail_cfg
