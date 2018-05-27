#include<ros.h>
#include<std_msgs/Int32.h>

std_msgs::Int32 tick1,tick2;
ros::Publisher enc1("encoder1",&tick1);
ros::Publisher enc2("encoder2",&tick2);
ros::NodeHandle nh1;

const int enc1A=21; //Change for sign
const int enc1B=20;
const int enc2A=18;
const int enc2B=19;

int32_t pos1 = 0;
int32_t pos2 = 0;

void setup() {

  attachInterrupt(digitalPinToInterrupt(enc1A) , Achange , CHANGE);
  attachInterrupt(digitalPinToInterrupt(enc1B) , Bchange , CHANGE);
  attachInterrupt(digitalPinToInterrupt(enc2A) , Cchange , CHANGE);
  attachInterrupt(digitalPinToInterrupt(enc2B) , Dchange , CHANGE);

  nh1.initNode();
  nh1.advertise(enc1); 
  nh1.advertise(enc2);
}

void Achange()
{
  if(PIND & (1<<PD0))
  {
    if(!(PIND & (1<<PD1)))
    pos1++;
    else
    pos1--;
  }
  else
  {
    if(PIND & (1<<PD1))
    pos1++;
    else
    pos1--;
  }  
}

void Bchange()
{
  if(PIND & (1<<PD1))
  {
    if(PIND & (1<<PD0))
    pos1++;
    else
    pos1--;
  }
  else
  {
    if(!(PIND & (1<<PD0)))
    pos1++;
    else
    pos1--;
  }   
}
void Cchange()
{
  if(PIND & (1<<PD2))
  {
    if(!(PIND & (1<<PD3)))
    pos2++;
    else
    pos2--;
  }
  else
  {
    if(PIND & (1<<PD3))
    pos2++;
    else
    pos2--;
  }  
}

void Dchange()
{
  if(PIND & (1<<PD3))
  {
    if(PIND & (1<<PD2))
    pos2++;
    else
    pos2--;
  }
  else
  {
    if(!(PIND & (1<<PD2)))
    pos2++;
    else
    pos2--;
  }   
}
void loop()
{
  tick1.data = pos1;
  enc1.publish(&tick1);
  tick2.data = pos2;
  enc2.publish(&tick2);
  nh1.spinOnce();
}

