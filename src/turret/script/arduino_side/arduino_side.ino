#include <AccelStepper.h>

#define YAW_STEP_DIR 8
#define YAW_STEP_PUL 9
#define YAW_STEP_INTERFACE 1
#define YAW_STEP_PER_REV 1600

// stepper motor
AccelStepper yawStep(YAW_STEP_INTERFACE, YAW_STEP_PUL, YAW_STEP_DIR);

void setup()
{
    Serial.begin(9600);
    Serial.write("Arduino turned on\n");

    yawStep.setMaxSpeed(1000);
    yawStep.setAcceleration(500);

    Serial.write("Stepper motor initialized\n");
}

void loop()
{
    // read serial
    String input;
    while(Serial.available() > 0)
    {
        String buf = Serial.readString();
        input += buf;
    }
    input = input.substring(0, input.length() - 1);

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
        yawStep.setSpeed(1000);
        Serial.println("running clockwise");
        while(input != "stop")
        {
            yawStep.runSpeed();
            input = "";
            while(Serial.available() > 0)
            {
                String buf = Serial.readString();
                input += buf;
            }
            input = input.substring(0, input.length() - 1);
        }
        yawStep.stop();
        Serial.println("stopped");
    }
    else if(input == "runCWW")
    {
        yawStep.setSpeed(-1000);
        Serial.println("running counter-clockwise");
        while(input != "stop")
        {
            yawStep.runSpeed();
            input = "";
            while(Serial.available() > 0)
            {
                String buf = Serial.readString();
                input += buf;
            }
            input = input.substring(0, input.length() - 1);
        }
        yawStep.stop();
        Serial.println("stopped");
    }

    // move to position
    if(String(input[0]) + String(input[1]) == "to")
    {
        // parse input for position
        char pos = input[2]; // + or -
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

    delay(1);
}