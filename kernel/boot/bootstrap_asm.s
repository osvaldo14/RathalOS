global entrypoint  ; the entry point symbol defined in kernel.ld

extern kernel_main

; Values for the multiboot header
MULTIBOOT_MAGIC        equ 0x1BADB002  ; multiboot magic value
MULTIBOOT_ALIGN        equ 1   ; load kernel and modules on page boundary
MULTIBOOT_MEMINFO      equ 2   ; provide kernel with memory info

MULTIBOOT_FLAGS        equ (MULTIBOOT_ALIGN|MULTIBOOT_MEMINFO)

; Magic + checksum + flags must equal 0!
MULTIBOOT_CHECKSUM     equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

;---------------------------------------------------------------------------------------------------
; .multiboot section
; This section must be located at the very beginning of the kernel image.

section .multiboot

; Mandatory part of the multiboot header
; see http://git.savannah.gnu.org/cgit/grub.git/tree/doc/multiboot.h?h=multiboot
dd MULTIBOOT_MAGIC
dd MULTIBOOT_FLAGS
dd MULTIBOOT_CHECKSUM

entrypoint:
	; code starts executing here
	cli  ; disable hardware interrupts

	; TODO :
	mov esp,stack
	mov ebp,esp
				 	; - Initialize the stack pointer and EBP (both to the same value)

	push ebx	 	; - Pass the multiboot info to the kernel
	Call kernel_main	; - Call the kernel entry point (C code)
					; ...
	

	; infinite loop (should never get here)
.forever:
	hlt
	jmp .forever

;---------------------------------------------------------------------------------------------------
; TODO : declare a .stack section for the kernel. It should at least be 1MB long. Given this stack
; area won t be initialized, the nobits keyword should be added when declaring the section.

section .stack nobits

resb 2097152
stack: 





