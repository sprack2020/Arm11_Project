setup:
ldr r1, =0x20200000     ;base address for GPIO operations
ldr r2, =0x00040000     ;bit mask for setting pin 16 as output
str r2, [r1, #4]        ;set pin 16 as output
ldr r2, =0x00010000     ;bit mask for setting/clearing pin 16
str r2, [r1, #28]       ;initially clear pin 16


on:                     ;turn LED on
str r2, [r1, #40]
ldr r0, =0x1
b wait

off:                    ;turn LED off
str r2, [r1, #28]
ldr r0, =0x0
b wait

wait:
ldr r3, =0x00300000

waitLoop:
sub r3, r3, #1
cmp r3, #0
beq next
b waitLoop

next:
cmp r0, #0
beq on
b off