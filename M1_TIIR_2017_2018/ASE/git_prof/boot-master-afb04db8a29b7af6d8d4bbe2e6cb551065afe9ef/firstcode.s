;-------------------------------------
;---- My very first piece of code ----
;-------------------------------------

org	0x7c00			; The BIOS will copy the bootsector at 0x7C00 and jump
bits	16			; The bootsector will be started in the hugly 8086 "Real Mode"

entrypoint:
	cli			; suspend all interruptions
	mov ax,cs		; use the code segment as a data segment for the source
	mov ds,ax                     
	mov si,msg		; ds:si contain the address of the msg
	mov ax,0x0b800		; 0xb80000 is the video address (text mode)
	mov es,ax
	mov di,0		; es:di (=0xb800 x 16 + 0) contain the video address

	mov cx,4000		; counter = 80 x 25 x 2 bytes (text matrix size)     
	mov al,0		; we will fill the video memory with 0 (clear)
clear_screen:
	stosb			; store the byte al at the address es:di and increment di
       	loop clear_screen	; loop to clear_screen until cx == 0

	mov di,0		; es:di contain the address of the first byte of the video address
	mov cx,12		; count register = 12 
	mov al,byte 0x70	; 0x70=0 111 0000 => 0=No blink 111=background color 7 0000=firstground 0
print_msg:
	movsb			; copy a byte from ds:si (msg) to es:di (video buffer) and inc si and di
	stosb			; copy al in es:di and inc di
	loop print_msg		; loop for each byte of the msg...

halt:				; never ending loop
	jmp halt		; 

	hlt                 	; halt the system

msg:								
	db "Hello World!"	; store this ascii sequence in the memory at address msg
times 510 - ($-$$) db 0		; a bootsector is 512 bytes long... it set all unused bytes to 0

	db 0x55,0xAA		; excepted the last two set to 0x55 and 0xAA => the Boot Signature
				; the bios only run a bootsector with a 0x55 0xAA terminal bytes.
