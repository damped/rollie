#!/bin/bash
#
#   boot.sh
#
#   Runs at boot

cd /home/pi/rollie/tools/ > /dev/null 2>&1

# Send IP with email
/usr/bin/python /home/pi/rollie/tools/sendip.py > /dev/null 2>&1 &&

# Connect to the server
/bin/bash connect_to_server.sh > /dev/null 2>&1 &&

# Get the newest version of the code
runuser -l  pi -c '/bin/bash update.sh > /dev/null 2>&1'

