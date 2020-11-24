#include "Wire.h"
const int MPU_ADDR = 0x68; // I2C address

const int IN1 = 5;
const int IN2 = 6;
const int IN3 = 7;
const int IN4 = 8;
const int ENA = 9;
const int ENB = 10;

int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data

void setup()
{
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

void loop()
{
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 7 * 2, true);

    // int maxNaklon = 14000;         // maximum tilt
    // const int k = 255 / maxNaklon; // tilt koeficent
    // float speed = k * gyro_y;      // converting tilt to speed
    // int speedint = (int)speed;

    gyro_y = Wire.read() << 8 | Wire.read();
    Serial.print(" | Y = ");
    Serial.print(gyro_y);
    Serial.println();

    if (gyro_y >= -700)
    {
    naprej();
    int speed = 130;
    digitalWrite(ENA, speed);
    digitalWrite(ENB, speed);
    } else if (gyro_y >= -1500) {
    naprej();
    int speed = 150;
    digitalWrite(ENA, speed);
    digitalWrite(ENB, speed);
    } else if (gyro_y >= -2500) {
    naprej();
    int speed = 180;
    digitalWrite(ENA, speed);
    digitalWrite(ENB, speed);
    } else if (gyro_y >= -4000) {
    naprej();
    int speed = 200;
    digitalWrite(ENA, speed);
    digitalWrite(ENB, speed);
    } else if (gyro_y >= -5000) {
    naprej();
    int speed = 220;
    digitalWrite(ENA, speed);
    digitalWrite(ENB, speed);
    } else if (gyro_y >= -7000) {
    naprej();
    int speed = 250;
    digitalWrite(ENA, speed);
    digitalWrite(ENB, speed);
    }
    
    if (gyro_y <= 1200)
    {
    nazaj();
    int speed = 140;
    digitalWrite(ENA, speed);
    digitalWrite(ENB, speed);
    } else if (gyro_y <= 2000) {
    naprej();
    int speed = 150;
    digitalWrite(ENA, speed);
    digitalWrite(ENB, speed);
    } else if (gyro_y <= 3000) {
    naprej();
    int speed = 180;
    digitalWrite(ENA, speed);
    digitalWrite(ENB, speed);
    } else if (gyro_y <= 4500) {
    naprej();
    int speed = 200;
    digitalWrite(ENA, speed);
    digitalWrite(ENB, speed);
    } else if (gyro_y <= 5500) {
    naprej();
    int speed = 220;
    digitalWrite(ENA, speed);
    digitalWrite(ENB, speed);
    } else if (gyro_y <= 7500) {
    naprej();
    int speed = 250;
    digitalWrite(ENA, speed);
    digitalWrite(ENB, speed);
    }
    else
    {
        prmer();
    }
}

void naprej()
{
    digitalWrite(IN1, LOW); // naprej [\]
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    //digitalWrite(ENA, speedint);
    //digitalWrite(ENB, speedint);
}

void nazaj()
{
    digitalWrite(IN1, HIGH); // nazaj [/]
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    //digitalWrite(ENA, speedint);
    //digitalWrite(ENB, speedint);
}

void prmer()
{
    digitalWrite(IN1, LOW); // PRMER [|]
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(ENA, 0);
    digitalWrite(ENB, 0);
}