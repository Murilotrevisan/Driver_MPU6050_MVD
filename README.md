# Driver_MPU6050_MVD
Repositório para confecção do driver de funções mínimas para funcionamento da IMU MPU6050 a ser utilizada pelos projetos de baixo nível do Zenith.

## Exemplo

### SETUP:

* sem leitura de sinais externos
* filtro digital passa baixa de 260 Hz
* atualização dos dados em 4 Hz
* giroscópio com range máximo de 250°/s
* acelerômetro com range máximo de 2g

~~~C
//configurações a serem utilizadas no sensor
MPU6050_config_t config = {
    .FSyncEnable = MPU_FSYNC_DISABLE,
    .LowPassFilter = MPU_DLPF_CG0,
    .Sample = MPU_SMPRT_4,
    .GyroRange = MPU_GFS_SEL_250,
    .AccelRange = MPU_AFS_SEL_2
}

//configuração do i2c
//configurar o endereço de acordo com o utilizado no hardware 0x68 ou 0x69
i2c_device_t dev = {
    .i2c = &hi2c1,
    .adress = 0x68
}

MPU6050_t mpu = {
    .config = config,
    .device = dev
}

mpu6050_init(mpu);

MPU6050_values_t medida;
~~~

### MEDIDA

~~~C
MPU6050_measure(mpu, &medida);

printf("Acelerômetro x: %f\r\n", medida.AccelX);
printf("Acelerômetro y: %f\r\n", medida.AccelY);
printf("Acelerômetro z: %f\r\n", medida.AccelZ);

printf("Giroscópio x: %f\r\n", medida.GyroX);
printf("Giroscópio y: %f\r\n", medida.GyroY);
printf("Giroscópio z: %f\r\n", medida.GyroZ);

printf("Temperatura ambiente: %f\r\n", medida.Temp);
~~~