/*
Author: Andrew Elder
Teacher: Mr D'arcy
Course: TEI4M
*/

uint8_t data = 2;
uint8_t clock = 3;
uint8_t latch = 4;
//char beck[] = "     ";



void setup() {
  // put your setup code here, to run once:
  asm(

    //this setup is currntly MSG
    "setupA: \n"
    //r30, r31 for rZ
    //    "ldi r26, lo8(beck) \n"
    //    "ldi r27, hi8(beck) \n"
    //    //STS   k, Rr
    //    "ldi r16, 0b00001111 \n"
    //    "ldi r17, 0b00001111 \n"
    //    "ldi r18, 0b00001111 \n"
    //    "st X+, r16\n"
    //    "st X+, r17\n"
    //    "st X+, r18\n"


    "ser r30\n" //sets all the bits high in R 30
    "out 0x0A, r30\n" //sets all the I/O pins to output

    "ldi r16, 0b10000000 \n"
    "ldi r17, 0b00001111 \n"
    "ldi r18, 0b11111110 \n"

"ldi r24, 8 \n"

    "start: \n"
    //MAKE SURE TO USE RIGHT REGISTERS
    "ldi r23, 6 \n"

    "sstart: \n"

    "cbi 0x0B, 0x04 \n" //turns off pin 4 / latch



    "intz: \n"

    "ldi r20, 128 \n" //value and mask

    "comp: \n"
    "cbi 0x0B, 0x03 \n" //turns off pin 3 / clock
    "rcall delay \n" // delay

    "tst r20 \n"
    "breq end \n"
    "mov r19, r16 \n" //coping register
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

    "end: \n "                                           //end of first
    

    "intz2: \n"

    "ldi r20, 128 \n" //value and mask

    "comp2: \n"
    "cbi 0x0B, 0x03 \n" //turns off pin 3 / clock
    "rcall delay \n" // delay

    "tst r20 \n"
    "breq end2 \n"
    "mov r19, r17 \n" //coping register
    "and r19, r20 \n" //anding to get sing bit
    "breq zero2 \n" //if zero branch
    "sbi 0x0B, 0x02 \n" //turns on pin 2 / data
    "lsr r20 \n" //divde by 2
    "rjmp clockend2 \n"

    "zero2: \n"
    "cbi 0x0B, 0x02 \n" //turns off pin 2 / data
    "lsr r20 \n" //divde by 2
    "clockend2: \n"

    "sbi 0x0B, 0x03 \n" //turns on pin 3 / clock
    "rcall delay \n" // delay
    "rjmp comp2 \n" //go back for anothe rround

    "end2: \n "                                    //end of second loop


    "intz3: \n"

    "ldi r20, 128 \n" //value and mask

    "comp3: \n"
    "cbi 0x0B, 0x03 \n" //turns off pin 3 / clock
    "rcall delay \n" // delay

    "tst r20 \n"
    "breq end3 \n"
    "mov r19, r18 \n" //coping register
    "and r19, r20 \n" //anding to get sing bit
    "breq zero3 \n" //if zero branch
    "sbi 0x0B, 0x02 \n" //turns on pin 2 / data
    "lsr r20 \n" //divde by 2
    "rjmp clockend3 \n"

    "zero3: \n"
    "cbi 0x0B, 0x02 \n" //turns off pin 2 / data
    "lsr r20 \n" //divde by 2
    "clockend3: \n"

    "sbi 0x0B, 0x03 \n" //turns on pin 3 / clock
    "rcall delay \n" // delay
    "rjmp comp3 \n" //go back for anothe rround

    "end3: \n "

    "sbi 0x0B, 0x04 \n" //turns on pin 4 / latch            //End of Shift Out

    "ldi r22, 40 \n\t rcall delay \n" //chooses register, sets register to 32

    "sbrc r23, 0 \n"
    "rjmp odd \n"

    "sec \n"
    "ror r16 \n"
    "lsl r18 \n"

    "dec r23\n"
    "brne sstart \n"

    "odd: \n"

    "lsl r16 \n"
    "sec \n"
    "ror r18 \n"

    "dec r23\n"
    "brne sstart \n"


    "ldi r22, 255 \n\t rcall delay \n" //chooses register, sets register to 32

    "sec \n"
    "ror r16 \n"
    "lsl r18 \n"
    

    "rjmp start \n"


    "delay:\n" //allows to jump to line
    "dec r8\n" //takes one aways from r8 from 255
    "brne delay\n" //jumps back to delay if r8 is not 0
    "dec r9\n" //takes one aways from r9 from 255
    "brne delay\n"  //jumps back to delay if r9 is not 0
    "ret\n"  //returns back to where delay was called


    "longDelay:\n" //allows to jump to line
    "dec r8\n" //takes one aways from r8 from 255
    "brne delay\n" //jumps back to delay if r8 is not 0
    "dec r9\n" //takes one aways from r9 from 255
    "brne delay\n"  //jumps back to delay if r9 is not 0
    "dec r10\n" //takes one aways from r9 from 255
    "brne delay\n"  //jumps back to delay if r9 is not 0
    "dec r21\n" //takes one aways from r16 from 255
    "brne delay\n"  //jumps back to delay if r16 is not 0
    "ret\n"  //returns back to where delay was called


    //"dec r21 \n"
    //"brne intz \n"


    //      //this setup is currntly LSG
    //    "setup2: \n"
    //
    //    "ser r30\n" //sets all the bits high in R 30
    //    "out 0x0A, r30\n" //sets all the I/O pins to output
    //
    //    "intz4: \n"
    //    "cbi 0x0B, 0x04 \n" //turns off pin 4 / latch
    //
    //    "ldi r18, 0b10101010 \n" //value for shift out
    //    "ldi r20, 1 \n" //value and mask
    //
    //    "comp4: \n"
    //    "cbi 0x0B, 0x03 \n" //turns off pin 3 / clock
    //    "rcall delay \n" // delay
    //
    //    "tst r20 \n"
    //    "breq end4 \n"
    //    "mov r19, r18 \n" //coping register
    //    "and r19, r20 \n" //anding to get sing bit
    //    "breq zero4 \n" //if zero branch
    //    "sbi 0x0B, 0x02 \n" //turns on pin 2 / data
    //    "lsr r18 \n" //divde by 2
    //    "rjmp clockend4 \n"
    //
    //    "zero4: \n"
    //    "cbi 0x0B, 0x02 \n" //turns off pin 2 / data
    //    "lsr r18 \n" //divde by 2
    //    "clockend4: \n"
    //
    //    "sbi 0x0B, 0x03 \n" //turns on pin 3 / clock
    //    "rcall delay \n" // delay
    //    "rjmp comp4 \n" //go back for anothe rround
    //
    //
    //    "end4: \n"
    //    "sbi 0x0B, 0x04 \n" //turns on pin 4 / latch
  );

}

void loop() {
  // put your main code here, to run repeatedly:

}
