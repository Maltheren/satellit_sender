#include<decoder.h>



uint8_t wait_for_change(){
    bool state_now = digitalRead(3);
    while(digitalRead(3) == state_now){
    }
    if(state_now){
        return FALLING;
    }
    else{
        return RISING;
    }
}


void decode_symbol(){
    uint32_t start = micros();
    int res = wait_for_change();
    

}

void handle_interrupt(){

    static int16_t score = 0;
    static uint32_t lastTime = 0;
    uint32_t t_now = micros();
    uint32_t delay = t_now - lastTime;
    if(delay > 420 && delay < 580){
        score++;
    }
    else{
        score -= 2;
        if(score < 0){
            score = 0;
        }

    }
    lastTime = t_now;
    if(score < 15){
        digitalWrite(7, LOW);
        return;
    }
    //så vi locked så vi begynder at kigge på offtider

    uint32_t lowpulse = 250;
    while(lowpulse > 200 && lowpulse < 300){

        lowpulse = pulseIn(3, LOW, 2000);

        if(lowpulse == 0){
            digitalWrite(7, HIGH); //vi er LOCKED Sir jeg dig
            delayMicroseconds(3000);
            
        }
    }

}

decoder::decoder(uint16_t baud_rate){
    this->baud_rate = baud_rate;
    DDRD |= (1<<pin);
    pinMode(7, OUTPUT);

    this->T = 1000000/baud_rate;
    this->T = this->T/2;
    this->T = this->T*2;//laver baudraten et tal vi kan dele i 2
    attachInterrupt(digitalPinToInterrupt(3), handle_interrupt,RISING);
}
