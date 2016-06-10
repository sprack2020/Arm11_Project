;blink GPIO 16 LED on and off
setup:
ldr r1, =0x20200000     ;base address for GPIO operations
ldr r2, =0x00040000     ;bit mask for setting pin 16 as output
str r2, [r1, #4]        ;set pin 16 as output
ldr r2, =0x00010000     ;bit mask for setting/clearing pin 16
str r2, [r1, #28]       ;initially clear pin 16
b on                    

loopOn:i                ;wait, then jump to on
ldr r3, =0x00300000
whileOn:
sub r3, r3, #1
cmp r3, #0
beq on
b whileOn

loopOff:                ;wait, then jump to off
ldr r3, =0x00300000
whileOff:
sub r3, r3, #1
cmp r3, #0
beq off
b whileOff

on:                     ;turn LED on
str r2, [r1, #40]
b loopOff

off:                    ;turn LED off
str r2, [r1, #28]
b loopOn
