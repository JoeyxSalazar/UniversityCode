@**********************Part One****************************
.data
msg:	.asciz		"I am a cane\n"
cop:	.space		60

.text
.global _start
_start:
	ldr r0,=msg		@address of msg
	ldr r1,=cop		@address of double
first:
	ldrb r2,[r0],#1 @copy char of msg
	cmp	r2,#0x20 	@compare character to space
	bne	nul			@if not equal, check null, then copy or end
	beq	first		@if equal, check next
	
second:
	strb r2,[r1],#1	@store character to duplicate 
	b	first
	
nul:
	cmp r2,#0x00	@compare char to null
	beq	done		@if null, end
	bne	second		@if not equal, str the char
	
done:
	b	done
.end
@*********************Part 2******************************
.data
msg:	.asciz		"I am a cane\n"
cop:	.space		60

.text
.global _start
_start:
	ldr r0,=msg //address of msg
	ldr r1,=cop //address of double
first:
	ldrb r2,[r0],#1 //copy char of msg
	cmp r2,#0x20 //compare to a space
	beq first //if equal check next
	strb r2,[r1], #1 //store char to duplicate
	cmp r2, #0x00 //compare to null
	beq done 
	bne first
done:
	b done
.end
@*********************Part 3*****************
.data
msg:	.asciz		"~ am a cane\n"
		.skip		20
cop:	.space		60

.text
.global _start
_start:
	ldr r0,=msg		@address of msg
	ldr r1,=cop		@address of double
	
reqs:
	ldrb r2,[r0]
	cmp r2,#0x60	@hex vals greater than this include lowercase and symbols
	bge rev			@if first char is hex equiv of 60 or more, reverse it
	ble first		@if less, copy like normal

first:
	ldrb r2,[r0],#1 @copy char of msg
	cmp	r2,#0x20 	@compare character to space
	bne	nul			@if not equal, check null, then copy or end
	beq	first		@if equal, check next
	
second:
	strb r2,[r1],#1	@store character to duplicate 
	b	first
	
nul:
	cmp r2,#0x00	@compare char to null
	beq	done		@if null, end
	bne	second		@if not equal, str the char
	
rev:
	ldrb r2,[r0],#1	@give r2 a char
	cmp r2,#0x20	@compare it to a space
	beq rev			@if its a space, restart process
	bne	nulrev		@if not a space, check null
		
nulrev:
	strb r2,[r1],#-1	@store char, but move pointer backwards
	cmp r2,#0x00		@compare char to null
	bne rev				@if not null, keep checking
	beq done			@if it was null, end
	
done:
	b	done
.end