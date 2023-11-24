/*
*/

#define motor_r_pwm 8
#define motor_r_a 4 
#define motor_r_b 5
#define motor_l_pwm 9
#define motor_l_a 6
#define motor_l_b 7
int val=175;


void setup() {
    Serial.begin(115200);
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

void loop(){
    move_forward();
    delay(1000);
    move_backward();
    delay(1000);
    move_left();
    delay(1000);
    move_right();
    delay(1000);
}

void move_forward(){
    Serial.println("Moving Forward");

    digitalWrite(motor_r_a, HIGH);
    digitalWrite(motor_r_b, LOW);
    digitalWrite(motor_l_a, HIGH);
    digitalWrite(motor_l_b, LOW);
    analogWrite(motor_r_pwm, val);
    analogWrite(motor_l_pwm, val);

}

void move_backward(){
    Serial.println("Moving Backwards");

    digitalWrite(motor_r_a, LOW);
    digitalWrite(motor_r_b, HIGH);
    digitalWrite(motor_l_a, LOW);
    digitalWrite(motor_l_b, HIGH);
    analogWrite(motor_r_pwm, val);
    analogWrite(motor_l_pwm, val);
}

void move_left(){
    Serial.println("Moving Left");
    digitalWrite(motor_r_a, HIGH);
    digitalWrite(motor_r_b, LOW);
    digitalWrite(motor_l_a, LOW);
    digitalWrite(motor_l_b, LOW);
    analogWrite(motor_r_pwm, val);
    analogWrite(motor_l_pwm, 0);
}

void move_right(){
    Serial.println("Moving Right");
    
    digitalWrite(motor_r_a, LOW);
    digitalWrite(motor_r_b, LOW);
    digitalWrite(motor_l_a, HIGH);
    digitalWrite(motor_l_b, LOW);
    analogWrite(motor_r_pwm, 0);
    analogWrite(motor_l_pwm, val);
}
void stop(){
    analogWrite(motor_r_pwm, 0);
    analogWrite(motor_l_pwm, 0);
}