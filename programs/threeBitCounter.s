ldr r0, =0x20200000
ldr r1, =0x00001240
str r1, [r0]

mov r4, #4
mov r5, #8
mov r6, #16

loop:
str r4, [r0, #28]
str r5, [r0, #28]
str r6, [r0, #28]
str r4, [r0, #40]
str r5, [r0, #40]
str r6, [r0, #40]

wait1:
ldr r3, =0x00300000
sub r3, r3, #1
cmp r3, #0
bne wait1

str r4, [r0, #28]

wait2:
ldr r3, =0x00300000
sub r3, r3, #1
cmp r3, #0
bne wait2

str r4, [r0, #40]
str r5, [r0, #28]

wait3:
ldr r3, =0x00300000
sub r3, r3, #1
cmp r3, #0
bne wait3

str r4, [r0, #28]

wait4:
ldr r3, =0x00300000
sub r3, r3, #1
cmp r3, #0
bne wait4

str r6, [r0, #28]
str r5, [r0, #40]
str r4, [r0, #40]

wait5:
ldr r3, =0x00300000
sub r3, r3, #1
cmp r3, #0
bne wait5

str r4, [r0, #28]

wait6:
ldr r3, =0x00300000
sub r3, r3, #1
cmp r3, #0
bne wait6

str r5, [r0, #28]
str r4, [r0, #40]

wait7:
ldr r3, =0x00300000
sub r3, r3, #1
cmp r3, #0
bne wait7

str r4, [r0, #28]

wait8:
ldr r3, =0x00300000
sub r3, r3, #1
cmp r3, #0
bne wait8

b loop
