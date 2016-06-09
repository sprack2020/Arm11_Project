main:

; outputs to pins at GPIO 0, 1 and 2

; register allocation
; r0 - r3 variable
; r9 setting controls
; r10 for comparing single bits
; r11 clear address
; r12 write address

ldr r9, #0x20200000 ;address pins0-9
orr r9, #0x1  ;sets pin0 output
orr r9, #0x8  ;sets pin1 output
orr r9, #0x40 ;sets pin2 output

; r9 no longer required

ldr r11, #0x20200028 ;r11 contains clear address
ldr r12, #0x2020001c ;r12 contains write address



led0:
ldr r0, #1
str r0, [r11] ;clears GPIO pin 0

wait0:

ldr r0, #10000 ;i = 10000

while0:
cmp r0, #0
beq endwhile0 ;while i>0

ldr r1, #10000 ;j = 10000

while1:
cmp r1, #0
beq endwhile1 ;while j>0

sub r1, r1, #1 ;j-- 

b while1
endwhile1:

sub r0, r0, #1 ;i--

b while0
endwhile0:



ldr r0, #1
str r0, [r11] ;clears GPIO pin 0
str r0, [r12] ;writes GPIO pin 0



wait1:

ldr r0, #10000 ;i = 10000

while2:
cmp r0, #0
beq endwhile2 ;while i>0

ldr r1, #10000 ;j = 10000

while3:
cmp r1, #0
beq endwhile3 ;while j>0

sub r1, r1, #1 ;j-- 

b while3
endwhile3:

sub r0, r0, #1 ;i--

b while2
endwhile2:




led1:

if0:
and r10, r12, #8
cmp r10, #0
bne else0 ;if led1 is on write pin1 else clear and continue to led2

ldr r0, #8
str r0, [r11] ;clears GPIO pin 1
str r0, [r12] ;writes GPIO pin 1

b led0 
 
else0:

ldr r0, #8
str r0, [r11] ;clears GPIO pin 1





led2:

if1:
and r10, r12, #0x40
cmp r10, #0
bne else1 ;if led2 is on write pin2 else clear 

ldr r0, #0x40
str r0, [r11] ;clears GPIO pin 2
str r0, [r12] ;writes GPIO pin 2

b endif1
 
else1:

ldr r0, #0x40
str r0, [r11] ;clears GPIO pin 2

endif1:
b led0 ;return to start of counter














