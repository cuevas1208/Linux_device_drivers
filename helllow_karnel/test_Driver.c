#include <stdio.h>



int main() {
        int adder_out;
        int *base;
        base = 0xf09e0000;
                                                  
        printf("Start IP Adder 8 bit test\n\n\r");
                          
        *base = 0x00301;       
        adder_out = *(base >> 4);                   
        printf("A=1; B=3; S=%d\n\r", adder_out);    
                 
        return 0;
}

