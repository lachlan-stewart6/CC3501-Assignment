// Registers for ICM-20948

#define WHO_AM_I 0x00 // Response of 0xEA for 
#define USER_CTRL 0x03
#define ICM_ADDR 0x69
#define MAG_ADDR 0x0C
#define LP_CONFIG 0x05  
#define PWR_MGMT_1 0x06 // Requires a 0 for power on
#define PWR_MGMT_2 0x07

#define ACCEL_XOUT_H 0x2D // This initialises all readings of ACCEL, GYRO

#define ACCEL_FS 0 // +-2G OR 16384 LSB/g
#define ACCEL_FS 1 //+-4G OR 8192 LSB/g
#define ACCEL_FS 2 //+-8G OR 4096 LSB/g
#define ACCEL_FS 3 //+-16G OR 2048 LSB/g

#define GYRO_XOUT_H 0x33

#define GYRO_SEL_250 0 //+-250dps OR 131 LSB/dps
#define GYRO_SEL_500 1 //+-500dps OR 65.5 LSB/dps
#define GYRO_SEL_1000 2//+-1000dps OR 32.8 LSB/dps
#define GYRO_SEL_2000 3//+-2000dps OR 16.4 LSB/dps

#define MAG_XOUT_H 0x11

#define FIFO_EN_1 0x66
#define FIFO_EN_2 0x67
#define FIFO_RST 0x68
#define FIFO_MODE 0x69
#define FIFO_COUNT_H 0x70
#define FIFO_COUNT_L 0x71
#define FIFO_R_W 0x72
#define DATA_RDY_STATUS 0x74
#define FIFO_CFG 0x76
#define REG_BANK_SEL 0x7F

#define TEMP_FIFO_EN 7
#define XG_FIFO_EN 6
#define YG_FIFO_EN 5
#define ZG_FIFO_EN 4
#define ACCEL_FIFO_EN 3
#define SLV2_FIFO_EN 2
#define SLV1_FIFO_EN 1
#define SLV0_FIFO_EN 0


