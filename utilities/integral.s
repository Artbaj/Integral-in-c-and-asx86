

.data
dividend: .double 0.0
one: .double 1.0
sum: .double 0.0
 
	
  

.text

.globl evaluate

.type evaluate @function



evaluate: 
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx 
    mov $1,%eax
    mov 24(%ebp),%ecx
    cmp $0,%ecx
    jl negPower
    je zeroPower
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
	

     negPower:
      	fldl 8(%ebp)
        fldz             
        fcomip %st(1), %st(0)  
        fstp  %st(0)      
        ja  divByZero 
        fldl 8(%ebp)           
        fldl 8(%ebp)
        incl %ecx
        negPowerLoop:
            test %ecx,%ecx
            jz doneNeg
            fmul %st(1),%st(0)  
            incl %ecx
		    jmp negPowerLoop 

    doneNeg:
        xorl %eax,%eax
        fstp %st(1)
        fdivrl one
        fmull 16(%ebp)
        popl %ebx
        leave
        ret

   divByZero:
        fld1            
        fchs
        fsqrt
        leave 
        ret

    zeroPower:
        fldl 8(%ebp)
        leave
        ret

