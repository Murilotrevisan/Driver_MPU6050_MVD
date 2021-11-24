# Driver_MPU6050_MVD
Repositório para confecção do driver de funções mínimas para funcionamento da IMU MPU6050 a ser utilizada pelos projetos de baixo nível do Zenith. As funções utilizadas de configuração foram a taxa de atualização dos registradores internos, frequência de corte do filtro passa baixa das leituras, range máximo do giroscópio, e do acelerêmetro.

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

MPU6050_init(mpu);

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

## Notas

* O range do giroscópio e do acelerômetro alteram a precisão da medida, caso seja necessário aumentar o range há queda da precisão da leitura, não há indicação no datasheet de quanto é a alteração da precisão com o aumento do range, investigar caso seja necessário maior precisão ou maior range de leitura, há informações de precisão que devem ser estudadas na página 12 do datasheet.
* O aumento da taxa de leitura ocasiona em maior consumo de energia no componente, no tópico 6 do datasheet há mais informações de consumo, porém, a variação de consumo do modo com menor taxa de atualização varia entre 10 uA até 150 uA.
* De acordo com o datasheet, o valor de reset de todos os registradores é 0x00 com exceção dos registradores de PWR_MGMT e WHO_AM_I.
* A partir do regustrador de PWR_MGMT é possível colocar a MPU em modo SLEEP e resetar a MPU, não está implementado neste driver, porém pode ser adicionado caso necessite dessas funções, além disso pode desabilitar o sensor de temperatura para redução de consumo caso já exista outra medição de temperatura externa.
* o datasheet encontra-se em [Datasheet geral](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf) e [mapa de registradores](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf).