#include "stdio.h"
#define set_tc3400_clk DDRD |= 0b00010000
#define set_tc3400_data DDRD &= 0b11011111
#define tc_clkh PORTD |= 0b00010000
#define tc_clkl PORTD &= 0b11101111
#define tc_data PIND & 0b00100000
#define tc_delay _delay_us(5)
#define SET_SUPPLY DDRD |= 0b01000000
#define SUPPLY_ON PORTD |= 0b01000000
#define SUPPLY_OFF PORTD &= 0b10111111
int tc_read(void){
 int data=0;
 SET_SUPPLY;
 set_tc3400_clk;
 set_tc3400_data;
 tc_clkl;
 SUPPLY_OFF;
 _delay_ms(50);
 tc_clkh;
 SUPPLY_ON;
 _delay_ms(50);
 tc_delay;
 tc_clkl;
 tc_delay;
 tc_clkh;
 tc_delay;
 while((tc_data)==0) {;}
 tc_delay;
 for(unsigned char i=0;i<16;i++){
     data<<=1;
     tc_clkl;
     tc_delay;
 if((tc_data)==0b00100000){
     data|=0x0001;
 }
    tc_clkh;
 tc_delay;
 }
 SUPPLY_OFF;
 return data;
}
int main(){
    int data = tc_read();
    printf(data);
    return 0;
}
