#!/bin/bash
#
#   boot.sh
#
#   Runs at boot

cd /home/pi/rollie/tools/ > dev/null

# Send IP with email
/usr/bin/python /home/pi/rollie/tools/sendip.py > dev/null &&

# Connect to the server
/bin/bash connect_to_server.sh > dev/null &&

# Get the newest version of the code
/bin/bash update.sh > dev/null

