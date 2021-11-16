/*
 * MPU6050_MVD.c
 *
 *  Created on: Oct 19, 2021
 *      Author: Murilo Henrique Pasini Trevisan
 */


#include "MPU6050_MVD.h"

/* Configurações do sensor */

// Função para enviar via i2c o valor do samplerate
error_t MPU6050_smprt(MPU6050_t mpu) {

	//Caso o valor de reset não seja o mesmo do datasheet usar esta parte comentada
	// result8_t config_raw = i2c_read8(mpu.device, MPU_SMPRT_DIV);
	// config_reg = config_raw.value

	uint8_t smprt_reg = 0x00;

	smprt_reg |= mpu.config.Sample;

	return i2c_write8(mpu.device, MPU_SMPRT_DIV, smprt_reg);
}


// Função para enviar via i2c o valor do registrador de configuração geral
error_t MPU6050_config(MPU6050_t mpu) {

	//Caso o valor de reset não seja o mesmo do datasheet usar esta parte comentada
	// result8_t config_raw = i2c_read8(mpu.device, MPU_CONFIG);
	// config_reg = config_raw.value

	uint8_t config_reg = 0x00;

	config_reg |= mpu.config.FSyncEnable;
	config_reg |= mpu.config.LowPassFilter;

	return i2c_write8(mpu.device, MPU_CONFIG, config_reg);
}

// Função para enviar via i2c o valor do registrador de configuração do giroscópio
error_t MPU6050_gyro_config(MPU6050_t mpu) {

	//Caso o valor de reset não seja o mesmo do datasheet usar esta parte comentada
	//result8_t config_raw = i2c_read8(mpu.device, MPU_GYRO_CONFIG);
	//gyro_config_reg = config_raw.value

	uint8_t gyro_config_reg = 0x00;

	gyro_config_reg |= mpu.config.GyroRange;

	return i2c_write8(mpu.device, MPU_GYRO_CONFIG, gyro_config_reg);
}

// Função para enviar via i2c o valor do registrador de configuração do acelerômetro
error_t MPU6050_accel_config(MPU6050_t mpu) {

	//Caso o valor de reset não seja o mesmo do datasheet usar esta parte comentada
	//result8_t config_raw = i2c_read8(mpu.device, MPU_ACCEL_CONFIG);
	//accel_config_reg = config_raw.value

	uint8_t accel_config_reg = 0x00;

	accel_config_reg |= mpu.config.AccelRange;

	return i2c_write8(mpu.device, MPU_ACCEL_CONFIG, accel_config_reg);
}

error_t MPU6050_init(MPU6050_t mpu) {

	//Realiza todas as configurações em uma única função
	//para facilitar a execução do programa na main

	MPU6050_smprt(MPU6050_t mpu);
	MPU6050_config(MPU6050_t mpu);
	MPU6050_accel_config(MPU6050_t mpu);
	MPU6050_gyro_config(MPU6050_t mpu);

	return 0;
}






/* Leituras do sensor */











