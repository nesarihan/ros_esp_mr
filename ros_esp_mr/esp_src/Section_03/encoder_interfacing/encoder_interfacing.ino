#include <ros.h>
#include <std_msgs/Int16.h>

#define enc_r 1
#define enc_l 2

ros::NodeHandle  nh;

std_msgs::Int16 enc_r_msg;
std_msgs::Int16 enc_l_msg;
ros::Publisher enc_r_node("enc_r_values", &enc_r_msg);
ros::Publisher enc_l_node("enc_l_values", &enc_l_msg);


void setup(){
    nh.initNode();
    nh.advertise(enc_r_node);
    nh.advertise(enc_l_node);
    pin_definition();
}

void loop(){
    nh.spinOnce();

}

void pin_definition(){
    pinMode(enc_r, INPUT);
    pinMode(enc_l, INPUT);
    attachInterrupt(ditigalPinToInterrupt(enc_r), Update_encR, CHANGE);
    attachInterrupt(ditigalPinToInterrupt(enc_l), Update_encL, CHANGE);

}

void Update_encR(){

}

void Update_encL(){

}