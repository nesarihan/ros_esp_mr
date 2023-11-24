/*
*/

#include <ros.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle nh;

#define motor_r_pwm 8
#define motor_r_a 4 
#define motor_r_b 5
#define motor_l_pwm 9
#define motor_l_a 6
#define motor_l_b 7
int val=175;
float left_wheel;
float right_wheel;

void cmd_vel_to_pwm_cb (const geometry_msgs::Twist&velocity_msg){
    left_wheel= (velocity_msg.linear.x - velocity_msg.angular.z)/2;
    right_wheel= (velocity_msg.linear.x + velocity_msg.angular.z)/2;
    direction();
    speed();
    if (velocity_msg.linear.x==0.0 & velocity_msg.angular.z==0.0){
        stop();
    }
    //Serial.print(left_wheel); Serial.print(" / "); Serial.println(right_wheel);
}

ros:ros::Subscriber <geometry_msgs::Twist> sub("/cmd_vel", &cmd_vel_to_pwm_cb);


void setup() {
    //Serial.begin(115200);
    nh.initNode();
    nh.subscribe(sub);
    pin_def();
    stop();
    //Serial.println("Test running!");
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
    nh.spinOnce();
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