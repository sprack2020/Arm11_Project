ldr r10, =0
ldr r11, =0
ldr r12, =538968064
ldr r1, =65536
orr r11, r11, #262144
str r11, [r12, #4]
str r1, [r12, #28]
str r1, [r12, #40]
ldr r2, =1
while_0:
cmp r2, #0
beq endwhile_0
str r1, [r12, #40]
ldr r11, =-1
sub r11, r11, r1
and r10, r10, r11
ldr r0, =10000000
while_1:
cmp r0, #0
beq endwhile_1
sub r0, r0, #1
b while_1
endwhile_1:
str r1, [r12, #28]
orr r10, r10, r1
ldr r0, =10000000
while_2:
cmp r0, #0
beq endwhile_2
sub r0, r0, #1
b while_2
endwhile_2:
b while_0
endwhile_0:
