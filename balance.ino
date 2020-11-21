#include "Wire.h"
const int MPU_ADDR = 0x68; // I2C address

int IN1 = 5;
int IN2 = 6;
int IN3 = 7;
int IN4 = 8;

int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data

void setup() {
    Serial.begin(9600);
    Wire.begin();
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x6B); 
    Wire.write(0); //wakes up mpu6050.
    Wire.endTransmission(true);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}

void loop() {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 7*2, true);
 
    gyro_y = Wire.read()<<8 | Wire.read(); 
    Serial.print(" | Y = "); Serial.print(gyro_y);
    Serial.println();

    if (gyro_y >= 1500) {
        naprej();
    } else if (gyro_y <= -1500) {
        nazaj();
    } else {
        prmer();
    }
}

void naprej() {
    digitalWrite(IN1,LOW);  // naprej [\]
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
}

void nazaj() {
    digitalWrite(IN1,HIGH);  // nazaj [/]
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
}

void prmer() {
    digitalWrite(IN1,LOW);  // PRMER [|]
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
}