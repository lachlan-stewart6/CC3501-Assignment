/*
 * main.h
 *
 *  Created on: 24 Oct 2020
 *      Author: jc493320
 */

#ifndef SOURCES_MAIN_H_
#define SOURCES_MAIN_H_

#define QUEUE_LENGTH 2

typedef struct {
	int msg_id ;
	int AccX, AccY, AccZ;
	int accAngleX, accAngleY;
	int GyroX, GyroY, GyroZ;
	int gyroAngleX, gyroAngleY , gyroAngleZ;
	int MagX, MagY , MagZ ;
	int yaw, pitch, roll;
	word elapsedTime, bluetoothTime;
	byte acc[6];
	byte gyro[6];
	byte mag[6];
} Message ;

typedef struct {
	LWMSGQ_STRUCT header;
	Message msgs [QUEUE_LENGTH];
}MessageQueue;

MessageQueue msg_queue;
Message msg;




#endif /* SOURCES_MAIN_H_ */
