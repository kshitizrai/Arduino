const int enc1A=21;
const int enc1B=20;
const int enc2A=19;
const int enc2B=18;

const int dig1=2 ;
const int dig2=3; 
const int an1=4 ;
const int an2=5 ;

int pwm1=0 , pwm2=0 ,vel1=0 ,vel2=0 , flag=0;

double velocity1;
int32_t pos1 = 0;
int32_t lastpos1;

double velocity2;
int32_t pos2 = 0;
int32_t lastpos2;

String str,str1;
double omega=0 , linear=0 , radius=0 , lengthbot=0.6919;
void setup() {
  // put your setup code here, to run once:
pinMode(enc2A,INPUT);
pinMode(enc2B,INPUT);
pinMode(enc1A,INPUT);
pinMode(enc1B,INPUT);

pinMode(dig1,OUTPUT);
pinMode(dig2,OUTPUT);
pinMode(an1,OUTPUT);
pinMode(an2,OUTPUT);

Serial.begin(9600);

attachInterrupt(digitalPinToInterrupt(enc1A) , Achange , CHANGE);
attachInterrupt(digitalPinToInterrupt(enc1B) , Bchange , CHANGE);
attachInterrupt(digitalPinToInterrupt(enc2A) , Cchange , CHANGE);
attachInterrupt(digitalPinToInterrupt(enc2B) , Dchange , CHANGE);
  
  sei();
  TCCR1A  = 0;
  TCCR1B  = 0;
  TCNT1   = 0;
  OCR1A   = 6250;
  TCCR1B |=(1<<WGM12)|(1<<CS12);;
  TIMSK1 |=(1<<OCIE1A);
  Serial2.begin(9600);
  analogWrite(dig1,0);
  analogWrite(an1,0);
  analogWrite(dig2,0);
  analogWrite(an2,0); 
}
ISR(TIMER1_COMPA_vect)
{
  velocity1 = ((pos1-lastpos1)*0.00004325/(0.1));
  lastpos1 = pos1; 
  velocity2 = ((pos2-lastpos2)*0.00004325)/(0.1);
  lastpos2 = pos2; 
  linear = (velocity1+velocity2)/2;
  omega = (velocity1-velocity2)/lengthbot;
  if(velocity1==velocity2)
  radius=0;
  else
  radius = 0.500*lengthbot*((velocity1+velocity2)/(velocity1-velocity2));
  str = "O:" +String(omega)+","+String(radius)+","+String(linear)+",";
}
void Achange()
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

void Bchange()
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
void Cchange()
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

void Dchange()
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

void motordriver(int pwm1,int pwm2)
{
if(pwm1>=0)
  {
   // Serial.println("M1 Backward");
    analogWrite(dig1,0);
    analogWrite(an1,pwm1);
  }
  else
  {
   // Serial.println("M1 Forward");
    analogWrite(dig1,255);
    analogWrite(an1,-pwm1);    
  }
  
if(pwm2>=0)
  {
   // Serial.println("M2 Backward");
    analogWrite(dig2,0);
    analogWrite(an2,pwm2);
  }
  else
  {
   // Serial.println("M2 Forward");
    analogWrite(dig2,255);
    analogWrite(an2,-pwm2);    
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()>0)
  {
  if(flag==0)
  {
    vel1 = Serial.readStringUntil(',').toInt();
    flag=1;
  }
  if(flag==1)
  {
    vel2 = Serial.readStringUntil(',').toInt();
    flag=0;
  }
  }
  pwm1 = map(vel1,-2789,2789,-255,255);
  pwm2 = map(vel2,-2789,2789,-255,255);
  motordriver(pwm1,pwm2); 
if(Serial2.available()>0)
{
  str1 = Serial2.readStringUntil('\n');
}
if(str1.substring(1,6) == "GPGGA")
{
  str1="g:"+str1;
}
else
{
  str1="g:"; 
}
Serial.println(str1);
Serial.println(str);
}
