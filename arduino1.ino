const int rango = 15;
const int luzDimmer = A0;
const int soundSensor = A1;
const int lightBit = 5;

float valorActualLuzDimmer = 0;
float valorLuzDimmer = 0;
bool soundSensorOn = false;
bool lockSensor = false;


void setup() {
  // put your setup code here, to run once:
  pinMode(lightBit, OUTPUT ) ;
  pinMode(luzDimmer, INPUT ) ;
  pinMode(soundSensor, INPUT ) ;
}

void loop() {
  
  if (sensorChanged()) cambiarLuzSensor();
  if (cambioLuzDimmer()) cambiarLuzDimmer();
}

bool cambioLuzDimmer()
{
  valorLuzDimmer = analogRead(luzDimmer);
  return (valorActualLuzDimmer > valorLuzDimmer + rango || valorActualLuzDimmer < valorLuzDimmer - rango);
}

void cambiarLuzDimmer()
{
  delay(200);
  if (cambioLuzDimmer()) {
    valorActualLuzDimmer = valorLuzDimmer;
    writeBit(lightBit, calculateDimmerBitOutput());
  }
}

bool sensorChanged()
{
  if (!lockSensor)
  {
    int valorSensor = analogRead(soundSensor);  
    if (valorSensor>500) {
      lockSensor = true;
      return true;
    }      
  }
  return false;
}

void cambiarLuzSensor()
{
  if (soundSensorOn) writeBit(lightBit, 200);
  else writeBit(lightBit, calculateDimmerBitOutput());
  soundSensorOn = !soundSensorOn; 
  delay(3000);
  lockSensor = false;
}

int calculateDimmerBitOutput()
{
  return (valorActualLuzDimmer/1023)*45 + 210;
}

void writeBit(int cloudbit, int value)
{
  analogWrite(cloudbit, value); 
  delay(200);
  analogWrite(cloudbit, 0);  
}
