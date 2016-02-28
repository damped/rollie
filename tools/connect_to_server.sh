#!/bin/bash
createTunnel() {
  sleep 2
  /usr/bin/ssh -N -R $(hostname):localhost:22 root@159.203.6.212 &
  if [[ $? -eq 0 ]]; then
    echo Tunnel to jumpbox created successfully
  else
    echo An error occurred creating a tunnel to jumpbox. RC was $?
  fi
}

for i in `seq 1 5`;
do
  /bin/pidof ssh
  if [[ $? -ne 0 ]]; then
    echo Creating new tunnel connection
    createTunnel
  fi
echo ye
sleep 5
done
