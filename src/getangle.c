
//authors Michael and Jonas
//description, Program to return an accurate angle from the IMU.
//
//Outputs


#include <iostream>
#include <errno.h>
#include <wiringPi.h>
#include "stdio.h"
#include <math.h>
#include <wiringPiI2C.h>

// adxl345 registers

#define ADXL345_REG_DEVID               (0x00)    // Device ID
#define ADXL345_REG_THRESH_TAP          (0x1D)    // Tap threshold
#define ADXL345_REG_OFSX                (0x1E)    // X-axis offset
#define ADXL345_REG_OFSY                (0x1F)    // Y-axis offset
#define ADXL345_REG_OFSZ                (0x20)    // Z-axis offset
#define ADXL345_REG_DUR                 (0x21)    // Tap duration
#define ADXL345_REG_LATENT              (0x22)    // Tap latency
#define ADXL345_REG_WINDOW              (0x23)    // Tap window
#define ADXL345_REG_THRESH_ACT          (0x24)    // Activity threshold
#define ADXL345_REG_THRESH_INACT        (0x25)    // Inactivity threshold
#define ADXL345_REG_TIME_INACT          (0x26)    // Inactivity time
#define ADXL345_REG_ACT_INACT_CTL       (0x27)    // Axis enable control for activity and inactivity detection
#define ADXL345_REG_THRESH_FF           (0x28)    // Free-fall threshold
#define ADXL345_REG_TIME_FF             (0x29)    // Free-fall time
#define ADXL345_REG_TAP_AXES            (0x2A)    // Axis control for single/double tap
#define ADXL345_REG_ACT_TAP_STATUS      (0x2B)    // Source for single/double tap
#define ADXL345_REG_BW_RATE             (0x2C)    // Data rate and power mode control
#define ADXL345_REG_POWER_CTL           (0x2D)    // Power-saving features control
#define ADXL345_REG_INT_ENABLE          (0x2E)    // Interrupt enable control
#define ADXL345_REG_INT_MAP             (0x2F)    // Interrupt mapping control
#define ADXL345_REG_INT_SOURCE          (0x30)    // Source of interrupts
#define ADXL345_REG_DATA_FORMAT         (0x31)    // Data format control
#define ADXL345_REG_DATAX0              (0x32)    // X-axis data 0
#define ADXL345_REG_DATAX1              (0x33)    // X-axis data 1
#define ADXL345_REG_DATAY0              (0x34)    // Y-axis data 0
#define ADXL345_REG_DATAY1              (0x35)    // Y-axis data 1
#define ADXL345_REG_DATAZ0              (0x36)    // Z-axis data 0
#define ADXL345_REG_DATAZ1              (0x37)    // Z-axis data 1
#define ADXL345_REG_FIFO_CTL            (0x38)    // FIFO control
#define ADXL345_REG_FIFO_STATUS         (0x39)    // FIFO status


#define  ALPHA                          (0 )      //Alpha

/*
 //function prototypes
void accelGetc0ord(void);   //grabs the  coordinates and from accelerometer
void gyroGetcoord(void);    //grabs the coordinates from gyro
void imuSetup(void);        //setup
*/
struct AccelRaw
{
  int x;
  int y;
  int z;
};

struct AccelG
{
  double x;
  double y;
  double z;
};

struct AccelRotation
{
  double pitch;
  double roll;
};

/*
class ADXL345()
    {
    public:

    }
*/
// prototypes
//AccelRaw ADXL345::readAccel()
//void ADXL345::init(char, char, char);

// prototypes, non class
void initialization(void);
AccelG readAccelG(void);
AccelRaw readAccel(void);

int main() {

/*
        int ret;
        int devGyro = wiringPiI2CSetup(0x68);
        int dataGyro = wiringPiI2CReadReg8(devGyro, ADXL345_REG_DEVID);

        printf("Gyro device:%x\n", devGyro);
        printf("Gyro device id:%x\n\n", dataGyro);

        wiringPiI2CWriteReg8(devGyro, 0x15, 0x09);
        wiringPiI2CWriteReg8(devGyro, 0x16, 0x1a);
//      accelerometer code
*/


        initialization();



/*	printf("Gyro Data:\n");

        for (int i = 0; i<=2; i++)
        {
                int a = i*2;
                signed int gyroAngles = wiringPiI2CReadReg16(devGyro,(0x1d+a));

                //printf("GYRO ANGLES\n" );
                printf("%x: %d, %x\n", a+0x1d, gyroAngles, gyroAngles);
        }
*/
        printf("\nAccel device:%x\n", devAccel);
        printf("Accel device id:%x\n\n", dataAccel);

	printf("Acc Data:\n");

        for (int j = 0; j<=2; j++)
        {
                int b = j*2;
                signed int accAngles = wiringPiI2CReadReg16(devAccel,(0x32+b));

                //printf("ACC ANGLES\n" );
                printf("%x: %d, %x\n", b+0x32, accAngles, accAngles);
        }

        return 0;
}


//  setup for accelerometer

//void ADXL345::init(char x_offset, char y_offset, char z_offset)
void initialization()
      {
          int devAccel = wiringPiI2CSetup(0x53);
          int dataAccel = wiringPiI2CReadReg8(devAccel,0x00);

          wiringPiI2CWriteReg8(devAccel, ADXL345_REG_POWER_CTL, 0x08);

          wiringPiI2CWriteReg8(devAccel, ADXL345_REG_DATA_FORMAT, 0x0B);

          wiringPiI2CWriteReg8(devAccel, ADXL345_REG_OFSX, x_offset);
          wiringPiI2CWriteReg8(devAccel, ADXL345_REG_OFSY, y_offset);
          wiringPiI2CWriteReg8(devAccel, ADXL345_REG_OFSZ, z_offset);
      }

//AccelG ADXL345::readAccelG()
AccelG readAccelG()
      {
          AccelRaw raw;
        //  raw = readAccel();


          double fXg, fYg, fZg;
          fXg =raw.x * 0.00390625; //+ _xoffset;
          fYg =raw.y * 0.00390625; //+ _yoffset;
          fZg =raw.z * 0.00390625; //+ _zoffset;

          AccelG res;

          res.x = fXg * ALPHA + (xg * (1.0-ALPHA));
          xg = res.x;

          res.y = fYg * ALPHA + (yg * (1.0-ALPHA));
          yg = res.y;

          res.z = fZg * ALPHA + (zg * (1.0-ALPHA));
          zg = res.z;

          return res;


      }
/*
//AccelRaw ADXL345::readAccel()
AccelRaw readAccel()
      {
          readFrom(ADXL345_DATAX0, ADXL345_TO_READ, _buff); //read the acceleration data from the ADXL345

          // each axis reading comes in 16 bit resolution, ie 2 bytes. Least Significat Byte first!!
          // thus we are converting both bytes in to one int
          AccelRaw raw;
          raw.x = (((int)_buff[1]) << 8) | _buff[0];
          raw.y = (((int)_buff[3]) << 8) | _buff[2];
          raw.z = (((int)_buff[5]) << 8) | _buff[4];

          return raw;
      }
*/
