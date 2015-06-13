   1              		.cpu cortex-m0
   2              		.fpu softvfp
   3              		.eabi_attribute 20, 1
   4              		.eabi_attribute 21, 1
   5              		.eabi_attribute 23, 3
   6              		.eabi_attribute 24, 1
   7              		.eabi_attribute 25, 1
   8              		.eabi_attribute 26, 1
   9              		.eabi_attribute 30, 6
  10              		.eabi_attribute 34, 0
  11              		.eabi_attribute 18, 4
  12              		.code	16
  13              		.file	"main.c"
  14              		.text
  15              	.Ltext0:
  16              		.cfi_sections	.debug_frame
  17              		.section	.text.sum,"ax",%progbits
  18              		.align	2
  19              		.global	sum
  20              		.code	16
  21              		.thumb_func
  23              	sum:
  24              	.LFB0:
  25              		.file 1 "../src/main.c"
   1:../src/main.c **** extern int asm_sum(int x, int y);
   2:../src/main.c **** 
   3:../src/main.c **** int sum(int x, int y) {
  26              		.loc 1 3 0
  27              		.cfi_startproc
  28 0000 80B5     		push	{r7, lr}
  29              	.LCFI0:
  30              		.cfi_def_cfa_offset 8
  31              		.cfi_offset 7, -8
  32              		.cfi_offset 14, -4
  33 0002 82B0     		sub	sp, sp, #8
  34              	.LCFI1:
  35              		.cfi_def_cfa_offset 16
  36 0004 00AF     		add	r7, sp, #0
  37              	.LCFI2:
  38              		.cfi_def_cfa_register 7
  39 0006 7860     		str	r0, [r7, #4]
  40 0008 3960     		str	r1, [r7]
   4:../src/main.c **** 	return x + y;
  41              		.loc 1 4 0
  42 000a 7A68     		ldr	r2, [r7, #4]
  43 000c 3B68     		ldr	r3, [r7]
  44 000e D318     		add	r3, r2, r3
   5:../src/main.c **** }
  45              		.loc 1 5 0
  46 0010 181C     		mov	r0, r3
  47 0012 BD46     		mov	sp, r7
  48 0014 02B0     		add	sp, sp, #8
  49              		@ sp needed for prologue
  50 0016 80BD     		pop	{r7, pc}
  51              		.cfi_endproc
  52              	.LFE0:
  54              		.section	.text.main,"ax",%progbits
  55              		.align	2
  56              		.global	main
  57              		.code	16
  58              		.thumb_func
  60              	main:
  61              	.LFB1:
   6:../src/main.c **** 
   7:../src/main.c **** int main(void) {
  62              		.loc 1 7 0
  63              		.cfi_startproc
  64 0000 80B5     		push	{r7, lr}
  65              	.LCFI3:
  66              		.cfi_def_cfa_offset 8
  67              		.cfi_offset 7, -8
  68              		.cfi_offset 14, -4
  69 0002 82B0     		sub	sp, sp, #8
  70              	.LCFI4:
  71              		.cfi_def_cfa_offset 16
  72 0004 00AF     		add	r7, sp, #0
  73              	.LCFI5:
  74              		.cfi_def_cfa_register 7
   8:../src/main.c **** 
   9:../src/main.c **** 	int i, j;
  10:../src/main.c **** 
  11:../src/main.c **** 	i = sum(1, 2);
  75              		.loc 1 11 0
  76 0006 0120     		mov	r0, #1
  77 0008 0221     		mov	r1, #2
  78 000a FFF7FEFF 		bl	sum
  79 000e 031C     		mov	r3, r0
  80 0010 7B60     		str	r3, [r7, #4]
  12:../src/main.c **** 	j = asm_sum(5, 6);
  81              		.loc 1 12 0
  82 0012 0520     		mov	r0, #5
  83 0014 0621     		mov	r1, #6
  84 0016 FFF7FEFF 		bl	asm_sum
  85 001a 031C     		mov	r3, r0
  86 001c 3B60     		str	r3, [r7]
  87              	.L3:
  13:../src/main.c **** 
  14:../src/main.c **** 	// Enter an infinite loop, just incrementing a counter
  15:../src/main.c **** 	volatile static int loop = 0;
  16:../src/main.c **** 	while (1) {
  17:../src/main.c **** 		loop++;
  88              		.loc 1 17 0 discriminator 1
  89 001e 034B     		ldr	r3, .L4
  90 0020 1B68     		ldr	r3, [r3]
  91 0022 5A1C     		add	r2, r3, #1
  92 0024 014B     		ldr	r3, .L4
  93 0026 1A60     		str	r2, [r3]
  18:../src/main.c **** 	}
  94              		.loc 1 18 0 discriminator 1
  95 0028 F9E7     		b	.L3
  96              	.L5:
  97 002a C046     		.align	2
  98              	.L4:
  99 002c 00000000 		.word	loop.3492
 100              		.cfi_endproc
 101              	.LFE1:
 103              		.bss
 104              		.align	2
 105              	loop.3492:
 106 0000 00000000 		.space	4
 107              		.text
 108              	.Letext0:
DEFINED SYMBOLS
                            *ABS*:00000000 main.c
     /tmp/ccpG7IPy.s:18     .text.sum:00000000 $t
     /tmp/ccpG7IPy.s:23     .text.sum:00000000 sum
     /tmp/ccpG7IPy.s:55     .text.main:00000000 $t
     /tmp/ccpG7IPy.s:60     .text.main:00000000 main
     /tmp/ccpG7IPy.s:99     .text.main:0000002c $d
     /tmp/ccpG7IPy.s:105    .bss:00000000 loop.3492
     /tmp/ccpG7IPy.s:104    .bss:00000000 $d
                     .debug_frame:00000010 $d

UNDEFINED SYMBOLS
asm_sum
