ldr r0, =0x20200000     ;r0 contains base address for GPIO operations
ldr r1, =0x00001240     ;bitmask to enable pins 2-4 as output
str r1, [r0]            ;set pins 2-4 as output

mov r4, #0x4            ;bitmasks for setting/clearing GPIO 2-4
mov r5, #0x8
mov r6, #0x16
orr r8, r4, r5
orr r8, r8, r6          ;pre-setup bitmasks for setting/clearing multiple
orr r9, r4, r5          ;pins at a time as needed

str r4, [r0, #28]       ;clear pins initially
str r5, [r0, #28]
str r6, [r0, #28]

loop:
str r8, [r0, #40]       ;all leds off (pins set)

ldr r3, =0x00800000
wait1:
sub r3, r3, #1
cmp r3, #0
bne wait1

str r4, [r0, #28]       ;LED 1  on

ldr r3, =0x00800000
wait2:
sub r3, r3, #1
cmp r3, #0
bne wait2

str r4, [r0, #40]       ;LED 1 off
str r5, [r0, #28]       ;LED 2 on

ldr r3, =0x00800000
wait3:
sub r3, r3, #1
cmp r3, #0
bne wait3

str r4, [r0, #28]       ;LED 1 on

ldr r3, =0x00800000
wait4:
sub r3, r3, #1
cmp r3, #0
bne wait4

str r6, [r0, #28]       ;LED 3 on
str r9, [r0, #40]       ;LEDs 1 and 2 off

ldr r3, =0x00800000
wait5:
sub r3, r3, #1
cmp r3, #0
bne wait5

str r4, [r0, #28]       ;LED 1 on

ldr r3, =0x00800000
wait6:
sub r3, r3, #1
cmp r3, #0
bne wait6

str r5, [r0, #28]       ;LED 2 on
str r4, [r0, #40]       ;LED 1 off

ldr r3, =0x00800000
wait7:
sub r3, r3, #1
cmp r3, #0
bne wait7

str r4, [r0, #28]       ;LED 1 on

ldr r3, =0x00800000
wait8:
sub r3, r3, #1
cmp r3, #0
bne wait8

b loop                  ;repeat
