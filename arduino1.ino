const int rango = 15;
int luzDimmer = A0;
int lightBit = 5;
float valorActualLuzDimmer = 0;
float valorLuzDimmer = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(lightBit, OUTPUT ) ;
  pinMode(luzDimmer, INPUT ) ;
}

void loop() {
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
    float escribir = (valorActualLuzDimmer/1023)*45 + 210;
    analogWrite(lightBit, escribir);
    delay(200);
    analogWrite(lightBit, 0);
  }
}
