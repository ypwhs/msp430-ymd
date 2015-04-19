#define aDIO P2_7
#define aSCK P4_2
#define aRCK P4_1
unsigned char t[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
void setup() {
  pinMode(aDIO, OUTPUT); pinMode(aSCK, OUTPUT); pinMode(aRCK, OUTPUT);
}
void out()
{
  digitalWrite(aRCK, 0);
  digitalWrite(aRCK, 1);
}
long i;
void loop() {
  long a = millis();
  i=0;
  while(a){
    shiftOut(aDIO, aSCK, MSBFIRST, 1 << (7-i));
    shiftOut(aDIO, aSCK, MSBFIRST, t[a%10]);
    out();
    a/=10;
    i++;
  }
  out();
}
