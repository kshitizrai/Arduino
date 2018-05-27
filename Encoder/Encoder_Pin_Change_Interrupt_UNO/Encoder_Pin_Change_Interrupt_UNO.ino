const int enc2A = 7;
const int enc2B = 9;
int pos = 0;
int rev = 0;
int ppr = 20000 ;
int lastpos = -5;
int newpos  = 0;
void setup() {
  // put your setup code here, to run once:
  cli();
  PCICR |= 0b00000101 ; // PortD and PortB
  PCMSK0 |= 1 << PB1 ; //Pin 9;
  PCMSK2 |= 1 << PD7 ; //Pin 7;
  sei();
  Serial.begin(9600); 
}

ISR(PCINT0_vect)
{
  if(digitalRead(enc2B) == HIGH)
  {
    if(digitalRead(enc2A) == LOW)
    pos++;
    else
    pos--;
  }
  else
  {
    if(digitalRead(enc2A) == HIGH)
    pos++;
    else
    pos--;
  }  
}
ISR (PCINT2_vect)
{
  if(digitalRead(enc2B) == HIGH)
  {
    if(digitalRead(enc2A) == HIGH)
    pos++;
    else
    pos--;
  }
  else
  {
    if(digitalRead(enc2A) == LOW)
    pos++;
    else
    pos--;
  }   
}

void loop() {
  // put your main code here, to run repeatedly:
newpos = pos;
  if(newpos!=lastpos)
  { 
  Serial.print("Pos=");
  Serial.println(pos);
  }
lastpos=newpos;
}
