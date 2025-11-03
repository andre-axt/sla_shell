.section .data
    space: .asciz " "
    newline: .asciz "\n"
    buffer: .space 1024

.section .text
.global echo2
.global strlen2
.global pwd2

strlen2:
    mov $0, %rax

strlen2_loop:
    cmpb $0, (%rdi)      
    je strlen2_end
    inc %rax
    inc %rdi
    jmp strlen2_loop

strlen2_end:
    ret

echo2:
    push %r12
    push %r13            
    mov %rdi, %r12
    mov $1, %r13
    
echo2_loop:
    mov (%r12, %r13, 8), %rdi
    test %rdi, %rdi
    jz echo2_end       

    call print_string

    inc %r13
    mov (%r12, %r13, 8), %rdi
    test %rdi, %rdi
    jz echo2_newline

    mov $space, %rdi
    call print_string
    jmp echo2_loop

echo2_newline:
    mov $newline, %rdi
    call print_string

echo2_end:
    pop %r13
    pop %r12
    ret

print_string:         
    push %rdi
    call strlen2
    pop %rsi

    mov %rax, %rdx
    mov $1, %rax
    mov $1, %rdi
    syscall
    ret

pwd2:
    mov $79, %rax
    mov $buffer, %rdi
    mov $1024, %rsi
    syscall

    call print_string
    
    mov $newline, %rdi
    call print_string
    ret