#define aDIO P2_7
#define aSCK P4_2
#define aRCK P4_1
unsigned char t[10] = {
  0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
void setup() {
  pinMode(aDIO, OUTPUT); 
  pinMode(aSCK, OUTPUT); 
  pinMode(aRCK, OUTPUT);
  pinMode(P2_1, INPUT_PULLUP); 
  pinMode(P1_1, INPUT_PULLUP);
}
void out()
{
  digitalWrite(aRCK, 0);
  digitalWrite(aRCK, 1);
}
int i;
long last=0,now=0;
long a=0,b=20000101;
int yue[]={
  0,31,28,31,30,31,30,31,31,30,31,30,31};
int y,m,d;
int button = 1;
void loop() {
  now = millis();
  if(now-last>1000){
    last=now;
    b++;
  }
  y = b/10000;
  m = b/100%100;
  d = b%100;
  if((y%4==0&&y%100!=0)|(y%400==0))yue[2]=29;
  else yue[2]=28;
  if(d>yue[m]){
    b+=100;
    b-=d-1;
  }
  if(m>12){
    b+=10000;
    b-=1100;
  }

  if(!digitalRead(P1_1)){
    if(button){
      b+=100;
    }
    button=0;
  }

  if(!digitalRead(P2_1)){
    if(button){
      b+=10000;
    }
    button=0;
  }

  if(digitalRead(P1_1) && digitalRead(P2_1))button=1;

  i=0;
  a=b;
  while(a){
    shiftOut(aDIO, aSCK, MSBFIRST, 1 << (7-i));
    shiftOut(aDIO, aSCK, MSBFIRST, t[a%10]);
    out();
    a/=10;
    i++;
  }
  out();
}



