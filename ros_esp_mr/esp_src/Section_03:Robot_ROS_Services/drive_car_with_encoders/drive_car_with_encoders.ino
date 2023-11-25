#include <ros.h>
#include <std_msgs/Int16.h>
#include <geometry_msgs/Twist.h>

#define enc_r 1
#define enc_l 2
#define motor_r_pwm 8
#define motor_r_a 4 
#define motor_r_b 5
#define motor_l_pwm 9
#define motor_l_a 6
#define motor_l_b 7
int count_r=0;
int count_l=0;
int val=175;
float left_wheel;
float right_wheel;

ros::NodeHandle  nh;
void cmd_vel_to_pwm_cb (const geometry_msgs::Twist&velocity_msg);
ros::Subscriber <geometry_msgs::Twist> sub("/cmd_vel", &cmd_vel_to_pwm_cb);

std_msgs::Int16 enc_r_msg;
std_msgs::Int16 enc_l_msg;
ros::Publisher enc_r_node("enc_r_values", &enc_r_msg);
ros::Publisher enc_l_node("enc_l_values", &enc_l_msg);


void setup(){
    nh.initNode();
    nh.subscribe(sub);
    nh.advertise(enc_r_node);
    nh.advertise(enc_l_node);
    pin_definition();
    
}

void loop(){
    enc_r_node.publish(&enc_r_msg);
    enc_l_node.publish(&enc_l_msg);
    nh.spinOnce();

}

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

void pin_definition(){
    pinMode(motor_r_pwm, OUTPUT);
    pinMode(motor_r_a, OUTPUT);
    pinMode(motor_r_b, OUTPUT);
    pinMode(motor_l_pwm, OUTPUT);
    pinMode(motor_l_a, OUTPUT);
    pinMode(motor_l_b, OUTPUT);
    pinMode(enc_r, INPUT);
    pinMode(enc_l, INPUT);
    attachInterrupt(digitalPinToInterrupt(enc_r), Update_encR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(enc_l), Update_encL, CHANGE);

}

void Update_encR(){
    enc_r_msg.data=count_r ++;
}

void Update_encL(){
    enc_l_msg.data=count_l ++;
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
