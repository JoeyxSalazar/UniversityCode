.data
ar1:	.word	5
ar2:	.word	4

.global _start
.text

_start:
	ldr r0,=ar1		//E59F001C
	ldr r1,=ar2		//E59F101C
loop:
	ldr r2,[r0]		//E4902004  
	ldr r3,[r1]		//E4913004
	subs r4, r2, r3 //E0524003	1110 0000 0101 0010 0100 0000 0000 0011
	beq	done		//0a000000
	b loop			//EAFFFFFA	1110 1010 1111 1111 1111 1111 1111 1010
done:
	b done			//EAFFFFFA
.end
*************************************************************************


	