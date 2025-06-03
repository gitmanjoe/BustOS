#include "sound.h"
#include "screen.h"
#include "ports.h"
#include "timer.h"

// play frequency
void play_freq(unsigned int nFrequence) {
unsigned int Div;
unsigned char tmp;
//Set the PIT to the desired frequency
Div = 1193180 / nFrequence;
port_byte_out(0x43, 0xb6);
port_byte_out(0x42, (unsigned char) (Div) );
port_byte_out(0x42, (unsigned char) (Div >> 8));
// play the sound using the PC speaker
tmp = port_byte_in(0x61);
if (tmp != (tmp | 3)) {
port_byte_out(0x61, tmp | 3);
}
}

// turn speaker off
void nosound() {
    unsigned char tmp = port_byte_in(0x61) & 0xFC;
    port_byte_out(0x61, tmp);
}
// duration delay
void time_wait(int duration ){
    for(int i=0;i<duration;i++){
        for(int j=0;j<100000;j++){

        }
    }
}
//Make a beep for frequency and duration
void beep(unsigned int freq, int duration) {
play_freq(freq);
time_wait(duration);
nosound();
}