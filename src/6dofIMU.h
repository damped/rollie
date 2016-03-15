#ifndef 6DOFIMU_H_
#define 6DOFIMU_H_


// libraries and header files
#include <iostream>
#include <errno.h>
#include <wiringPi.h>
#include "stdio.h"
#include <math.h>
#include <wiringPiI2C.h>
#include <stdint.h>
#include <stdlib.h>



//prototypes
double accPitch(int);
int accConfig(void);
float getangle(int, int);
int gyroConfig(void);



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

#define WHO_AM_I_REG    0x00
#define SMPLRT_DIV_REG  0x15
#define DLPF_FS_REG     0x16
#define INT_CFG_REG     0x17
#define INT_STATUS      0x1A
#define TEMP_OUT_H_REG  0x1B
#define TEMP_OUT_L_REG  0x1C
#define GYRO_XOUT_H_REG 0x1D
#define GYRO_XOUT_L_REG 0x1E
#define GYRO_YOUT_H_REG 0x1F
#define GYRO_YOUT_L_REG 0x20
#define GYRO_ZOUT_H_REG 0x21
#define GYRO_ZOUT_L_REG 0x22
#define PWR_MGM_REG     0x3E

//----------------------------
// Low Pass Filter Bandwidths
//----------------------------
#define LPFBW_256HZ 0x00
#define LPFBW_188HZ 0x01
#define LPFBW_98HZ  0x02
#define LPFBW_42HZ  0x03
#define LPFBW_20HZ  0x04
#define LPFBW_10HZ  0x05
#define LPFBW_5HZ   0x06

//-----------
// Offsets
//-----------
short int TEMP_OUT_OFFSET = 0;
short int GYRO_XOUT_OFFSET = 0;
short int GYRO_YOUT_OFFSET = 0;
short int GYRO_ZOUT_OFFSET = 0;
