************************Part One************************
.data

led:	.word	0xff200000
sw:		.word	0xff200040
push:	.word	0xff200050

.text
.global _start

_start:
	ldr r0,=led
	ldr r0, [r0]
	
	ldr r1,=sw
	ldr r1,[r1]
	
	ldr r2,[r1] //read from switches
	str r2,[r0] //store to led
	ldr r3,[r1] // read from switches
	str r3,[r0] //store to led
	b done


done:
	b done
	
*********************Part Two****************************
.data

led:	.word	0xff200000
sw:		.word	0xff200040
push:	.word	0xff200050
lights:	.word	1023  //value that turns on all LED's

.text
.global _start

_start:
	ldr r0,=led
	ldr r0, [r0]
	ldr r1,=sw
	ldr r1,[r1]
	mov r9, #0 // add
	mov r10, #1 //and
	mov r11, #2 //mul
	mov r12, #3 //xor
	ldr r8,=lights 
	ldr r8,[r8]
	
	ldr r2,[r1]// First value
	ldr r3,[r1]// Second value
	ldr r4,[r1] //Condition

comp:			//determine which operation was chosen
	cmp r4,r9
	beq add
	cmp r4,r10
	beq and
	cmp r4,r11
	beq mul
	cmp r4, r12
	beq xor
	b lightup

add:
	add r2, r2, r3
	cmp r2, #0
	beq lightup
	str r2,[r0]
	b done
	
and:
	AND r2, r2, r3
	cmp r2, #0
	beq lightup
	str r2,[r0]
	b done
mul:
	mul r2, r2, r3
	cmp r2, #0
	beq lightup
	str r2,[r0]
	b done
xor:
	EOR r2, r2, r3
	cmp r2, #0
	beq lightup
	str r2,[r0]
	b done
lightup:		//turn all led's on
	str r8,[r0]
	b done

done:
	b done
	
.end
	