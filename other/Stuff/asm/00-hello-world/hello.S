.data

msg:
    .ascii  "Hello, world!\n"
    len = . - msg


.text

    .global _start


_start:


    pushq   %rbp
    movq    %rsp,%rbp

    movq    $msg,%rdi
    call    puts

    pop     %rbp
    movl    $0,%eax
    ret

