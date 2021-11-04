/*
 * MPU6050_MVD.h
 *
 *  Created on: Oct 19, 2021
 *      Author: Murilo Henrique Pasini Trevisan
 */

#ifndef INC_MPU6050_MVD_H_
#define INC_MPU6050_MVD_H_

#include "bsp.h"


/* REGISTRADORES */

// Name				//Adress(hex)

// Registradores de configuração
#define MPU_SMPRT_DIV		(uint16_t)(0x19)
#define MPU_CONFIG			(uint16_t)(0x1A)
#define MPU_GYRO_CONFIG		(uint16_t)(0x1B)
#define	MPU_ACCEL_CONFIG	(uint16_t)(0x1C)
#define MPU_FIFO_EN			(uint16_t)(0x23) //Default desabilitado
#define MPU_INT_ENABLE		(uint16_t)(0x38) //Default desabilitado
#define MPU_INT_STATUS		(uint16_t)(0x3A) //Read only

// Registradores de leitura dos dados
// Acelerômetro
#define MPU_ACCEL_XOUT_H	(uint16_t)(0x3B)
#define MPU_ACCEL_XOUT_L	(uint16_t)(0x3C)
#define MPU_ACCEL_YOUT_H	(uint16_t)(0x3D)
#define MPU_ACCEL_YOUT_L	(uint16_t)(0x3E)
#define MPU_ACCEL_ZOUT_H	(uint16_t)(0x3F)
#define MPU_ACCEL_ZOUT_L	(uint16_t)(0x40)

//Temperatura
#define MPU_TEMP_OUT_H		(uint16_t)(0x41)
#define MPU_TEMP_OUT_L		(uint16_t)(0x42)

// Giroscópio
#define MPU_GYRO_XOUT_H		(uint16_t)(0x43)
#define MPU_GYRO_XOUT_L		(uint16_t)(0x44)
#define MPU_GYRO_YOUT_H		(uint16_t)(0x45)
#define MPU_GYRO_YOUT_L		(uint16_t)(0x46)
#define MPU_GYRO_ZOUT_H		(uint16_t)(0x47)
#define MPU_GYRO_ZOUT_L		(uint16_t)(0x48)

// Sensores externos conectados a IMU
// Leitura dos endereços 0x49 até 0x60
// Registradores de nomes EXT_SENS_DATA_00 até EXT_SENS_DATA_23

/* Configurações */

//SMPRT_DIV
//Sample rate = sensor output rate/(1+SMPLRT_DIV)
//SMPRLT_DIV = (sensor output rate)/(sample rate) - 1
//Utilizando filtros, SRmin=3,9 Hz e SRmáx=1kHz
//Inserir um valor para realizar a divisão
//Alguns valores base já calculados que podem ser usados
#define MPU_SMPRT_1k		(uint8_t)(0x00) //1 kHz
#define MPU_SMPRT_4			(uint8_t)(0x00) //4 Hz
#define MPU_SMPRT_10		(uint8_t)(0x63) //10 Hz
#define MPU_SMPRT_100		(uint8_t)(0x09) //100 Hz

//CONFIG
// configuração da external frame synchronization
#define MPU_FSYNC_DISABLE	(uint8_t)(0x00 << 5) //desabilita a leitura de sinais externos
// configuração do filtro digital passa baixa a ser utilizado
#define MPU_DLPF_CG0		(uint8_t)(0x00 << 3) //A-260 G-256 Hz Digital low pass filter
#define MPU_DLPF_CG1		(uint8_t)(0x01 << 3) //A-184 G-188 Hz
#define MPU_DLPF_CG2		(uint8_t)(0x02 << 3) //A-94  G-98  Hz
#define MPU_DLPF_CG3		(uint8_t)(0x03 << 3) //A-44  G-42  Hz
#define MPU_DLPF_CG4		(uint8_t)(0x04 << 3) //A-21  G-20  Hz
#define MPU_DLPF_CG5		(uint8_t)(0x05 << 3) //A-10  G-10  Hz
#define MPU_DLPF_CG6		(uint8_t)(0x06 << 3) //A-05  G-05  Hz

//GYRO_CONFIG
//Quanto maior o range menor a precisão do sensor
//Relação precisão e range explicada no datasheet na parte do acelerometro
#define MPU_GFS_SEL_250		(uint8_t)(0x00 << 4) //+- 250°/s
#define MPU_GFS_SEL_500		(uint8_t)(0x01 << 4) //+- 500°/s
#define MPU_GFS_SEL_1000	(uint8_t)(0x02 << 4) //+- 1000°/s
#define MPU_GFS_SEL_2000	(uint8_t)(0x03 << 4) //+- 2000°/s

//ACCEL_CONFIG
#define MPU_AFS_SEL_2		(uint8_t)(0x00 << 4) //+-2g
#define MPU_AFS_SEL_4		(uint8_t)(0x01 << 4) //+-4g
#define MPU_AFS_SEL_8		(uint8_t)(0x02 << 4) //+-8g
#define MPU_AFS_SEL_16		(uint8_t)(0x03 << 4) //+-16g

//FIFO_EN
#define MPU_FIFO_DISABLE	(uint8_t)(0x00) //Desabilita a FIFO

//INT_EN
#define MPU_INT_FIFO_DIS	(uint8_t)(0x00 << 4) //desabilita interrupção da FIFO
#define MPU_INT_DATA_READY	(uint8_t)(0x00 << 0) //desabilita interrupção de dados prontos

/* Structs de configuração */

typedef struct {
	uint8_t FSyncEnable;	//FSYNC
	uint8_t LowPassFilter;	//DLPF
} MPU6050_config_t ;

typedef struct {
	uint8_t GyroRange;
}MPU6050_gyro_config_t;

typedef struct {
	uint8_t AccelRange;
}MPU6050_accel_config_t;

typedef struct {
	i2c_device_t device;
	MPU6050_config_t config;
	MPU6050_gyro_config_t GyroConfig;
	MPU6050_accel_config_t AccelConfig;
}MPU6050_t;

/* Structs de leitura dos valores */

typedef struct {
	float AccelX;
	float AccelY;
	float AccelZ;
	float GyroX;
	float GyroY;
	float GyroZ;
	float Temp;
} MPU6050_values_t;

error_t MPU6050_config(MPU6050_t mpu);
error_t MPU6050_gyro_config(MPU6050_t mpu);
error_t MPU6050_accel_config(MPU6050_t mpu);




#endif /* INC_MPU6050_MVD_H_ */