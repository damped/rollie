# rollie
Self Balancing Robot


This is the place for a high level discription of the code and what its for

## Compiling
for now, run `g++ getangle.c -lwiringPi -o run` in the src directory.

## Getting angles
The gyroscope is located at 0x68 and returns a device id of 0x69
The acceleromiter is located at 0x53 and returns a device id of 0xE5

## Installation
### Dependencies
i2c-tools

### Edit Chron tab
run `crontab -e` to open the cron tab editor. Then add the following:
```
@reboot /home/pi/rollie/tools/boot.sh >> boot.log 2>&1

*/1 * * * * ~/rollie/tools/connect_to_server.sh >> tunnel.log 2>&1
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

### Remote Server
To be able to connect to the raspberrypi enter `pi1` on the server. This will auto connect to the raspberrypi provided that it has established a reverse ssh tunnel.

### Connecting the IMU
To connect the IMU to the raspberry Pi connect the ground and 3.3V and connect the SCL and SCA to their respective inputs on the Pi. Follow this pinout for the PI.

 ![Raspberry Pi pinout](https://www.element14.com/community/servlet/JiveServlet/previewBody/73950-102-4-309126/GPIO_Pi2.png)
 
### Reading from the IMU
 ![Accelerameter Register Map](http://www.aimagin.com/learn/images/thumb/2/2a/Using_i2c_master-example-adx345_register_map.PNG/800px-Using_i2c_master-example-adx345_register_map.PNG)
