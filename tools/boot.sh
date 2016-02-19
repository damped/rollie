#!/bin/bash
#
#   boot.sh
#
#   Runs at boot


# Send IP with email
/usr/bin/python /home/pi/rollie/tools/sendip.py

# Connect to the server
/bin/bash connect_to_server.sh

