const int enc1A = 7;
const int enc1B = 9;
const int enc2A = 2 ;
const int enc2B = 3 ;

int pos1 = 0;
int ppr = 20000 ;
int lastpos1 = -5;
int newpos1  = 0;

int pos2 = 0;;
int lastpos2 = -5;
int newpos2  = 0;
void setup() {
  // put your setup code here, to run once:
  cli();
  PCICR |= 0b00000101 ; // PortD and PortB
  PCMSK0 |= 1 << PB1 ; //Pin 9;
  PCMSK2 |= 1 << PD7 ; //Pin 7;
  sei();
  Serial.begin(9600); 
  attachInterrupt(digitalPinToInterrupt(enc2A) , changeA , CHANGE);
  attachInterrupt(digitalPinToInterrupt(enc2B) , changeB , CHANGE);
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
newpos1 = pos1;
  if(newpos1!=lastpos1)
  { 
  Serial.print("Pos1=");
  Serial.println(pos1);
  }
lastpos1=newpos1;

newpos2 = pos2;
  if(newpos2!=lastpos2)
  { 
  //Serial.print("Pos=");
  //Serial.println(pos2);
  }
lastpos2=newpos2;
}
