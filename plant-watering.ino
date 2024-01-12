#define sensorPin A0
const int RED_PIN = 4;
const int GREEN_PIN = 5;
const int YELLOW_PIN = 6;
const int maxMoisture = 60; // in percent
const int minMoisture = 20; // in percent
const int PUMP_PIN = 8;
const int waterTime = 2;

class Led{
  private:
    byte pin;
  
  public:
    Led(byte pin) {
      this->pin = pin;
      init();
    }
    void init() {
      pinMode(pin, OUTPUT);
      off();
    }
    void on() {
      digitalWrite(pin, HIGH);
    }
    void off() {
      digitalWrite(pin, LOW);
    }
};

class Pump{
  private:
  byte pin;
  byte onTime;
  
  public:
  Pump(byte pin, byte onTime){
    this->pin = pin;
    this->onTime = onTime;
  };
  void init() {
    pinMode(pin, OUTPUT);
    off();
  }
  void on() {
    digitalWrite(pin, 1);
    delay(onTime * 1000); // convert to milliseconds
    this->off();
  }
  void off() {
   digitalWrite(pin, LOW);
  }
};

Led redLed(RED_PIN);
Led greenLed(GREEN_PIN);
Led yellowLed(YELLOW_PIN);
Pump waterPump(PUMP_PIN, waterTime);

void setup()
{
  Serial.begin(9600);
  pinMode(PUMP_PIN, OUTPUT);
}

void loop()
{
  
  int moisture = getMoisture();
  
  Serial.print("Analog output: ");
  Serial.println(moisture);

  if(moisture < minMoisture){
    Serial.println("PUMP On");        
    redLed.on();
    greenLed.off();
    yellowLed.off();
    waterPump.on();
  }

  if(moisture > minMoisture && moisture < maxMoisture){   
    redLed.off();
    greenLed.on();
    yellowLed.off();
    waterPump.off();
  }

  if(moisture > maxMoisture){    
    redLed.off();
    greenLed.off();
    yellowLed.on();
    waterPump.off();
  }
  
  delay(500);
}

int getMoisture(){
  int percentMoisture = (100-((analogRead(sensorPin) / 1023.00) * 100));
  return abs(percentMoisture-100);
}