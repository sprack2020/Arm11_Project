ldr r0, =0x20200000
ldr r1, =0x00001240
str r1, [r0]
ldr r1, =0x00040000
str r1, [r0, #4]

mov r4, #0x4
mov r5, #0x8
mov r6, #0x16
mov r7, #0

str r4, [r0, #28]
str r5, [r0, #28]
str r6, [r0, #28]

loop:
orr r8, r4, r5
orr r8, r8, r6
str r8, [r0, #40]

ldr r3, =0x00800000
wait1:
sub r3, r3, #1
cmp r3, #0
bne wait1

str r4, [r0, #28]
str r7, [r0, #40]

ldr r3, =0x00800000
wait2:
sub r3, r3, #1
cmp r3, #0
bne wait2

str r4, [r0, #40]
str r5, [r0, #28]

ldr r3, =0x00800000
wait3:
sub r3, r3, #1
cmp r3, #0
bne wait3

str r4, [r0, #28]
str r7, [r0, #40]

ldr r3, =0x00800000
wait4:
sub r3, r3, #1
cmp r3, #0
bne wait4

str r6, [r0, #28]
orr r8, r5, r4
str r8, [r0, #40]

ldr r3, =0x00800000
wait5:
sub r3, r3, #1
cmp r3, #0
bne wait5

str r4, [r0, #28]
str r7, [r0, #40]

ldr r3, =0x00800000
wait6:
sub r3, r3, #1
cmp r3, #0
bne wait6

str r5, [r0, #28]
str r4, [r0, #40]

ldr r3, =0x00800000
wait7:
sub r3, r3, #1
cmp r3, #0
bne wait7

str r4, [r0, #28]
str r7, [r0, #40]

ldr r3, =0x00800000
wait8:
sub r3, r3, #1
cmp r3, #0
bne wait8

b loop
