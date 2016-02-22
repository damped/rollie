# rollie
Self Balancing Robot


This is the place for a high level discription of the code and what its for


## Installation
### Dependencies
`sudo apt-get install sshpass` used to send the password to the digital ocean server

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

#_IP=$(hostname -I) || true
#if [ "$_IP" ]; then
  #printf "My IP address is %s\n" "$_IP"
#fi

/bin/sleep 20

/usr/bin/python /home/pi/rollie/tools/sendip.py

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

## Remote Server
To be able to connect to the raspberrypi enter `pi1` on the server. This will auto connect to the raspberrypi provided that it has established a reverse ssh tunnle.

## Connecting the IMU
To connect the IMU to the raspberry Pi connect the ground and 3.3V and connect the SCL and SCA to their respective inputs on the Pi. Follow this pinout for the PI.

 ![Raspberry Pi pinout](https://www.element14.com/community/servlet/JiveServlet/previewBody/73950-102-4-309126/GPIO_Pi2.png)



## Dependencies
i2c-tools

