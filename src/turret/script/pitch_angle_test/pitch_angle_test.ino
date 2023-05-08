// a servo testing program for the turret
// include two servos

#include <Servo.h>

Servo rightServo;
Servo leftServo;

#define RIGHT_SERVO_PIN 8
#define LEFT_SERVO_PIN 6

#define RIGHT_SERVO_MIN 180
#define RIGHT_SERVO_MAX 0

#define LEFT_SERVO_MIN 0
#define LEFT_SERVO_MAX 180

#define RIGHT_SERVO_CENTER 90
#define LEFT_SERVO_CENTER 90

#define RIGHT_SERVO_INCREMENT 5
#define LEFT_SERVO_INCREMENT 5

#include <string.h>

void setup() {
    // put your setup code here, to run once:
    rightServo.attach(RIGHT_SERVO_PIN);
    leftServo.attach(LEFT_SERVO_PIN);
    // rightServo.write(RIGHT_SERVO_CENTER);
    // leftServo.write(LEFT_SERVO_CENTER);

    rightServo.write(RIGHT_SERVO_CENTER);
    leftServo.write(LEFT_SERVO_CENTER);

    Serial.begin(9600);
    Serial.println("Setup complete");
}

void loop()
{
    String input = Serial.readStringUntil('\n');
    if(input[0] == 'r')
    {
        int angle = abs(input.substring(1).toInt() - RIGHT_SERVO_MIN);
        rightServo.write(angle);
    }
    else if(input[0] == 'l')
    {
        int angle = abs(input.substring(1).toInt() - LEFT_SERVO_MIN);
        leftServo.write(angle);
    }
    else if(input[0] == 'a')
    {
        int rightAngle = abs(input.substring(1).toInt() - RIGHT_SERVO_MIN);
        int leftAngle = abs(input.substring(1).toInt() - LEFT_SERVO_MIN);
        rightServo.write(rightAngle);
        leftServo.write(leftAngle);
    }
}