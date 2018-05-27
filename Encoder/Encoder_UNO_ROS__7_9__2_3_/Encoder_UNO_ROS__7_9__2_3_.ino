#include<ros.h>
#include<std_msgs/String.h>

std_msgs::String ticks;
String str1;
ros::Publisher pub("Encoder" , &ticks);
ros::NodeHandle nh1;

const int enc1A = 7;
const int enc1B = 9;
const int enc2A = 2 ;
const int enc2B = 3 ;

int32_t pos1 = 0;
int32_t ppr = 20000 ;

int32_t pos2 = 0;;

int len1;       
char buf1[50];

void setup() {
  // put your setup code here, to run once:
  cli();
  PCICR |= 0b00000101 ; // PortD and PortB
  PCMSK0 |= 1 << PB1 ; //Pin 9;
  PCMSK2 |= 1 << PD7 ; //Pin 7;
  sei();

  TCCR1A  = 0;
  TCCR1B  = 0;
  TCNT1   = 0;
  OCR1A   = 6250;
  TCCR1B |=(1<<WGM12)|(1<<CS12);;
  TIMSK1 |=(1<<OCIE1A);

  nh1.initNode();
  nh1.advertise(pub); 
  
  attachInterrupt(digitalPinToInterrupt(enc2A) , changeA , CHANGE);
  attachInterrupt(digitalPinToInterrupt(enc2B) , changeB , CHANGE);
}

ISR(TIMER1_COMPA_vect)
{
str1 = String(pos1) +"," + String(pos2)+","; 
len1 = str1.length();
str1.toCharArray(buf1,len1);
ticks.data=buf1;
pub.publish(&ticks);
}
void changeA()
{
  if(digitalRead(enc2B) == HIGH)
  {
    if(digitalRead(enc2A) == LOW)
    pos2++;
    else
    pos2--;
  }
  else
  {
    if(digitalRead(enc2A) == HIGH)
    pos2++;
    else
    pos2--;
  }  
}

void changeB()
{
  if(digitalRead(enc2B) == HIGH)
  {
    if(digitalRead(enc2A) == HIGH)
    pos2++;
    else
    pos2--;
  }
  else
  {
    if(digitalRead(enc2A) == LOW)
    pos2++;
    else
    pos2--;
  }   
}
ISR(PCINT0_vect)
{
  if(digitalRead(enc1B) == HIGH)
  {
    if(digitalRead(enc1A) == LOW)
    pos1++;
    else
    pos1--;
  }
  else
  {
    if(digitalRead(enc1A) == HIGH)
    pos1++;
    else
    pos1--;
  }  
}
ISR (PCINT2_vect)
{
  if(digitalRead(enc1B) == HIGH)
  {
    if(digitalRead(enc1A) == HIGH)
    pos1++;
    else
    pos1--;
  }
  else
  {
    if(digitalRead(enc1A) == LOW)
    pos1++;
    else
    pos1--;
  }   
}

void loop() {
  // put your main code here, to run repeatedly:
  nh1.spinOnce();
}
