# rollie
Self Balancing Robot


This is the place for a high level discription of the code and what its for


## Installation
### Edit rc.local file to run stuff on boot

You will want to edit the file with `sudo nano /etc/rc.local` and add the following:

```c
#!/bin/sh -e
#
# rc.local
#
# This script is executed at the end of each multiuser runlevel.
# Make sure that the script will "exit 0" on success or any other
# value on error.
#
# In order to enable or disable this script just change the execution
# bits.
#
# By default this script does nothing.

# Print the IP address

/bin/sleep 20

_IP=$(hostname -I) || true
if [ "$_IP" ]; then
  #printf "My IP address is %s\n" "$_IP" mother fucker
  /usr/bin/python /home/pi/rollie/tools/sendip.py
fi

exit 0 
```

### BCIT Network Setup
Add the following to `sudo nano /etc/wpa_supplicant/wpa_supplicant.conf`
Make sure to edit the user and password.
```
network={
        ssid="BCIT_Secure"
        key_mgmt=WPA-EAP
        eap=PEAP
        identity="a00######"      <--- Here
        password="super_secret"   <--- And here
        phase2="auth=MSCHAPV2"
}
```
