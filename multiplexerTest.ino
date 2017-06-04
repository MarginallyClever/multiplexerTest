//------------------------------------------------------------------------------
// mutliplexer dm74ls151n test
// dan@marginallyclever.com
// based on http://pdf1.alldatasheet.com/datasheet-pdf/view/8059/NSC/DM74LS151N.html
//------------------------------------------------------------------------------


int outputPins[8] = {2,3,4,5,6,7,8,9};  // goes to chip d0-d7
int controlPins[3] = {10,11,12};  // goes to chip a,b,c
int inputPin=13;  // from chip output y
// chip strobe pin 7 to Arduino gnd
// chip gnd to Arduino gnd
// chip vcc to Arduino 5v


//------------------------------------------------------------------------------


void setup() {
  Serial.begin(57600);
  Serial.println("**START**");

  int i;
  for(i=2;i<13;++i) {
    pinMode(i,OUTPUT);  // to data inputs and 
  }
  pinMode(13,INPUT);  // to multiplexer pin 5
}


void loop() {
  int i;
  for(i=0;i<8;++i) {
    setControl(i);
    tryAllOuptutPins();
  }
}


// set one control pins
void setControl(int i) {
  Serial.print(i,DEC);
  Serial.print('=');
  digitalWrite(controlPins[0],(i&0x1)?HIGH:LOW);
  digitalWrite(controlPins[1],(i&0x2)?HIGH:LOW);
  digitalWrite(controlPins[2],(i&0x4)?HIGH:LOW);
}


// set voltage high on one control pin at a time.
// report the state of the input pin with each trial.
void tryAllOuptutPins() {
  int i;
  for(i=0;i<8;++i) {
    digitalWrite(outputPins[i],HIGH);
    int state = digitalRead(inputPin);
    Serial.print(state,DEC);
    digitalWrite(outputPins[i],LOW);
  }
  Serial.println();
}

