#include <ros.h>
#include <std_msgs/Int16.h>
#include <geometry_msgs/Twist.h>

#define enc_r 1
#define enc_l 2
int count_r=0;
int count_l=0;
int val=175;
float left_wheel;
float right_wheel;

ros::NodeHandle  nh;

ros:ros::Subscriber <geometry_msgs::Twist> sub("/cmd_vel", &cmd_vel_to_pwm_cb);

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