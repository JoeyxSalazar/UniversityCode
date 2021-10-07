.data
led:	.word	0xff200000
lights:	.word	1023
.global _start
.text
_start:
ldr r4,=led
ldr r4, [r4]
ldr r8,=lights 
ldr r8,[r8]
mov r0, #5 //x
mov r1, #0  //y
mov r2, #0  //a
//operands

cmp r0, #0
beq done
cmp r1, #0
beq lightup
//if one of them is zero, end

checklsb:
mov r10, #0
AND r10, r1, #1
cmp r10, #1
beq accumulate
bne lsbzero

accumulate:
add r2, r2, r0 //accumulate a
b lsbzero

lsbzero:
lsl r0,#1      //shift x left
lsr r1,#1	   //shift y right
cmp r1,#0
bne checklsb //continue checking bits
beq display	// end

display:
cmp r2, #0
beq lightup
str r2,[r4]
b done

lightup:
str r8,[r4]
b done

done:
b	done

.end