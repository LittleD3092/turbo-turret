#include <AccelStepper.h>
#include <Servo.h>

#define YAW_STEP_DIR 10 // CW+
#define YAW_STEP_PUL 12 // CLK+
#define YAW_STEP_INTERFACE 1
#define YAW_STEP_PER_REV 1600

// stepper motor
AccelStepper yawStep(YAW_STEP_INTERFACE, YAW_STEP_PUL, YAW_STEP_DIR);

// servo
Servo rightServo;
Servo leftServo;
#define RIGHT_SERVO_PIN 8
#define LEFT_SERVO_PIN 6

#define RIGHT_SERVO_MIN 100
#define RIGHT_SERVO_MAX 60

#define LEFT_SERVO_MIN 80
#define LEFT_SERVO_MAX 120

#define RIGHT_SERVO_CENTER 90
#define LEFT_SERVO_CENTER 90

#define RIGHT_SERVO_INCREMENT -5
#define LEFT_SERVO_INCREMENT 5

// check whether x is between min and max (inclusive)
// Precondition: x is the value to check, min and max are the bounds
// Postcondition: returns true if x is between min and max, false otherwise.
//                note that min can be greater than max, and the function
//                still works.
bool between(int x, int min, int max)
{
    if(min > max)
        return between(x, max, min);
    return x >= min && x <= max;
}

void setup()
{
    Serial.begin(9600);
    Serial.write("Arduino turned on\n");

    yawStep.setMaxSpeed(1000);
    yawStep.setAcceleration(500);
    Serial.write("Stepper motor initialized\n");

    rightServo.attach(RIGHT_SERVO_PIN);
    leftServo.attach(LEFT_SERVO_PIN);
    rightServo.write(RIGHT_SERVO_CENTER);
    leftServo.write(LEFT_SERVO_CENTER);
    Serial.write("Servo initialized\n");
}

void loop()
{
    // read serial
    String input = Serial.readStringUntil('\n');

    if(input != "")
        Serial.println("received: " + input);

    // ping command
    if(input == "ping")
    {
        Serial.println("pong");
    }

    // constant speed movement
    if(input == "runCW")
    {
        yawStep.setSpeed(-1000);
        Serial.println("running clockwise");
        while(input != "stop")
        {
            yawStep.runSpeed();
            if(Serial.available() > 0)
                input = Serial.readStringUntil('\n');
        }
        yawStep.stop();
        Serial.println("stopped");
    }
    else if(input == "runCCW")
    {
        yawStep.setSpeed(+1000);
        Serial.println("running counter-clockwise");
        while(input != "stop")
        {
            yawStep.runSpeed();
            if(Serial.available() > 0)
                input = Serial.readStringUntil('\n');
        }
        yawStep.stop();
        Serial.println("stopped");
    }

    // move to position
    if(String(input[0]) + String(input[1]) == "to")
    {
        // parse input for position
        char pos = input[2]; // + or -

        if(pos != '+' && pos != '-')
        {
            Serial.print("invalid position: ");
            Serial.println(pos);
            Serial.println("position must be + or -");
        }

        int steps = 0;
        for(int i = 3; i < input.length(); i++)
        {
            steps *= 10;
            steps += input[i] - '0';
        }
        if(pos == '-')
            steps *= -1;

        Serial.println("moving to position " + String(steps) + " steps...");

        // move to position
        yawStep.move(steps);
        yawStep.runToPosition();

        Serial.print("done");
    }

    // servo commands
    if(input == "rise" && 
       between(rightServo.read() + 
               RIGHT_SERVO_INCREMENT, 
               RIGHT_SERVO_MIN, RIGHT_SERVO_MAX) && 
       between(leftServo.read() + 
               LEFT_SERVO_INCREMENT, 
               LEFT_SERVO_MIN, LEFT_SERVO_MAX))
    {
        rightServo.write(rightServo.read() + RIGHT_SERVO_INCREMENT);
        leftServo.write(leftServo.read() + LEFT_SERVO_INCREMENT);
        Serial.println("servo raised");
    }

    if(input == "lower" && 
       between(rightServo.read() - 
               RIGHT_SERVO_INCREMENT, 
               RIGHT_SERVO_MIN, RIGHT_SERVO_MAX) && 
       between(leftServo.read() - 
               LEFT_SERVO_INCREMENT, 
               LEFT_SERVO_MIN, LEFT_SERVO_MAX))
    {
        rightServo.write(rightServo.read() - RIGHT_SERVO_INCREMENT);
        leftServo.write(leftServo.read() - LEFT_SERVO_INCREMENT);
        Serial.println("servo lowered");
    }

    // clear serial buffer
    while(Serial.available() > 0)
        Serial.read();

    delay(50);
}