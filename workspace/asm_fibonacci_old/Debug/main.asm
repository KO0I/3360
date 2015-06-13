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
  17              		.section	.rodata
  18              		.align	2
  19              	.LC0:
  20 0000 BF000000 		.word	191
  21 0004 AF000000 		.word	175
  22 0008 A7000000 		.word	167
  23 000c A3000000 		.word	163
  24 0010 A1000000 		.word	161
  25 0014 A0000000 		.word	160
  26 0018 B0000000 		.word	176
  27 001c B8000000 		.word	184
  28 0020 BC000000 		.word	188
  29 0024 BE000000 		.word	190
  30 0028 50000000 		.word	80
  31 002c 90000000 		.word	144
  32 0030 94000000 		.word	148
  33 0034 88000000 		.word	136
  34 0038 30000000 		.word	48
  35 003c 84000000 		.word	132
  36              		.section	.text.morse,"ax",%progbits
  37              		.align	2
  38              		.global	morse
  39              		.code	16
  40              		.thumb_func
  42              	morse:
  43              	.LFB32:
  44              		.file 1 "../src/main.c"
   1:../src/main.c **** #include "LPC11Uxx.h"
   2:../src/main.c **** #include "uart.h"
   3:../src/main.c **** #include "timer32.h"
   4:../src/main.c **** #include "gpio.h"
   5:../src/main.c **** #include "stdio.h"
   6:../src/main.c **** 
   7:../src/main.c **** 
   8:../src/main.c **** extern volatile uint32_t UARTCount;
   9:../src/main.c **** extern volatile uint8_t UARTBuffer[0x40];
  10:../src/main.c **** //static uint32_t DebugUpdateCounter = 0;
  11:../src/main.c **** 
  12:../src/main.c **** extern int asm_fibonacci(int x);
  13:../src/main.c **** 
  14:../src/main.c **** 
  15:../src/main.c **** 
  16:../src/main.c **** // Lookup Table:
  17:../src/main.c **** unsigned char morse(unsigned char n){
  45              		.loc 1 17 0
  46              		.cfi_startproc
  47 0000 80B5     		push	{r7, lr}
  48              	.LCFI0:
  49              		.cfi_def_cfa_offset 8
  50              		.cfi_offset 7, -8
  51              		.cfi_offset 14, -4
  52 0002 92B0     		sub	sp, sp, #72
  53              	.LCFI1:
  54              		.cfi_def_cfa_offset 80
  55 0004 00AF     		add	r7, sp, #0
  56              	.LCFI2:
  57              		.cfi_def_cfa_register 7
  58 0006 021C     		mov	r2, r0
  59 0008 FB1D     		add	r3, r7, #7
  60 000a 1A70     		strb	r2, [r3]
  18:../src/main.c ****   unsigned int lut[16] = {
  61              		.loc 1 18 0
  62 000c 3A1C     		mov	r2, r7
  63 000e 0832     		add	r2, r2, #8
  64 0010 094B     		ldr	r3, .L2
  65 0012 111C     		mov	r1, r2
  66 0014 1A1C     		mov	r2, r3
  67 0016 4023     		mov	r3, #64
  68 0018 081C     		mov	r0, r1
  69 001a 111C     		mov	r1, r2
  70 001c 1A1C     		mov	r2, r3
  71 001e FFF7FEFF 		bl	memcpy
  19:../src/main.c **** // symbol: | 3 bits len | 5 bits symbol |
  20:../src/main.c ****     0b10111111,   // Value is 0
  21:../src/main.c ****     0b10101111,   // Value is 1
  22:../src/main.c ****     0b10100111,
  23:../src/main.c ****     0b10100011,
  24:../src/main.c ****     0b10100001,
  25:../src/main.c ****     0b10100000,
  26:../src/main.c ****     0b10110000,
  27:../src/main.c ****     0b10111000,
  28:../src/main.c ****     0b10111100,
  29:../src/main.c ****     0b10111110,
  30:../src/main.c ****     0b01010000,   //  .-      A
  31:../src/main.c ****     0b10010000,   //  _...    B
  32:../src/main.c ****     0b10010100,   //  -.-.    C
  33:../src/main.c ****     0b10001000,   //  .-..    D
  34:../src/main.c ****     0b00110000,   //  .       E
  35:../src/main.c ****     0b10000100    //  ..-.    F
  36:../src/main.c ****   };
  37:../src/main.c ****   if((n >= 0) || (n <= 16)){
  38:../src/main.c ****     return lut[n];
  72              		.loc 1 38 0
  73 0022 FB1D     		add	r3, r7, #7
  74 0024 1A78     		ldrb	r2, [r3]
  75 0026 3B1C     		mov	r3, r7
  76 0028 0833     		add	r3, r3, #8
  77 002a 9200     		lsl	r2, r2, #2
  78 002c D358     		ldr	r3, [r2, r3]
  79 002e DBB2     		uxtb	r3, r3
  39:../src/main.c ****   }
  40:../src/main.c ****   else return -1;
  41:../src/main.c **** }
  80              		.loc 1 41 0
  81 0030 181C     		mov	r0, r3
  82 0032 BD46     		mov	sp, r7
  83 0034 12B0     		add	sp, sp, #72
  84              		@ sp needed for prologue
  85 0036 80BD     		pop	{r7, pc}
  86              	.L3:
  87              		.align	2
  88              	.L2:
  89 0038 00000000 		.word	.LC0
  90              		.cfi_endproc
  91              	.LFE32:
  93              		.section	.text.fibonacci,"ax",%progbits
  94              		.align	2
  95              		.global	fibonacci
  96              		.code	16
  97              		.thumb_func
  99              	fibonacci:
 100              	.LFB33:
  42:../src/main.c **** 
  43:../src/main.c **** unsigned int fibonacci(unsigned int n){
 101              		.loc 1 43 0
 102              		.cfi_startproc
 103 0000 90B5     		push	{r4, r7, lr}
 104              	.LCFI3:
 105              		.cfi_def_cfa_offset 12
 106              		.cfi_offset 4, -12
 107              		.cfi_offset 7, -8
 108              		.cfi_offset 14, -4
 109 0002 83B0     		sub	sp, sp, #12
 110              	.LCFI4:
 111              		.cfi_def_cfa_offset 24
 112 0004 00AF     		add	r7, sp, #0
 113              	.LCFI5:
 114              		.cfi_def_cfa_register 7
 115 0006 7860     		str	r0, [r7, #4]
  44:../src/main.c ****   if(n==0) return 0;
 116              		.loc 1 44 0
 117 0008 7B68     		ldr	r3, [r7, #4]
 118 000a 002B     		cmp	r3, #0
 119 000c 01D1     		bne	.L5
 120              		.loc 1 44 0 is_stmt 0 discriminator 1
 121 000e 0023     		mov	r3, #0
 122 0010 16E0     		b	.L6
 123              	.L5:
  45:../src/main.c ****   else if(n==1) return 1;
 124              		.loc 1 45 0 is_stmt 1
 125 0012 7B68     		ldr	r3, [r7, #4]
 126 0014 012B     		cmp	r3, #1
 127 0016 01D1     		bne	.L7
 128              		.loc 1 45 0 is_stmt 0 discriminator 1
 129 0018 0123     		mov	r3, #1
 130 001a 11E0     		b	.L6
 131              	.L7:
  46:../src/main.c ****   else if((n>20)||(n<0)) return 1;
 132              		.loc 1 46 0 is_stmt 1
 133 001c 7B68     		ldr	r3, [r7, #4]
 134 001e 142B     		cmp	r3, #20
 135 0020 01D9     		bls	.L8
 136              		.loc 1 46 0 is_stmt 0 discriminator 1
 137 0022 0123     		mov	r3, #1
 138 0024 0CE0     		b	.L6
 139              	.L8:
  47:../src/main.c ****   else{
  48:../src/main.c ****     return (fibonacci(n-1) + fibonacci(n-2));
 140              		.loc 1 48 0 is_stmt 1
 141 0026 7B68     		ldr	r3, [r7, #4]
 142 0028 013B     		sub	r3, r3, #1
 143 002a 181C     		mov	r0, r3
 144 002c FFF7FEFF 		bl	fibonacci
 145 0030 041C     		mov	r4, r0
 146 0032 7B68     		ldr	r3, [r7, #4]
 147 0034 023B     		sub	r3, r3, #2
 148 0036 181C     		mov	r0, r3
 149 0038 FFF7FEFF 		bl	fibonacci
 150 003c 031C     		mov	r3, r0
 151 003e E318     		add	r3, r4, r3
 152              	.L6:
  49:../src/main.c ****   }
  50:../src/main.c **** }
 153              		.loc 1 50 0
 154 0040 181C     		mov	r0, r3
 155 0042 BD46     		mov	sp, r7
 156 0044 03B0     		add	sp, sp, #12
 157              		@ sp needed for prologue
 158 0046 90BD     		pop	{r4, r7, pc}
 159              		.cfi_endproc
 160              	.LFE33:
 162              		.section	.rodata
 163              		.align	2
 164              	.LC3:
 165 0040 257300   		.ascii	"%s\000"
 166 0043 00       		.section	.text.main,"ax",%progbits
 167              		.align	2
 168              		.global	main
 169              		.code	16
 170              		.thumb_func
 172              	main:
 173              	.LFB34:
  51:../src/main.c **** 
  52:../src/main.c **** int main(void) {
 174              		.loc 1 52 0
 175              		.cfi_startproc
 176 0000 80B5     		push	{r7, lr}
 177              	.LCFI6:
 178              		.cfi_def_cfa_offset 8
 179              		.cfi_offset 7, -8
 180              		.cfi_offset 14, -4
 181 0002 82B0     		sub	sp, sp, #8
 182              	.LCFI7:
 183              		.cfi_def_cfa_offset 16
 184 0004 00AF     		add	r7, sp, #0
 185              	.LCFI8:
 186              		.cfi_def_cfa_register 7
  53:../src/main.c **** 
  54:../src/main.c **** 	int i;
  55:../src/main.c **** 	uint32_t j;
  56:../src/main.c ****   UARTInit(9600);
 187              		.loc 1 56 0
 188 0006 9623     		mov	r3, #150
 189 0008 9B01     		lsl	r3, r3, #6
 190 000a 181C     		mov	r0, r3
 191 000c FFF7FEFF 		bl	UARTInit
 192              	.L10:
  57:../src/main.c **** 
  58:../src/main.c ****   while(1) {
  59:../src/main.c **** 	j = 0;
 193              		.loc 1 59 0 discriminator 1
 194 0010 0023     		mov	r3, #0
 195 0012 7B60     		str	r3, [r7, #4]
  60:../src/main.c ****     UARTBuffer[j++] = 'b';
 196              		.loc 1 60 0 discriminator 1
 197 0014 124A     		ldr	r2, .L11
 198 0016 7B68     		ldr	r3, [r7, #4]
 199 0018 D318     		add	r3, r2, r3
 200 001a 6222     		mov	r2, #98
 201 001c 1A70     		strb	r2, [r3]
 202 001e 7B68     		ldr	r3, [r7, #4]
 203 0020 0133     		add	r3, r3, #1
 204 0022 7B60     		str	r3, [r7, #4]
  61:../src/main.c ****     UARTBuffer[j++] = '\r';
 205              		.loc 1 61 0 discriminator 1
 206 0024 0E4A     		ldr	r2, .L11
 207 0026 7B68     		ldr	r3, [r7, #4]
 208 0028 D318     		add	r3, r2, r3
 209 002a 0D22     		mov	r2, #13
 210 002c 1A70     		strb	r2, [r3]
 211 002e 7B68     		ldr	r3, [r7, #4]
 212 0030 0133     		add	r3, r3, #1
 213 0032 7B60     		str	r3, [r7, #4]
  62:../src/main.c ****     UARTBuffer[j++] = '\n';
 214              		.loc 1 62 0 discriminator 1
 215 0034 0A4A     		ldr	r2, .L11
 216 0036 7B68     		ldr	r3, [r7, #4]
 217 0038 D318     		add	r3, r2, r3
 218 003a 0A22     		mov	r2, #10
 219 003c 1A70     		strb	r2, [r3]
 220 003e 7B68     		ldr	r3, [r7, #4]
 221 0040 0133     		add	r3, r3, #1
 222 0042 7B60     		str	r3, [r7, #4]
  63:../src/main.c ****     UARTSend( (uint8_t *)UARTBuffer, j );
 223              		.loc 1 63 0 discriminator 1
 224 0044 064A     		ldr	r2, .L11
 225 0046 7B68     		ldr	r3, [r7, #4]
 226 0048 101C     		mov	r0, r2
 227 004a 191C     		mov	r1, r3
 228 004c FFF7FEFF 		bl	UARTSend
  64:../src/main.c ****     printf("%s",UARTBuffer);
 229              		.loc 1 64 0 discriminator 1
 230 0050 044A     		ldr	r2, .L11+4
 231 0052 034B     		ldr	r3, .L11
 232 0054 101C     		mov	r0, r2
 233 0056 191C     		mov	r1, r3
 234 0058 FFF7FEFF 		bl	printf
  65:../src/main.c ****   } // end of while loop
 235              		.loc 1 65 0 discriminator 1
 236 005c D8E7     		b	.L10
 237              	.L12:
 238 005e C046     		.align	2
 239              	.L11:
 240 0060 00000000 		.word	UARTBuffer
 241 0064 40000000 		.word	.LC3
 242              		.cfi_endproc
 243              	.LFE34:
 245              		.text
 246              	.Letext0:
 247              		.file 2 "/usr/local/lpcxpresso_5.2.6_2137/lpcxpresso/tools/bin/../lib/gcc/arm-none-eabi/4.6.2/../.
DEFINED SYMBOLS
                            *ABS*:00000000 main.c
     /tmp/ccCXHGEh.s:18     .rodata:00000000 $d
     /tmp/ccCXHGEh.s:37     .text.morse:00000000 $t
     /tmp/ccCXHGEh.s:42     .text.morse:00000000 morse
     /tmp/ccCXHGEh.s:89     .text.morse:00000038 $d
     /tmp/ccCXHGEh.s:94     .text.fibonacci:00000000 $t
     /tmp/ccCXHGEh.s:99     .text.fibonacci:00000000 fibonacci
     /tmp/ccCXHGEh.s:167    .text.main:00000000 $t
     /tmp/ccCXHGEh.s:172    .text.main:00000000 main
     /tmp/ccCXHGEh.s:240    .text.main:00000060 $d
                     .debug_frame:00000010 $d

UNDEFINED SYMBOLS
memcpy
UARTInit
UARTSend
printf
UARTBuffer
