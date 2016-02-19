#!/bin/bash
#
#   boot.sh
#
#   Runs at boot

cd /home/pi/rollie/tools/

# Send IP with email
/usr/bin/python /home/pi/rollie/tools/sendip.py &&

# Connect to the server
/bin/bash connect_to_server.sh &&

# Get the newest version of the code
/bin/bash update.sh &&

