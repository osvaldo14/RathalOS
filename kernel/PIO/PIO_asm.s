global outb
global outw
global inb
global inw

section .text

outb:
	push 	ebp
	mov 	ebp,esp

	mov		dx,[ebp+8]
	mov		al,[ebp+12]
	out 	dx,al

	mov		eax,0

	leave
	ret

outw:
	push 	ebp
	mov 	ebp,esp

	mov		dx,[ebp+8]
	mov		ax,[ebp+12]
	out 	dx,ax

	mov		eax,0

	leave
	ret


inb:
	push 	ebp
	mov 	ebp,esp

	mov		dx,[ebp+8]
	in 		al,dx

	leave
	ret

inw:
	push 	ebp
	mov 	ebp,esp

	mov		dx,[ebp+8]
	in 		ax,dx

	leave
	ret