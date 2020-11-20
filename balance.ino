#include "Wire.h"
const int MPU_ADDR = 0x68; // I2C address

int IN1=5;
int IN2=6;
int IN3=7;
int IN4=8;

int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
    sprintf(tmp_str, "%6d", i);
    return tmp_str;
}

void setup() {
    Serial.begin(9600);
    Wire.begin();
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x6B); 
    Wire.write(0); //wakes up mpu6050
    Wire.endTransmission(true);
    for (int i = 5; i <9; i ++)
    {
    pinMode(i, OUTPUT);  
    }
}

void loop() {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 7*2, true);
 
    gyro_y = Wire.read()<<8 | Wire.read(); 
    Serial.print(" | Y = "); Serial.print(convert_int16_to_str(gyro_y));
    Serial.println();
}