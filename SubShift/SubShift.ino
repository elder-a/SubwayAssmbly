/*
Author: Andrew Elder
Teacher: Mr D'arcy
Course: TEI4M
*/

uint8_t data = 2;
uint8_t clock = 3;
uint8_t latch = 4;



void setup() {
  // put your setup code here, to run once:
  asm(

    //this setup is currntly MSG
    "setupA: \n"

    "ldi r21, 3 \n"

    "ser r30\n" //sets all the bits high in R 30
    "out 0x0A, r30\n" //sets all the I/O pins to output

    "cbi 0x0B, 0x04 \n" //turns off pin 4 / latch

    "intz: \n"
    "ldi r18, 0b11110000 \n" //value for shift out
    "ldi r20, 128 \n" //value and mask

    "comp: \n"
    "cbi 0x0B, 0x03 \n" //turns off pin 3 / clock
    "rcall delay \n" // delay

    "tst r20 \n"
    "breq end \n"
    "mov r19, r18 \n" //coping register
    "and r19, r20 \n" //anding to get sing bit
    "breq zero \n" //if zero branch
    "sbi 0x0B, 0x02 \n" //turns on pin 2 / data
    "lsr r20 \n" //divde by 2
    "rjmp clockend \n"

    "zero: \n"
    "cbi 0x0B, 0x02 \n" //turns off pin 2 / data
    "lsr r20 \n" //divde by 2
    "clockend: \n"

    "sbi 0x0B, 0x03 \n" //turns on pin 3 / clock
    "rcall delay \n" // delay
    "rjmp comp \n" //go back for anothe rround

    "end: \n"
    "dec r21 \n"
    "brne intz \n"

    "sbi 0x0B, 0x04 \n" //turns on pin 4 / latch





    //      //this setup is currntly LSG
    //    "setup2: \n"
    //
    //    "ser r30\n" //sets all the bits high in R 30
    //    "out 0x0A, r30\n" //sets all the I/O pins to output
    //
    //    "intz2: \n"
    //    "cbi 0x0B, 0x04 \n" //turns off pin 4 / latch
    //
    //    "ldi r18, 0b10101010 \n" //value for shift out
    //    "ldi r20, 1 \n" //value and mask
    //
    //    "comp2: \n"
    //    "cbi 0x0B, 0x03 \n" //turns off pin 3 / clock
    //    "rcall delay \n" // delay
    //
    //    "tst r20 \n"
    //    "breq end2 \n"
    //    "mov r19, r18 \n" //coping register
    //    "and r19, r20 \n" //anding to get sing bit
    //    "breq zero2 \n" //if zero branch
    //    "sbi 0x0B, 0x02 \n" //turns on pin 2 / data
    //    "lsr r18 \n" //divde by 2
    //    "rjmp clockend2 \n"
    //
    //    "zero2: \n"
    //    "cbi 0x0B, 0x02 \n" //turns off pin 2 / data
    //    "lsr r18 \n" //divde by 2
    //    "clockend2: \n"
    //
    //    "sbi 0x0B, 0x03 \n" //turns on pin 3 / clock
    //    "rcall delay \n" // delay
    //    "rjmp comp2 \n" //go back for anothe rround
    //
    //
    //    "end2: \n"
    //    "sbi 0x0B, 0x04 \n" //turns on pin 4 / latch

    "delay:\n" //allows to jump to line
    "dec r8\n" //takes one aways from r8 from 255
    "brne delay\n" //jumps back to delay if r8 is not 0
    "dec r9\n" //takes one aways from r9 from 255
    "brne delay\n"  //jumps back to delay if r9 is not 0
    "ret\n"  //returns back to where delay was called
  );

}

void loop() {
  // put your main code here, to run repeatedly:

}
