#!/bin/bash

espweb_mdns_url=esp8266web.local
espweb_port=80
espweb_tunnel_service=srv.us
espweb_tunnel_username='[username]'

# Use this script to tunnel the espweb service online if you don't want to use
# port forwarding.

until ssh $espweb_tunnel_username@$espweb_tunnel_service -R 1:$espweb_mdns_url:$espweb_port
do
	echo Service stopped at $(date +"%Y-%m-%d %H:%M:%S").
	echo Restarting tunnel...
done
