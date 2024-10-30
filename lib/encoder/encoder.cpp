#include<encoder.h>
#define setHIGH (PORTD |= (1<<2))
#define setLOW (PORTD &= ~(1<<2))



encoder::encoder(uint16_t baud_rate){
    this->baud_rate = baud_rate;
    DDRD |= (1<<pin);

    this->T = 1000000/baud_rate;
    this->T = this->T/2;
    this->T = this->T*2;//laver baudraten et tal vi kan dele i 2
}

void encoder::training_signal(){
    const int length = 32;
    uint32_t previous_micros = micros();
    int i = 0;
    bool state = 0;

    
    for (int i = 0; i < length; i++)
    {
        delayMicroseconds(T/2);
        setHIGH;
        delayMicroseconds(T/2);
        setLOW;
    }
}

void encoder::send_start_symbol(){
    uint16_t buffer = start_symbol;

    for (uint8_t i = 0; i < (sizeof(start_symbol)*8); i++) //kører 2 gange pr bit
    {
        
        if (buffer & 0x01 == 1){
            setHIGH;
            delayMicroseconds(T/2);
            setLOW;
            delayMicroseconds(T/2);
        }
        else{   
            setLOW;
            delayMicroseconds(T/2);
            setHIGH;
            delayMicroseconds(T/2);
        }
        buffer = buffer >> 1;
    }
}



void encoder::send_stream(uint8_t* buffer, size_t size){
    training_signal(); //vi skriver lige så AGC'en er klar 
    delayMicroseconds(2000);
    send_start_symbol();
    
    setLOW;
}