#include "gyro.h"
#include "main.h"
#include "i2c.h"

static char header[] = "  No. xAccelData yAccelData zAccelData xGyroData  yGyroData  zGyroData  temperature\n";

// static short xyzAccelData[3] = {0};
// static short xyzGyroData[3] = {0};

extern float servoLoct[2];

static float xAccel = 0;
static float yAccel = 0;
static float zAccel = 0;

static float xGyro = 0;
static float yGyro = 0;
static float zGyro = 0;

float temperature = 0;

int16_t xAccelData = 0x0;
int16_t yAccelData = 0x0;
int16_t zAccelData = 0x0;

int16_t xGyroData = 0x0;
int16_t yGyroData = 0x0;
int16_t zGyroData = 0x0;

int16_t temperatureData = 0x0;

char xAccelOutput[8] = {0};
char yAccelOutput[8] = {0};
char zAccelOutput[8] = {0};

char xGyroOutput[8] = {0};
char yGyroOutput[8] = {0};
char zGyroOutput[8] = {0};

char temperatureOutput[8] = {0};

// static float pitch = 0;
// static float yaw = 0;
// static float roll = 0;

static int a = 0;

void gyroInit(void)
{
  uint8_t initData[5] = {0b00000000, 0b00000111, 0b11100000, 0b00000000, 0b00000110};
  a = MPU_I2C1_WRITE(MPU_ADDR_PWR_MGMT_1, initData);
  a = MPU_I2C1_WRITE(MPU_ADDR_SMPLRT_DIV, (initData + 1));
  a = MPU_I2C1_WRITE(MPU_ADDR_ACCEL_CONFIG, (initData + 3));  //set accel scale +/-2g
  a = MPU_I2C1_WRITE(MPU_ADDR_GYRO_CONFIG, (initData + 3));   //set gyro scale +/-250^o/s
  a = MPU_I2C1_WRITE(MPU_ADDR_CONFIG, (initData + 4));        //set filter width 5Hz and output 1kHz
  HAL_UART_Transmit(&huart2, (uint8_t*)header, sizeof(header), 0xff);
}

/*storage 6-axis data*/
void gyroGetData(void)
{
  xAccelData = MPUGetOneTermData(MPU_ADDR_ACCEL_XOUT_H, MPU_ADDR_ACCEL_XOUT_L);
  yAccelData = MPUGetOneTermData(MPU_ADDR_ACCEL_YOUT_H, MPU_ADDR_ACCEL_YOUT_L);
  zAccelData = MPUGetOneTermData(MPU_ADDR_ACCEL_ZOUT_H, MPU_ADDR_ACCEL_ZOUT_L);

  xGyroData = MPUGetOneTermData(MPU_ADDR_GYRO_XOUT_H, MPU_ADDR_GYRO_XOUT_L) + 310;
  yGyroData = MPUGetOneTermData(MPU_ADDR_GYRO_YOUT_H, MPU_ADDR_GYRO_YOUT_L) + 54;
  zGyroData = MPUGetOneTermData(MPU_ADDR_GYRO_ZOUT_H, MPU_ADDR_GYRO_ZOUT_L) + 54;

  temperatureData = MPUGetOneTermData(MPU_ADDR_TEMP_OUT_H, MPU_ADDR_TEMP_OUT_L);

  xAccel = xAccelData / 16384.0f;
  yAccel = yAccelData / 16384.0f;
  zAccel = zAccelData / 16384.0f;

  xGyro = xGyroData / 131.0f;
  yGyro = yGyroData / 131.0f;
  zGyro = zGyroData / 131.0f;

  temperature = temperatureData / 340.0f + 36.53f;

  my_sprintfloat(xAccelOutput, xAccel);
  my_sprintfloat(yAccelOutput, yAccel);
  my_sprintfloat(zAccelOutput, zAccel);

  my_sprintfloat(xGyroOutput, xGyro);
  my_sprintfloat(yGyroOutput, yGyro);
  my_sprintfloat(zGyroOutput, zGyro);

  my_sprintfloat(temperatureOutput, temperature);
}

/*Get one term in MPU6050*/
int16_t MPUGetOneTermData(uint8_t mpuAddrH, uint8_t mpuAddrL)
{
    uint8_t tempData8 = 0;
    int16_t tempData16 = 0;
    MPU_I2C1_READ(mpuAddrH, &tempData8);
    tempData16 = tempData8;
    MPU_I2C1_READ(mpuAddrL, &tempData8);
    tempData16 = (tempData16 << 8) | tempData8;
    return tempData16;
}


void my_sprintfloat(char* string, float data)
{
  if(data > 0)
  {
    uint16_t integralPart = ceil(data);
    uint16_t fractionalPart = ceil((data + 1 - integralPart) * 1000);
    sprintf(string, "+%d.%03d", integralPart - 1, fractionalPart);
  }
  else if(data < 0)
  {
    data = fabs(data);
    uint16_t integralPart = ceil(data);
    uint16_t fractionalPart = ceil((data + 1 - integralPart) * 1000);
    sprintf(string, "-%d.%03d", integralPart - 1, fractionalPart);
  }
  else
  {
    sprintf(string, "0.000");
  }
}

void gyroToServo(void)
{
  *(servoLoct + 0) += (xGyro * 0.02f) * 12.47f;
  *(servoLoct + 1) += (zGyro * 0.02f) * 12.47f;
 
}