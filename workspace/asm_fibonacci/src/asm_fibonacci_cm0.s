 	.syntax unified
  .cpu cortex-m0
 	.align	2
 	.global	asm_fibonacci
 	.thumb
 	.thumb_func
asm_fibonacci:
  # key:
  # r0 is first parameter, n
  # r7 is frame pointer
  # r2 and r3 are temporary values for f(n-2) and f(n-1) 
  #   (a and b in notes)
  # r4 is a scratch value

  push {r7,lr}
  # only three variables per recurse
  sub sp, sp, #12 
  add r7, sp, #0
  # save n
  str r0, [r7, #4]
  # Check input for 0, 1, or >20
  cmp r0, #0
  beq end
  cmp r0, #1
  beq end
  cmp r0, #21
  bge end


  # Otherwise
#b:
  # a <- n
  ldr r2, [r7, #4]
  cmp r2, #2
  blt a
  # a - 1
  subs r2, r2, #1
  # n <- a
  mov r0, r2
  # this makes f(n-1)   
  bl asm_fibonacci
  # b = f(n-1)
  mov r3, r0        
a:
  # a <- n
  ldr r2, [r7, #4]
  # a - 2
  subs r2, r2, #2       
  # n <- a
  mov r0, r2
  bl asm_fibonacci 
  # a = f(n-2) 
  mov r2, r0       

  # Finally:
  adds r0, r2, r3
  b end
  

end: # just return n
  #mov $ret, r0
  mov sp, r7
  add sp, sp, #12
  pop {r7, pc}

