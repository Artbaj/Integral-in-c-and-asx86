

.data
dividend: .double 0.0
divider: .double 0.0
sum: .double 0.0
 
	
  

.text

.globl powerOpt

.type powerOpt, @function



powerOpt:
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx 
    mov $1,%eax
    mov 16(%ebp),%ecx
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
    popl %ebx
    leave
	ret
	

