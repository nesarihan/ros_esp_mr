

const int trig_pin = 2;
const int echo_pin = 4;


#define SPEED_OF_SOUND 0.034

long duration;
float distance_in_cm;

void setup(){
    pinMode(trig_pin, OUTPUT);
    pinMode(echo_pin, INPUT);
    Serial.begin(115200);
}


void loop(){
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);
    
    duration = pulseIn(echo_pin, HIGH);
    distance_in_cm = (duration* SPEED_OF_SOUND)/2;
    Serial.println(distance_in_cm);
}