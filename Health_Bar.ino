#define ADC_PIN 36
#define FREQUENCY 5000
#define RESOLUTION 12
#define PWM_PIN 22
#define GREEN 4
#define YELLOW 16
#define RED 17
#define BUTTON 22

int digital_value = 0;
int percent_value;
bool isPush = false;

void show_push();

void setup() {
  Serial.begin(115200);
  ledcSetup(0,FREQUENCY,RESOLUTION);
  ledcAttachPin(GREEN,0);
  ledcSetup(1,FREQUENCY,RESOLUTION);
  ledcAttachPin(YELLOW,1);
  ledcSetup(2,FREQUENCY,RESOLUTION);
  ledcAttachPin(RED,2);
  attachInterrupt(BUTTON, show_push, RISING);
}

void loop() {
  digital_value = analogRead(ADC_PIN);
  percent_value = map(digital_value, 0, 4095, 0, 100);
  
  if(percent_value <= 100 && percent_value >= 67)
  {
   ledcWrite(0,(percent_value-67)*4095/33);
   ledcWrite(1,0);
   ledcWrite(2,0);
  }
  
  else if(percent_value <= 66 && percent_value >= 34)
  {
   ledcWrite(0,0);
   ledcWrite(1,(percent_value-33)*4095/33);
   ledcWrite(2,0);
  }
  
  else if(percent_value <= 33 && percent_value >= 0)
  {
   ledcWrite(0,0);
   ledcWrite(1,0);
   ledcWrite(2,percent_value*4095/33);
  }

  if(isPush == true)
  {
    ledcWrite(0, 4095);
    ledcWrite(1, 4095);
    ledcWrite(2, 4095);
    delay(100);
    ledcWrite(0, 0);
    ledcWrite(1, 0);
    ledcWrite(2, 0);
    delay(100);
  }
  if(digital_value == 4095)
  {
    isPush = false;
  } 
  
  Serial.print("Digital Value: ");
  Serial.print(digital_value);
  Serial.print("\t");
  Serial.print("Percent Value: ");
  Serial.println(percent_value);
}

void show_push(){
  isPush = true;
}
