.data

a: .double 2.5

b: .double 3.0

c: .double 0.0
.text

.globl get_fpu_control_word

.type get_fpu_control_word, @function



.globl get_status

.type get_status,@function

.globl miernik
.type miernik,@function



.globl change_precision

.type change_precision,@function



get_status:

pushl %ebp # zachowaj bazę stosu

movl %esp, %ebp # nowa rama stosu

fnstsw %ax

leave # przywróć stos (odpowiada mov esp, ebp + pop ebp)

ret



get_fpu_control_word:

   pushl %ebp # zachowaj bazę stosu

   movl %esp, %ebp # nowa rama stosu

   subl $4, %esp

   fstcw (%esp)

   xorl %eax,%eax

   mov (%esp),%ax

   leave

   ret





change_precision:

   pushl %ebp

   movl %esp, %ebp

   subl $4, %esp # rezerwujemy 4 bajty pod CW



   fstcw -4(%ebp) # zapisz CW do lokalnej zmiennej



   movw -4(%ebp), %ax # załaduj CW do AX

   andw $0xFCFF, %ax # wyczyść bity 8–9 (PC)

   orw $0x0000, %ax # ustaw PC = 10 → double precision (64-bit)

   movw %ax, -4(%ebp) # zapisz zmieniony CW z powrotem



   fldcw -4(%ebp) # załaduj CW do FPU



   xorl %eax, %eax # zwróć 0 (opcjonalnie)



   leave # PRZYWRÓĆ %ebp i stos

   ret # Wróć do wywołującego


miernik:
  
  xorl %eax,%eax
  push %ebx
  cpuid
  rdtsc
  pop %ebx
  ret 
