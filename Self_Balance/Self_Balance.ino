#include<SoftwareSerial.h>
#include<PID_v1.h>
const int rxpin=2;
const int txpin=3;
const int M11 = 9;
const int M21 = 6;
const int M12 = 5;
const int M22 = 10;
const int ena = 7;
const int enb = 8;
char x ,  roll[5] , r=0;
int i=0;
double setpoint=0 , final1 =0;
float output , iterm=0 , dterm=0 , pterm=0 , timeinitial=0 , timeold=0 , errornew=0 , errorold=0;
double kp1=25 , ki1=0.0 , kd1=6;
double kp2=25 , ki2=0.0 , kd2=6; 
            //PID myPID(&final1 , &output , &setpoint , kp , ki , kd ,DIRECT);
SoftwareSerial myserial(rxpin,txpin);
//float thom=0;

void setup() {
  // put your setup code here, to run once:
myserial.begin(57600);
Serial.begin(57600);
pinMode(M11,OUTPUT);
pinMode(M12,OUTPUT);
pinMode(M22,OUTPUT);
pinMode(M21,OUTPUT);
pinMode(ena,OUTPUT);
pinMode(enb,OUTPUT);
digitalWrite(M11,HIGH);
//digitalWrite(BRKA,LOW);
//digitalWrite(BRKB,LOW);
}
void pidini()
{
 timeinitial = millis(); 
 errornew = final1-4.65;
 if(errornew>0)
 {
 iterm =ki1*(iterm + ((errornew-errorold)*(timeinitial-timeold))); 
 pterm = kp1*errornew;
 dterm = kd1*(errornew-errorold)/(timeinitial-timeold);
 timeold = timeinitial;
 if(iterm>10)
 iterm=0;
 output = iterm + pterm + dterm; 
 errorold=errornew;
 }
 if(errornew<0)
 {
 iterm =ki2*(iterm + ((errornew-errorold)*(timeinitial-timeold)));
 pterm = kp2*errornew;
 dterm = kd2*(errornew-errorold)/(timeinitial-timeold);
 timeold = timeinitial;
 if(iterm<10)
 iterm=0;
 output = iterm + pterm + dterm; 
 }
 //Serial.println(output);
 //output=-50;
 motor();
}
void motor()
{ 
  
  if(output > 255)
  output=255;
 if(output<-255)
  output=-255;
  if(output>=0)
  {
   // output=-output;
   // Serial.print("Ulta");
   // Serial.println(output);
    digitalWrite(ena,HIGH);
    digitalWrite(enb,HIGH);
    analogWrite(M12,LOW);
    analogWrite(M21,LOW);
    analogWrite(M11,int(output));
    analogWrite(M22,int(output));
    //delay(100);
  }
  else
  { 
 //   Serial.print("Seedha");
   // Serial.println(output);
   output=-output;
    digitalWrite(ena,HIGH);
    digitalWrite(enb,HIGH);
   analogWrite(M11,LOW);
    analogWrite(M22,LOW);
    analogWrite(M21,int(output));
    analogWrite(M12,int(output));
    //delay(100);
   }
  
  //output=0;
}
void loop() {
  // put your main code here, to run repeatedly:
 if(myserial.available())
 {
  //Serial.print("Available");
  x = myserial.read();
  if(x==',')
 {
  double temp = atof(roll);
  float n = float(temp);
// Serial.println(temp);
  if(r==0)
  {
    setpoint = n;
    r=1;
  }
  if(r==1)
  {
    final1 = n;
    if((final1-setpoint)>0.2 || (final1-setpoint)<-0.2)
    {
     //  thom=final1-setpoint;
      //Serial.println("HI");
      pidini(); 
    }
    else
    {
      digitalWrite(ena,LOW);
      digitalWrite(enb,LOW);
    }
  
  }
 // roll = 0;
  i=0;
 }
  else
  {
    roll[i]=x;
    i++;
  }
 }
}


