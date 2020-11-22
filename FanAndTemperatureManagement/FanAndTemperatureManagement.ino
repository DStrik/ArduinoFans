  // Fan control
const int PWM = 3; 
  // Thermometer
const int sensor = A0; 
  // RBG LED lights
const int RED = 9;
const int GREEN = 10;
const int BLUE = 11;
  // Read from the sensor and convert volts to celcius
int sensorVal = 0;
float volts;
float celcius;
bool cooling = false;

void setup() {
  // To format the thermometer correctly
  Serial.begin(9600);
  // Declaring all the output pins
  pinMode(PWM, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  // Setting blue to default
  analogWrite(BLUE, 255);
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
}

void loop(){
  // Read from thermometer and convert volts to celcius
  sensorVal = analogRead(sensor);
  volts = sensorVal * 5;
  volts /= 1023.0;
  celcius = (volts - 0.5) * 100; 
  // Print to serial monitor
  Serial.print("Celcius = ");
  Serial.print(celcius);
  Serial.println();
  // These if statements control the fan speed and color of the lights 
  // according to the temperatures.
  if(celcius < 30 && !cooling){
    // Fan off
    analogWrite(PWM, 0);
    // Lights red
    analogWrite(BLUE, 255);
    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
  }else {
    cooling = true;
    // Fanpower maximum
    analogWrite(PWM, 255);
    // Lights red
    analogWrite(BLUE, 0);
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
  }
  
  // if the temperature has reached 26 then cooling is done
  if(celcius <= 26) { cooling = false; }
  // 5 second delay between readings of the temperature
  delay(5000);
}
