class Motor
{
public:
    Motor(int param_in1, int param_in2, int param_pwm, bool param_invert = false) : 
        in1(param_in1), in2(param_in2), pwm(param_pwm), invert(param_invert)
    {
        pinMode(in1, OUTPUT);
        pinMode(in2, OUTPUT);
        pinMode(pwm, OUTPUT);
    }

    Motor() : Motor(0, 0, 0)
    {}

    void write(int value)
    {
        if(invert) value = -value;

        if (value > 0)
        {
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
        }
        else if (value < 0)
        {
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
        }
        else
        {
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
        }

        analogWrite(pwm, abs(value));
    }

private:
    int in1;
    int in2;
    int pwm;
    bool invert;
};

class Piston
{
public:
    Piston(Motor param_leftMotor, Motor param_rightMotor) : 
        leftMotor(param_leftMotor), rightMotor(param_rightMotor)
    {}

    Piston() : Piston(Motor(), Motor())
    {}

    void write(int value)
    {
        leftMotor.write(value);
        rightMotor.write(value);
    }

private:
    Motor leftMotor;
    Motor rightMotor;
};

Piston piston(Motor(3, 4, 5), Motor(7, 8, 9));

void setup()
{
    Serial.begin(9600);
    Serial.println("Piston test started");
}

void loop()
{
    String input = Serial.readStringUntil('\n');
    if (input.length() > 0)
    {
        int value = input.toInt();
        Serial.print("Setting piston speed to ");
        Serial.println(value);
        piston.write(value);
    }

    delay(100);
}