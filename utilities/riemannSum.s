

.data
dividend: .double 0.0
sum: .double 0.0
 
	
  

.text

.globl riemannSum

.type riemannSum @function



riemannSum: 
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx 
    mov $1,%eax
    mov 24(%ebp),%ecx
	fldl 8(%ebp)           
    fldl 8(%ebp)           
    powerLoop:
		cmp %ecx,%eax
		jae doneP
        fmul %st(1),%st(0)  
		incl %eax
		jmp powerLoop

	doneP:
	xorl %eax,%eax
    fstp %st(1)
    fmull 16(%ebp)
    popl %ebx
    leave
	ret
	

