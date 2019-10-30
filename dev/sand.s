	.file	"sand.cpp"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	__vector_TIMER1_COMPA_vect
	.type	__vector_TIMER1_COMPA_vect, @function
__vector_TIMER1_COMPA_vect:
/* prologue: naked */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
/* #APP */
 ;  85 "sand.cpp" 1
	reti
 ;  0 "" 2
/* #NOAPP */
	nop
/* epilogue start */
	.size	__vector_TIMER1_COMPA_vect, .-__vector_TIMER1_COMPA_vect
.global	_Z8testFuncv
	.type	_Z8testFuncv, @function
_Z8testFuncv:
	push r28
	push r29
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
.L3:
	nop
	rjmp .L3
	.size	_Z8testFuncv, .-_Z8testFuncv
.global	_Z5setupv
	.type	_Z5setupv, @function
_Z5setupv:
	push r28
	push r29
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,12
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 12 */
/* stack size = 14 */
.L__stack_usage = 14
	std Y+1,__zero_reg__
	std Y+2,__zero_reg__
	std Y+3,__zero_reg__
	std Y+4,__zero_reg__
.L6:
	ldd r24,Y+1
	ldd r25,Y+2
	ldd r26,Y+3
	ldd r27,Y+4
	cpi r24,-1
	sbci r25,-1
	sbci r26,4
	cpc r27,__zero_reg__
	brlo .+2
	rjmp .L5
/* #APP */
 ;  99 "sand.cpp" 1
	push __tmp_reg__
	push __zero_reg__
	push r2
	push r3
	push r4
	push r5
	push r6
	push r7
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	push r16
	push r17
	push r18
	push r19
	push r20
	push r21
	push r22
	push r23
	push r24
	push r25
	push r26
	push r27
	push r28
	push r29
	push r30
	push r31
	in __tmp_reg__,  __SREG__
	push __tmp_reg__
 ;  0 "" 2
 ;  100 "sand.cpp" 1
	pop __tmp_reg__
	out __SREG__, __tmp_reg__
	pop r31
	pop r30
	pop r29
	pop r28
	pop r27
	pop r26
	pop r25
	pop r24
	pop r23
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18
	pop r17
	pop r16
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop r7
	pop r6
	pop r5
	pop r4
	pop r3
	pop r2
	pop __zero_reg__
	pop __tmp_reg__
 ;  0 "" 2
/* #NOAPP */
	ldd r24,Y+1
	ldd r25,Y+2
	ldd r26,Y+3
	ldd r27,Y+4
	adiw r24,1
	adc r26,__zero_reg__
	adc r27,__zero_reg__
	std Y+1,r24
	std Y+2,r25
	std Y+3,r26
	std Y+4,r27
	rjmp .L6
.L5:
/* #APP */
 ;  102 "sand.cpp" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	ldi r24,lo8(gs(_Z8testFuncv))
	ldi r25,hi8(gs(_Z8testFuncv))
	std Y+12,r25
	std Y+11,r24
	ldi r24,lo8(96)
	ldi r25,lo8(16)
	std Y+6,r25
	std Y+5,r24
	ldd r24,Y+5
	ldd r25,Y+6
	mov r18,r24
	mov r19,r25
	subi r18,1
	sbc r19,__zero_reg__
	std Y+6,r19
	std Y+5,r18
	ldd r18,Y+11
	ldd r19,Y+12
	mov r30,r24
	mov r31,r25
	st Z,r18
	ldd r24,Y+5
	ldd r25,Y+6
	mov r18,r24
	mov r19,r25
	subi r18,1
	sbc r19,__zero_reg__
	std Y+6,r19
	std Y+5,r18
	ldd r18,Y+11
	ldd r19,Y+12
	mov r18,r19
	clr r19
	mov r30,r24
	mov r31,r25
	st Z,r18
	std Y+8,__zero_reg__
	std Y+7,__zero_reg__
.L8:
	ldd r24,Y+7
	ldd r25,Y+8
	sbiw r24,24
	brsh .L7
	ldd r24,Y+5
	ldd r25,Y+6
	mov r18,r24
	mov r19,r25
	subi r18,1
	sbc r19,__zero_reg__
	std Y+6,r19
	std Y+5,r18
	mov r30,r24
	mov r31,r25
	st Z,__zero_reg__
	ldd r24,Y+7
	ldd r25,Y+8
	adiw r24,1
	std Y+8,r25
	std Y+7,r24
	rjmp .L8
.L7:
	ldd r24,Y+5
	ldd r25,Y+6
	mov r18,r24
	mov r19,r25
	subi r18,1
	sbc r19,__zero_reg__
	std Y+6,r19
	std Y+5,r18
	mov r30,r24
	mov r31,r25
	st Z,__zero_reg__
	ldd r24,Y+5
	ldd r25,Y+6
	mov r18,r24
	mov r19,r25
	subi r18,1
	sbc r19,__zero_reg__
	std Y+6,r19
	std Y+5,r18
	mov r30,r24
	mov r31,r25
	st Z,__zero_reg__
	ldd r24,Y+5
	ldd r25,Y+6
	mov r18,r24
	mov r19,r25
	subi r18,1
	sbc r19,__zero_reg__
	std Y+6,r19
	std Y+5,r18
	mov r30,r24
	mov r31,r25
	st Z,__zero_reg__
	ldd r24,Y+5
	ldd r25,Y+6
	mov r18,r24
	mov r19,r25
	subi r18,1
	sbc r19,__zero_reg__
	std Y+6,r19
	std Y+5,r18
	mov r30,r24
	mov r31,r25
	st Z,__zero_reg__
	ldd r24,Y+5
	ldd r25,Y+6
	mov r18,r24
	mov r19,r25
	subi r18,1
	sbc r19,__zero_reg__
	std Y+6,r19
	std Y+5,r18
	mov r30,r24
	mov r31,r25
	st Z,__zero_reg__
	ldd r24,Y+5
	ldd r25,Y+6
	mov r18,r24
	mov r19,r25
	subi r18,1
	sbc r19,__zero_reg__
	std Y+6,r19
	std Y+5,r18
	mov r30,r24
	mov r31,r25
	st Z,__zero_reg__
	ldd r24,Y+5
	ldd r25,Y+6
	mov r18,r24
	mov r19,r25
	subi r18,1
	sbc r19,__zero_reg__
	std Y+6,r19
	std Y+5,r18
	mov r30,r24
	mov r31,r25
	st Z,__zero_reg__
	ldd r24,Y+5
	ldd r25,Y+6
	mov r18,r24
	mov r19,r25
	subi r18,1
	sbc r19,__zero_reg__
	std Y+6,r19
	std Y+5,r18
	mov r30,r24
	mov r31,r25
	st Z,__zero_reg__
	ldd r24,Y+5
	ldd r25,Y+6
	mov r18,r24
	mov r19,r25
	subi r18,1
	sbc r19,__zero_reg__
	std Y+6,r19
	std Y+5,r18
	mov r30,r24
	mov r31,r25
	st Z,__zero_reg__
	ldi r24,lo8(93)
	ldi r25,0
	ldd r18,Y+5
	ldd r19,Y+6
	mov r30,r24
	mov r31,r25
	st Z,r18
/* #APP */
 ;  125 "sand.cpp" 1
	pop __tmp_reg__
	out __SREG__, __tmp_reg__
	pop r31
	pop r30
	pop r29
	pop r28
	pop r27
	pop r26
	pop r25
	pop r24
	pop r23
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18
	pop r17
	pop r16
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop r7
	pop r6
	pop r5
	pop r4
	pop r3
	pop r2
	pop __zero_reg__
	pop __tmp_reg__
 ;  0 "" 2
/* #NOAPP */
	std Y+10,__zero_reg__
	std Y+9,__zero_reg__
.L10:
	ldd r24,Y+9
	ldd r25,Y+10
	sbiw r24,2
	brge .L9
	ldd r24,Y+9
	ldd r25,Y+10
	adiw r24,1
	std Y+10,r25
	std Y+9,r24
	rjmp .L10
.L9:
	ldi r30,lo8(34)
	ldi r31,lo8(2)
	icall
	nop
/* epilogue start */
	adiw r28,12
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r29
	pop r28
	ret
	.size	_Z5setupv, .-_Z5setupv
.global	_Z4loopv
	.type	_Z4loopv, @function
_Z4loopv:
	push r28
	push r29
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	nop
/* epilogue start */
	pop r29
	pop r28
	ret
	.size	_Z4loopv, .-_Z4loopv
	.ident	"GCC: (GNU) 5.4.0"
