#include<arduino.h>
#include<encoder.h>
//decoder testencoder(2000);

#define pin1 10    
#define pin2 9
#define LED 8
#define T_period 13
encoder testencoder(2000);

#define pin_1_LOW PORTB &= ~(1 << PB1)
#define pin_1_HIGH PORTB |= (1 << PB1)
#define pin_2_LOW PORTB &= ~(1 << PB2)
#define pin_2_HIGH PORTB |= (1 << PB2)


void pling(int8_t polarity, size_t periods);

void setup(){
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(LED, OUTPUT);
    pin_1_LOW;
    pin_2_LOW;
    Serial.begin(9600);
}
uint8_t testdata[] = {1, 2, 4};


void loop(){
    digitalWrite(LED, HIGH);
    testencoder.send_stream(testdata, sizeof(testdata));
    pling(1, 16);
    pin_1_LOW;
    pin_2_LOW;
    Serial.println("PLING");
    digitalWrite(LED, LOW);
    delay(500);
}




void pling(int8_t polarity, size_t periods){
  for (int i = 0; i < periods; i++)
  {
    switch (polarity)
    {
    case 1:
      pin_2_HIGH;
      pin_1_LOW;
      delayMicroseconds(T_period);
      pin_2_LOW;
      pin_1_HIGH;
      delayMicroseconds(T_period);
    break;
    case -1:
      pin_2_LOW;
      pin_1_HIGH;
      delayMicroseconds(T_period);
      pin_2_HIGH;
      pin_1_LOW;
      delayMicroseconds(T_period);
    break;
    case 0:
      pin_2_LOW;
      pin_1_LOW;
      delayMicroseconds(T_period);
      pin_2_LOW;
      pin_1_LOW;
      delayMicroseconds(T_period);
    break;
    default:
      break;
    }
  }
  
}
