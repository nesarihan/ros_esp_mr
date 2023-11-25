/*
*/

#define motor_r_pwm 8
#define motor_r_a 4 
#define motor_r_b 5
#define motor_l_pwm 9
#define motor_l_a 6
#define motor_l_b 7
int val=175;
float left_wheel;
float right_wheel;


void setup() {
    Serial.begin(115200);
    pin_def();
    stop();
    Serial.println("Test running!");
    delay(2000);
}

void pin_def(){
    pinMode(motor_r_pwm, OUTPUT);
    pinMode(motor_r_a, OUTPUT);
    pinMode(motor_r_b, OUTPUT);
    pinMode(motor_l_pwm, OUTPUT);
    pinMode(motor_l_a, OUTPUT);
    pinMode(motor_l_b, OUTPUT);
}

void cmd_vel_to_pwm(float x, float z){
    left_wheel= (x-z)/2;
    right_wheel= (x+z)/2;
    direction();
    speed();
    if (x==0.0 & z==0.0){
        stop();
    }
    Serial.print(left_wheel); Serial.print(" / "); Serial.println(right_wheel);
}

void loop(){
    Serial.println("Forward");
    cmd_vel_to_pwm(0.5, 0.0);
    delay(2000);
    Serial.println("Backwards");
    cmd_vel_to_pwm(-0.5, 0.0);
    delay(2000);
    Serial.println("Left");
    cmd_vel_to_pwm(0.0, 1.0);
    delay(2000);
    Serial.println("Right");
    cmd_vel_to_pwm(0.0, -1.0);
    delay(2000);
}

void direction(){
    digitalWrite(motor_l_a, left_wheel > 0);
    digitalWrite(motor_l_b, left_wheel < 0);
    digitalWrite(motor_r_a, right_wheel > 0);
    digitalWrite(motor_r_b, right_wheel < 0);
}

void speed(){
    analogWrite(motor_r_pwm, val);
    analogWrite(motor_l_pwm, val);
}

void stop(){
    analogWrite(motor_r_pwm, 0);
    analogWrite(motor_l_pwm, 0);
}