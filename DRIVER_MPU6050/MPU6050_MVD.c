/*
 * MPU6050_MVD.c
 *
 *  Created on: Oct 19, 2021
 *      Author: Murilo Henrique Pasini Trevisan
 */


#include "MPU6050_MVD.h"

// Função para enviar via i2c o valor do registrador de configuração geral
error_t MPU6050_config(MPU6050_t mpu) {

	//Caso o valor de reset não seja o mesmo do datasheet usar esta parte comentada
	// result16_t config_raw = i2c_read16(mpu.device, MPU_CONFIG);
	// config_reg = config_raw.value

	uint8_t config_reg = 0x00;

	config_reg |= mpu.config.FSyncEnable;
	config_reg |= mpu.config.LowPassFilter;

	return i2c_write8(mpu.device, MPU_CONFIG, config_reg);
}

// Função para enviar via i2c o valor do registrador de configuração do giroscópio
error_t MPU6050_gyro_config(MPU6050_t mpu) {

	//Caso o valor de reset não seja o mesmo do datasheet usar esta parte comentada
	//result16_t config_raw = i2c_read8(mpu.device, MPU_GYRO_CONFIG);
	//gyro_config_reg = config_raw.value

	uint8_t gyro_config_reg = 0x00;

	gyro_config_reg |= mpu.GyroConfig.GyroRange;

	return i2c_write8(mpu.device, MPU_GYRO_CONFIG, gyro_config_reg);
}

// Função para enviar via i2c o valor do registrador de configuração do acelerômetro
error_t MPU6050_accel_config(MPU6050_t mpu) {

	//Caso o valor de reset não seja o mesmo do datasheet usar esta parte comentada
	//result16_t config_raw = i2c_read8(mpu.device, MPU_ACCEL_CONFIG);
	//accel_config_reg = config_raw.value

	uint8_t accel_config_reg = 0x00;

	accel_config_reg |= mpu.AccelConfig.AccelRange;

	return i2c_write8(mpu.device, MPU_ACCEL_CONFIG, accel_config_reg);
}














