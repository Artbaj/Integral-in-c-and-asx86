

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
	fstpl dividend      #reseting dividend
	
    powerLoop:
		cmp %ecx,%eax
		jae doneP
		fldl dividend          # ST(0) = dividend
		fldl 8(%ebp)              # ST(0) = x, ST(1) = dividend
		fmul %st(1), %st(0)   
		fstpl dividend 
		call cleanfpu
		incl %eax
		jmp powerLoop

	doneP:
	xorl %eax,%eax
    fldl dividend
    popl %ebx
    leave
	ret
	
cleanfpu:
	mov $8 ,%edx
	popLoop:
	cmp $0 ,%edx
	jb cleaned
	fstp %st(0) 
    decl %edx
cleaned:
ret
