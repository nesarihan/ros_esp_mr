/*
*/

#define motor_r_pwm
#define motor_r_a
#define motor_r_b
#define motor_l_pwm
#define motor_l_a
#define motor_l_b



void setup() {
    Serial.begin(115200);
}

void pin_def(){

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
}

void move_backward(){
    Serial.println("Moving Backwards");
}

void move_left(){
    Serial.println("Moving Left");
}

void move_right(){
    Serial.println("Moving Right");
}