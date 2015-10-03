//                            attiny85
//                      reset -+---+- power
//      (WheelSensorPin) pb3  -+*  +- pb2 (WriteSignalPin)
//                       pb4  -+   +- pb1 (WheelOutput1)
//                  ground    -+---+- pb0 (WheelOutput0)


///*
#define WheelOutput0 0   
#define WheelOutput1 1  
#define WriteSignalPin 2
#define WheelSensorPin 3


int WheelTickState= 0;
int OLDWheelTickState = 0;
int WheelTCount = 0; 
int OLDWheelTCount  = 0;

void setup()
{
  pinMode (WheelOutput0, OUTPUT);
  pinMode (WheelOutput1, OUTPUT);
  pinMode (WriteSignalPin, OUTPUT);
  pinMode (WheelSensorPin, INPUT);
}


void loop(){
	//check pin state
  if (analogRead(WheelSensorPin) >500) WheelTickState = 1;
  if (analogRead(WheelSensorPin) <150) WheelTickState = 0;

  if(WheelTickState != OLDWheelTickState) WheelTCount++;

  OLDWheelTickState = WheelTickState;

  // reset count 
	if(WheelTCount >3) WheelTCount = 0;

	//output binary
	int FirstBit = 0;
	int SecondBit = 0;
	
	if(WheelTCount == 1 || WheelTCount == 3 ) FirstBit = 1; 
	if(WheelTCount == 2 || WheelTCount == 3 ) SecondBit = 1;



	if(WheelTCount!=OLDWheelTCount){
		//signal bit is on while data is being changed on other ones, so Arduino doesnt read while information is being changed
		digitalWrite(WriteSignalPin, 1);

		digitalWrite(WheelOutput0, FirstBit);
		digitalWrite(WheelOutput1, SecondBit);
		
		digitalWrite(WriteSignalPin, 0);
	}


	OLDWheelTCount = WheelTCount;
}
