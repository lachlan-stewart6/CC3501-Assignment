/*
 * mpu6050.h
 *
 *  Created on: 8 Oct 2020
 *      Author: jc299375
 */

#ifndef SOURCES_MPU6050_H_
#define SOURCES_MPU6050_H_

//Registers
#define CONFIG 0x1A //FRAME SYN and LOW Pass filter
#define DLPF_CONFIG 0
#define DLPF_BW_260 0 //FS=8kHz
#define DLPF_BW_180 1 //FS=1kHz
#define DLPF_BW_100 2 //FS=1kHz

#define GYRO_CONFIG 0x1B //Sets standby bits and full scale
#define XG_ST 7
#define YG_ST 6
#define ZG_ST 5
#define FS_SEL 3
#define FS_SEL_250 0 //+-250deg/s
#define FS_SEL_500 1 //+-500deg/s
#define FS_SEL_1000 2//+-1000deg/s
#define FS_SEL_2000 3//+-2000deg/s

#define ACCEL_CONFIG 0x1C //Sets standby bits and full scale
#define XA_ST 7
#define YA_ST 6
#define ZA_ST 5
#define AFS_SEL 3
#define AFS_SEL_2 0 //+-2g
#define AFS_SEL_4 1 //+-4g
#define AFS_SEL_8 2//+-8g
#define FS_SEL_16 3//+-16g

#define PWR_MGMT_1 0x6B
#define DEVICE_RESET 7
#define SLEEP 6
#define CYCLE 5
#define TEMP_DIS 3
#define CLKSEL 0
#define INT8 0
#define PLL_X 1
#define PLL_Y 2
#define PLL_Z 3


#define PWR_MGMT_2 0x6C
#define LP_WAKE_CTRL 6
#define STBY_XA 5
#define STBY_YA 4
#define STBY_ZA 3
#define STBY_XG 2
#define STBY_YG 1
#define STBY_ZG 0

#define FIFO_EN 0x23
#define TEMP_FIFO_EN 7
#define XG_FIFO_EN 6
#define YG_FIFO_EN 5
#define ZG_FIFO_EN 4
#define ACCEL_FIFO_EN 3
#define SLV2_FIFO_EN 2
#define SLV1_FIFO_EN 1
#define SLV0_FIFO_EN 0

#define FIFO_COUNT_H 0x72
#define FIFO_COUNT_L 0x73
#define FIFO_R_W 0x74

#define USER_CTRL 0x6A
#define FIFO_EN_BIT 6
#define FIFO_RESET 2


#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48

#define INT_ENABLE 0x38
#define DATA_RDY_EN 0


#define SMPLRT_DIV 0x19
#define I2C_MST_CTRL 0x24

#define SMPRT_DIV 0x19

#define WHO_AM_I 0x75



#endif /* SOURCES_MPU6050_H_ */
