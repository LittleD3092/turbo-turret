#include <AccelStepper.h>
#include <Servo.h>

#define YAW_STEP_DIR 10 // CW+
#define YAW_STEP_PUL 12 // CLK+
#define YAW_STEP_INTERFACE 1
#define YAW_STEP_PER_REV 1600

#define FIRING_STEP_DIR 8 // CW+
#define FIRING_STEP_PUL 9 // CLK+
#define FIRING_STEP_INTERFACE 1
#define FIRING_STEP_PER_REV 1600
#define FIRING_STEP_MAX_SPEED 4000
#define FIRING_STEP_ACCELERATION 4000

#define GENEVA_STEP_DIR A4 // CW+
#define GENEVA_STEP_PUL A5 // CLK+
#define GENEVA_STEP_INTERFACE 1
#define GENEVA_STEP_PER_REV 1600

#define PISTON_STEP_DIR 11 // CW+
#define PISTON_STEP_PUL 13 // CLK+
#define PISTON_STEP_INTERFACE 1
#define PISTON_STEP_PER_REV 1600
#define PISTON_STEP_MAX_SPEED 800
#define PISTON_STEP_ACCELERATION 500

// stepper motor
AccelStepper yawStep(YAW_STEP_INTERFACE, YAW_STEP_PUL, YAW_STEP_DIR);
AccelStepper genevaStep(GENEVA_STEP_INTERFACE, GENEVA_STEP_PUL, GENEVA_STEP_DIR);

// dc motor
#define CHASSIS_LEFT_DC_IN1 2
#define CHASSIS_LEFT_DC_IN2 4
#define CHASSIS_LEFT_DC_PWM 3
#define CHASSIS_LEFT_DC_MAX_SPEED 255
#define CHASSIS_LEFT_DC_INVERTED 0
#define CHASSIS_RIGHT_DC_IN1 7
#define CHASSIS_RIGHT_DC_IN2 5
#define CHASSIS_RIGHT_DC_PWM 6
#define CHASSIS_RIGHT_DC_MAX_SPEED 255
#define CHASSIS_RIGHT_DC_INVERTED 0

// global variables
int remainingAmmo = 3;

// classes
class Piston
{
public:
    Piston(int interface, int pul, int dir, int perRev, int maxSpeed, int acceleration)
    {
        stepper = AccelStepper(interface, pul, dir);
        stepper.setMaxSpeed(maxSpeed);
        stepper.setAcceleration(acceleration);
    }
    void moveForward()
    {
        stepper.move(PISTON_STEP_PER_REV * -0.44);
        stepper.runToPosition();
    }
    void moveBackward()
    {
        stepper.move(PISTON_STEP_PER_REV * 0.44);
        stepper.runToPosition();
    }
private:
    AccelStepper stepper;
};

class FireControl
{
public:
    FireControl(int interface, int pul, int dir, int perRev, int maxSpeed, int acceleration)
    {
        stepper = AccelStepper(interface, pul, dir);
        stepper.setMaxSpeed(maxSpeed);
        stepper.setAcceleration(acceleration);
    }

    void fire()
    {
        stepper.move(-FIRING_STEP_PER_REV * 0.5);
        stepper.runToPosition();
        stepper.move(FIRING_STEP_PER_REV * 0.55);
        stepper.runToPosition();
    }

private:
    AccelStepper stepper;
};

class DcMotor
{
public:
    DcMotor(int in1, int in2, int pwm)
    {
        this->in1 = in1;
        this->in2 = in2;
        this->pwm = pwm;
        pinMode(in1, OUTPUT);
        pinMode(in2, OUTPUT);
        pinMode(pwm, OUTPUT);
    }
    DcMotor()
    {
        this->in1 = 0;
        this->in2 = 0;
        this->pwm = 0;
    }
    void write(int speed)
    {
        if (speed > 0)
        {
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            analogWrite(pwm, speed);
        }
        else if (speed < 0)
        {
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            analogWrite(pwm, -speed);
        }
        else
        {
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
            analogWrite(pwm, 0);
        }
    }
private:
    int in1;
    int in2;
    int pwm;
};

class Chassis
{
public:
    Chassis(DcMotor leftMotor, int leftMaxSpeed, bool leftMotorInverted, DcMotor rightMotor, int rightMaxSpeed, bool rightMotorInverted)
    {
        this->leftMotor = leftMotor;
        this->leftMaxSpeed = leftMaxSpeed;
        this->leftMotorInverted = leftMotorInverted;
        this->rightMotor = rightMotor;
        this->rightMaxSpeed = rightMaxSpeed;
        this->rightMotorInverted = rightMotorInverted;
    }

    void move(int leftSpeed, int rightSpeed)
    {
        leftMotor.write(leftSpeed);
        rightMotor.write(rightSpeed);
    }

    void moveForward()
    {
        move(leftMaxSpeed, rightMaxSpeed);
    }

    void moveBackward()
    {
        move(-leftMaxSpeed, -rightMaxSpeed);
    }

    void turnLeft()
    {
        move(-leftMaxSpeed, rightMaxSpeed);
    }

    void turnRight()
    {
        move(leftMaxSpeed, -rightMaxSpeed);
    }

    void moveFrontLeft()
    {
        move(leftMaxSpeed / 2, rightMaxSpeed);
    }

    void moveFrontRight()
    {
        move(leftMaxSpeed, rightMaxSpeed / 2);
    }

    void moveBackLeft()
    {
        move(-leftMaxSpeed / 2, -rightMaxSpeed);
    }

    void moveBackRight()
    {
        move(-leftMaxSpeed, -rightMaxSpeed / 2);
    }

    void stop()
    {
        move(0, 0);
    }

private:
    DcMotor leftMotor;
    DcMotor rightMotor;
    bool leftMotorInverted;
    bool rightMotorInverted;
    int leftMaxSpeed;
    int rightMaxSpeed;
};

Piston piston(PISTON_STEP_INTERFACE, PISTON_STEP_PUL, PISTON_STEP_DIR, PISTON_STEP_PER_REV, PISTON_STEP_MAX_SPEED, PISTON_STEP_ACCELERATION);
Chassis chassis(
    DcMotor(
        CHASSIS_LEFT_DC_IN1, CHASSIS_LEFT_DC_IN2, CHASSIS_LEFT_DC_PWM
    ), 
    CHASSIS_LEFT_DC_MAX_SPEED, 
    CHASSIS_LEFT_DC_INVERTED, 
    DcMotor(
        CHASSIS_RIGHT_DC_IN1, 
        CHASSIS_RIGHT_DC_IN2, 
        CHASSIS_RIGHT_DC_PWM
    ), 
    CHASSIS_RIGHT_DC_MAX_SPEED, 
    CHASSIS_RIGHT_DC_INVERTED
);
FireControl fireControl(FIRING_STEP_INTERFACE, FIRING_STEP_PUL, FIRING_STEP_DIR, FIRING_STEP_PER_REV, FIRING_STEP_MAX_SPEED, FIRING_STEP_ACCELERATION);

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
    genevaStep.setMaxSpeed(1000);
    genevaStep.setAcceleration(500);
    Serial.write("Stepper motor initialized\n");
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
        yawStep.setSpeed(+1000);
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
        yawStep.setSpeed(-1000);
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
        yawStep.move(-steps);
        yawStep.runToPosition();

        Serial.print("done");
    }

    // if(input == "fire" && remainingAmmo > 0)
    // {
    //     remainingAmmo--;

    //     // piston forward
    //     piston.moveForward();
    //     // fire
    //     fireControl.fire();
    //     // piston back
    //     piston.moveBackward();

    //     if(remainingAmmo != 0)
    //     {
    //         // reload
    //         genevaStep.move(GENEVA_STEP_PER_REV * 2.4);
    //         genevaStep.runToPosition();
    //     }

    //     Serial.println("fired");
    // }
    // else if(input == "fire" && remainingAmmo == 0)
    // {
    //     Serial.println("out of ammo");
    // }

    if(input == "reset" && remainingAmmo < 3)
    {
        remainingAmmo++;

        // reset
        genevaStep.move(-GENEVA_STEP_PER_REV * 2.4);
        genevaStep.runToPosition();

        Serial.println("reset");
    }
    else if(input == "reset" && remainingAmmo == 3)
    {
        Serial.println("already at max ammo");
    }

    if(input == "force reset")
    {
        remainingAmmo++;
        if(remainingAmmo > 3)
            remainingAmmo = 3;

        // reset
        genevaStep.move(-GENEVA_STEP_PER_REV * 2.4);
        genevaStep.runToPosition();

        Serial.println("force reset");
    }

    if(input == "piston test")
    {
        piston.moveForward();
        piston.moveBackward();
        Serial.println("piston test done");
    }

    if(input == "piston backward")
    {
        piston.moveBackward();
        Serial.println("piston moved backward");
    }

    if(input == "fire")
    {
        // fire
        fireControl.fire();
        Serial.println("fired");
    }

    if(input == "move forward")         chassis.moveForward();
    else if(input == "move backward")   chassis.moveBackward();
    else if(input == "turn left")       chassis.turnLeft();
    else if(input == "turn right")      chassis.turnRight();
    else if(input == "move front left") chassis.moveFrontLeft();
    else if(input == "move front right")chassis.moveFrontRight();
    else if(input == "move back left")  chassis.moveBackLeft();
    else if(input == "move back right") chassis.moveBackRight();
    else if(input == "stop")            chassis.stop();

    // clear serial buffer
    while(Serial.available() > 0)
        Serial.read();

    delay(50);
}