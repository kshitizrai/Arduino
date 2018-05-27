const int enc2A = 2 ;
const int enc2B = 3 ;
int pos2 = 0;;
int ppr = 20000 ;
int lastpos2 = -5;
int newpos2  = 0;
void setup() {
  // put your setup code here, to run once:
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

void loop() {
  // put your main code here, to run repeatedly:
newpos2 = pos2;
  if(newpos2!=lastpos2)
  { 
  Serial.print("Pos=");
  Serial.println(pos2);
  }
lastpos2=newpos2;
}
