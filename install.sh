#!/usr/bin/bash

echo Installing dnsfw v1.3.0-stable
echo I hope you edited your config!
echo ------------------------------
install -m 750 dnsfw /usr/sbin/
mkdir -p /etc/bacon
install -m 644 dnsfw.conf /etc/bacon/

install -m 644 dnsfw.service /etc/systemd/system/
systemctl daemon-reload
systemctl enable dnsfw.service
systemctl start dnsfw.service

service dnsfw status
echo Done! You may edit the config file at
echo /etc/bacon/dnsfw.conf
echo ------------------------------