setup:
ldr r1, =0x20200000
ldr r2, =0x00040000
str r2, [r1, #4]
ldr r2, =0x00010000
str r2, [r1, #28]
b on

loopOn:
ldr r3, =0x00300000
whileOn:
sub r3, r3, #1
cmp r3, #0
beq on
b whileOn

loopOff:
ldr r3, =0x00300000
whileOff:
sub r3, r3, #1
cmp r3, #0
beq off
b whileOff

on:
str r2, [r1, #40]
b loopOff

off:
str r2, [r1, #28]
b loopOn
