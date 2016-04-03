# rollie
Self Balancing Robot


This is the place for a high level discription of the code and what its for

## Git
Git cheat sheet: https://confluence.atlassian.com/bitbucketserver/basic-git-commands-776639767.html
Git workflow: https://www.atlassian.com/git/tutorials/comparing-workflows/feature-branch-workflow

## Compiling
Depriciated: for now, run `g++ getangle.c -lwiringPi -o run` in the src directory.

The new makefile system allows us to easaly compile all the files togeter. It does some fancy things like only compileing what was changed, and allows us to install the program in the `~/bin` folder. This means that when you type `rollie` from anywher it will exicute the program.

For testing run:
```
make
./rollie
```

When you wish to install:
```
make install
rollie
```

Before you commit run:
```
make clean
git add *    #or any spicific files to add to the commit
git commit -m "message"
git push
```
Maybe we will add that last part to make so we just need to do something like `make commit` idk...


## Getting angles
Complementary filter http://www.pieter-jan.com/node/11

The gyroscope is located at 0x68 and returns a device id of 0x69
The acceleromiter is located at 0x53 and returns a device id of 0xE5

### PID controller
The PID controller is provided by a github libary. https://github.com/cvra/pid

## Installation
### Dependencies
i2c-tools

### Edit raspi-config
Enter `sudo raspi-config` and set the host name to a number ex 2223. This is used to represent the port number to distiguish it between the other clients on the server.


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

## Hardware 
### Reading from the IMU
#### Accelerometer reg map
 ![Accelerameter Register Map](http://www.aimagin.com/learn/images/thumb/2/2a/Using_i2c_master-example-adx345_register_map.PNG/800px-Using_i2c_master-example-adx345_register_map.PNG)
 
#### Gyro reg map
![Gyro Register Map](http://fixled.ru/image/data/Gyromap-s.jpg)

### Stepper drivers
https://www.pololu.com/product/1182

### References
Realy great stuff:
http://letsmakerobots.com/node/38610
