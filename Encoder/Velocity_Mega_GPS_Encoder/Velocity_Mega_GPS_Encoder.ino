const int enc1A=21; //Change for sign
const int enc1B=20;
const int enc2A=18;
const int enc2B=19;
  
  double velocity1;
  int32_t pos1 = 0;
  int32_t lastpos1;
  
  double velocity2;
  int32_t pos2 = 0;
  int32_t lastpos2;
  
  String str,str1;
  double omega=0 , linear=0 , radius=0 , lengthbot=0.7112;
  void setup() {
    // put your setup code here, to run once:
  pinMode(enc2A,INPUT);
  pinMode(enc2B,INPUT);
  pinMode(enc1A,INPUT);
  pinMode(enc1B,INPUT);

Serial.begin(4800);
Serial2.begin(9600);

attachInterrupt(digitalPinToInterrupt(enc1A) , Achange , FALLING);
attachInterrupt(digitalPinToInterrupt(enc1B) , Bchange , FALLING);
attachInterrupt(digitalPinToInterrupt(enc2A) , Cchange , FALLING);
attachInterrupt(digitalPinToInterrupt(enc2B) , Dchange , FALLING);
  
  sei();
  TCCR1A  = 0;
  TCCR1B  = 0;
  TCNT1   = 0;
  OCR1A   = 6250;  //6250:- 0.1 , 12500 :- 0.2 , 250000 :- 0.4
  TCCR1B |=(1<<WGM12)|(1<<CS12);;
  TIMSK1 |=(1<<OCIE1A);
}
ISR(TIMER1_COMPA_vect)
{
  velocity1 = ((pos1-lastpos1)*0.00007603)/(0.1);    // Change according ticks
  lastpos1 = pos1; 
  velocity2 = ((pos2-lastpos2)*0.00007603)/(0.1);
  lastpos2 = pos2; 
  linear = (velocity1+velocity2)/2;
  omega = (velocity1-velocity2)/lengthbot;
  str = "O:" +String(omega)+","+String(linear)+","; 
  Serial.println(str);  // comment only when testing gps  */
 /* Serial.println(pos2);
  str = "O:" + String(pos1) + ',' + String(pos2);
  Serial.println(str); */
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

void loop() {
  // put your main code here, to run repeatedly:
if(Serial2.available()>0)
{
  str1 = Serial2.readStringUntil('\n');
}
if(str1.substring(1,6) == "GPGGA")
{
  str1 = "g:" + str1;
  Serial.println(str1);
}
  if(pos1>999999)
  pos1=0;
  if(pos1<-999999)
  pos1=0;
  if(pos2>999999)
  pos2=0;
  if(pos1<-999999)
  pos2=0;
}
