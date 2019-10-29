%include "../const.inc"
extern exception_handler
extern irq_handler

section .text   ; start of the text (code) section

;------------------------------------------------
; Load the IDT
global idt_load
idt_load:
    mov eax,[esp+4]
    lidt [eax]
    ret

;------------------------------------------------
; CPU exceptions exemples

global _exception0
_exception0:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    0  ; exception number
    jmp     exception_wrapper

global _exception1
_exception1:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    1  ; exception number
    jmp     exception_wrapper

global _exception2
_exception2:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    2  ; exception number
    jmp     exception_wrapper

global _exception3
_exception3:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    3  ; exception number
    jmp     exception_wrapper

global _exception4
_exception4:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    4  ; exception number
    jmp     exception_wrapper

global _exception5
_exception5:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    5  ; exception number
    jmp     exception_wrapper

global _exception6
_exception6:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    6  ; exception number
    jmp     exception_wrapper

global _exception7
_exception7:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    7  ; exception number
    jmp     exception_wrapper

global _exception9
_exception9:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    9  ; exception number
    jmp     exception_wrapper

global _exception15
_exception15:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    15  ; exception number
    jmp     exception_wrapper

global _exception16
_exception16:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    16  ; exception number
    jmp     exception_wrapper

global _exception18
_exception18:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    18  ; exception number
    jmp     exception_wrapper

global _exception19
_exception19:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    19  ; exception number
    jmp     exception_wrapper

global _exception20
_exception20:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    20  ; exception number
    jmp     exception_wrapper

;-------------------------------------
;-------------------------------------

global _exception8
_exception8:
    cli          ; disable interrupts
    push    8  ; exception number
    jmp     exception_wrapper

global _exception10
_exception10:
    cli          ; disable interrupts
    push    10  ; exception number
    jmp     exception_wrapper

global _exception11
_exception11:
    cli          ; disable interrupts
    push    11  ; exception number
    jmp     exception_wrapper

global _exception12
_exception12:
    cli          ; disable interrupts
    push    12  ; exception number
    jmp     exception_wrapper

global _exception13
_exception13:
    cli          ; disable interrupts
    push    13  ; exception number
    jmp     exception_wrapper

global _exception14
_exception14:
    cli          ; disable interrupts
    push    14  ; exception number
    jmp     exception_wrapper

global _exception17
_exception17:
    cli          ; disable interrupts
    push    17  ; exception number
    jmp     exception_wrapper

;------------------------------------------------
; IRQ

global _IRQexception0
_IRQexception0:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    0  ; irq number
    jmp     irq_wrapper

global _IRQexception1
_IRQexception1:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    1  ; irq number
    jmp     irq_wrapper

global _IRQexception2
_IRQexception2:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    2  ; irq number
    jmp     irq_wrapper

global _IRQexception3
_IRQexception3:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    3  ; irq number
    jmp     irq_wrapper

global _IRQexception4
_IRQexception4:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    4  ; irq number
    jmp     irq_wrapper

global _IRQexception5
_IRQexception5:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    5  ; irq number
    jmp     irq_wrapper

global _IRQexception6
_IRQexception6:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    6  ; irq number
    jmp     irq_wrapper

global _IRQexception7
_IRQexception7:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    7  ; irq number
    jmp     irq_wrapper

global _IRQexception8
_IRQexception8:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    8  ; irq number
    jmp     irq_wrapper

global _IRQexception9
_IRQexception9:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    9  ; irq number
    jmp     irq_wrapper

global _IRQexception10
_IRQexception10:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    10  ; irq number
    jmp     irq_wrapper

global _IRQexception11
_IRQexception11:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    11  ; irq number
    jmp     irq_wrapper

global _IRQexception12
_IRQexception12:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    12  ; irq number
    jmp     irq_wrapper

global _IRQexception13
_IRQexception13:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    13  ; irq number
    jmp     irq_wrapper

global _IRQexception14
_IRQexception14:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    14  ; irq number
    jmp     irq_wrapper

global _IRQexception15
_IRQexception15:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    15  ; irq number
    jmp     irq_wrapper

;------------------------------------------------
; Wrapper for exceptions

exception_wrapper:
    ; Save all registers
    push    eax
    push    ebx
    push    ecx
    push    edx
    push    esi
    push    edi
    push    ebp
    push    ds
    push    es
    push    fs
    push    gs

    ; Load kernel data descriptor into all segments
    mov     ax,GDT_KERNEL_DATA_SELECTOR
    mov     ds,ax
    mov     es,ax
    mov     fs,ax
    mov     gs,ax

    ; Pass the stack pointer (which gives the CPU context) to the C function
    mov     eax,esp
    push    eax
    call    exception_handler  ; implemented in idt.c
    pop     eax  ; only here to balance the "push eax" done before the call

    ; Restore all registers
    pop     gs
    pop     fs
    pop     es
    pop     ds
    pop     ebp
    pop     edi
    pop     esi
    pop     edx
    pop     ecx
    pop     ebx
    pop     eax
    
	; Fix the stack pointer due to the 2 push done before the call to
	; exception_wrapper: error code and exception/irq number
    add     esp,8
    iret

;------------------------------------------------
; Wrapper for exceptions

irq_wrapper:
	; Save all registers
    push    eax
    push    ebx
    push    ecx
    push    edx
    push    esi
    push    edi
    push    ebp
    push    ds
    push    es
    push    fs
    push    gs

    ; Load kernel data descriptor into all segments
    mov     ax,GDT_KERNEL_DATA_SELECTOR
    mov     ds,ax
    mov     es,ax
    mov     fs,ax
    mov     gs,ax

    ; Pass the stack pointer (which gives the CPU context) to the C function
    mov     eax,esp
    push    eax
    call    irq_handler ; implemented in idt.c
    pop     eax  ; only here to balance the "push eax" done before the call

    ; Restore all registers
    pop     gs
    pop     fs
    pop     es
    pop     ds
    pop     ebp
    pop     edi
    pop     esi
    pop     edx
    pop     ecx
    pop     ebx
    pop     eax
    
    ; Fix the stack pointer due to the 2 push done before the call to
    ; exception_wrapper: error code and exception/irq number
    add     esp,8
    iret
