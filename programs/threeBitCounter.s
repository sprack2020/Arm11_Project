ldr r12, =0x20200000     ;r12 contains base address for GPIO operations
ldr r7, =0               ;r7 will help calculate the state register
ldr r8, =0               ;r8 will be the led state register


orr r7, r7, 0x00000040   ;bitmask to enable pins 2-4 as output
str r7, [r12]            ;set pins 2-4 as output
ldr r9, =0x4             ;bitmask for setting/clearing GPIO 2, r9
str r9, [r12, #28]       ;clear pin 2
str r9, [r12, #40]       ;set pin 2

orr r7, r7, #0x00000200
str r7, [r12]
ldr r10, =0x8            ;bitmask for setting/clearing GPIO 3, r10
str r10, [r12, #28]      ;clear pin 3
str r10, [r12, #40]      ;set pin 3

orr r7, r7, #0x00001000
str r7, [r12]
ldr r11, =0x10           ;bitmask for setting/clearing GPIO 4, r11
str r11, [r12, #28]      ;clear pin 4
str r11, [r12, #40]      ;set pin 4


led0:

led0_off:
str r9, [r12, #40]      ;led0 = off
ldr r7, =0xffffffff     ;sets r7 to an all 1 bitmask
sub r7, r7, r9          ;r7 is all 1's without led0
and r8, r8, r7          ;sets led0 state to off
b wait

led0_on:
str r9, [r12, #28]      ;led0 = on
orr r8, r8, r9          ;sets led0 state to on
b wait

led1:
and r7, r8, r10         ;bool r7 is true when led1 is on else false
cmp r7, #0              ;if led1 is on turn off else turn on
bne led1_off

led1_on:
str r10, [r12, #28]     ;led1 = on
orr r8, r8, r10         ;sets led1 state to on
b led0

led1_off:
str r10, [r12, #40]     ;led1 = off
ldr r7, =0xffffffff     ;sets r7 to an all 1 bitmask
sub r7, r7, r10         ;r7 is all 1's without led1
and r8, r8, r7          ;sets led1 state to off

led2:
and r7, r8, r11         ;bool r7 is true when led2 is on else false
cmp r7, #0              ;if led2 is on turn off else turn on
bne led2_off

led2_on:
str r11, [r12, #28]     ;led2 = on
orr r8, r8, r11         ;sets led2 state to on
b led0


led2_off:
str r11, [r12, #40]     ;led2 = off
ldr r7, =0xffffffff     ;sets r7 to an all 1 bitmask
sub r7, r7, r11         ;r7 is all 1's without led2
and r8, r8, r7          ;sets led2 state to off
b led0

wait:                   ;waits ~1 second before continuing
ldr r0, =0x00800000

while:
sub r0, r0, #1
cmp r0, #0
bne while

next:                   ;if led0 is off then turn led0 on else turn led1 on
and r7, r8, r9
cmp r7, #0
bne led1
b led0_on
