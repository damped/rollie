#!/bin/bash
#
#   update.sh
#
#   Update the rollie folder from github
#

/usr/bin/git fetch origin

/usr/bin/git reset --hard origin/master
