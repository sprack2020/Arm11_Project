ldr r10, =0
ldr r11, =0
ldr r12, =538968064
ldr r1, =4
orr r11, r11, #64
str r11, [r12, #0]
str r1, [r12, #40]
str r1, [r12, #28]
ldr r2, =8
orr r11, r11, #512
str r11, [r12, #0]
str r2, [r12, #40]
str r2, [r12, #28]
ldr r3, =16
orr r11, r11, #4096
str r11, [r12, #0]
str r3, [r12, #40]
str r3, [r12, #28]
ldr r4, =131072
orr r11, r11, #2097152
str r11, [r12, #4]
str r4, [r12, #40]
str r4, [r12, #28]
ldr r5, =1
while_0:
cmp r5, #0
beq endwhile_0
str r1, [r12, #28]
orr r10, r10, r1
ldr r0, =900000
while_1:
cmp r0, #0
beq endwhile_1
sub r0, r0, #1
b while_1
endwhile_1:
str r1, [r12, #40]
ldr r11, =-1
sub r11, r11, r1
and r10, r10, r11
str r2, [r12, #28]
orr r10, r10, r2
ldr r0, =900000
while_2:
cmp r0, #0
beq endwhile_2
sub r0, r0, #1
b while_2
endwhile_2:
str r2, [r12, #40]
ldr r11, =-1
sub r11, r11, r2
and r10, r10, r11
str r3, [r12, #28]
orr r10, r10, r3
ldr r0, =900000
while_3:
cmp r0, #0
beq endwhile_3
sub r0, r0, #1
b while_3
endwhile_3:
str r3, [r12, #40]
ldr r11, =-1
sub r11, r11, r3
and r10, r10, r11
str r4, [r12, #28]
orr r10, r10, r4
ldr r0, =900000
while_4:
cmp r0, #0
beq endwhile_4
sub r0, r0, #1
b while_4
endwhile_4:
str r4, [r12, #40]
ldr r11, =-1
sub r11, r11, r4
and r10, r10, r11
b while_0
endwhile_0: