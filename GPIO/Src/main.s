	.cpu arm7tdmi
	.arch armv4t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
	.align	2
	.global	delay
	.syntax unified
	.arm
	.type	delay, %function
delay:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L2
.L3:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L2:
	ldr	r3, [fp, #-8]
	ldr	r2, .L4
	cmp	r3, r2
	bls	.L3
	nop
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L5:
	.align	2
.L4:
	.word	49999
	.size	delay, .-delay
	.align	2
	.global	main
	.syntax unified
	.arm
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	ldr	r3, .L8
	str	r3, [fp, #-8]
	ldr	r3, .L8+4
	str	r3, [fp, #-12]
	ldr	r3, .L8+8
	str	r3, [fp, #-16]
	ldr	r3, .L8+12
	str	r3, [fp, #-20]
	ldr	r3, [fp, #-20]
	ldr	r3, [r3]
	orr	r2, r3, #8
	ldr	r3, [fp, #-20]
	str	r2, [r3]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3]
	orr	r2, r3, #1426063360
	ldr	r3, [fp, #-8]
	str	r2, [r3]
	ldr	r3, [fp, #-12]
	ldr	r3, [r3]
	orr	r2, r3, #-1442840576
	ldr	r3, [fp, #-12]
	str	r2, [r3]
.L7:
	ldr	r3, [fp, #-16]
	ldr	r3, [r3]
	orr	r2, r3, #61440
	ldr	r3, [fp, #-16]
	str	r2, [r3]
	bl	delay
	ldr	r3, [fp, #-16]
	ldr	r3, [r3]
	bic	r2, r3, #61440
	ldr	r3, [fp, #-16]
	str	r2, [r3]
	bl	delay
	b	.L7
.L9:
	.align	2
.L8:
	.word	1073875968
	.word	1073875980
	.word	1073875988
	.word	1073887280
	.size	main, .-main
	.ident	"GCC: (Arm GNU Toolchain 14.2.Rel1 (Build arm-14.52)) 14.2.1 20241119"
