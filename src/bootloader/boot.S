
;;------------------------------------------------------------;;
;;   @author Gustaf Franzén :: https://github.com/BjorneEk    ;;
;;                    main bootloader                         ;;
;;------------------------------------------------------------;;



[bits 16]   ; specify this is to be compiled as 16 bit code
[org 0x7c00]

; where to load the kernel to
KERNEL_OFFSET equ 0x9000

; BIOS sets boot drive in 'dl'; store for later use
mov [BOOT_DRIVE], dl

; setup stack
mov bp, 0x8000
mov sp, bp


mov al, 't'
call pchar
mov al, 'e'
call pchar
mov al, 'a'
call pchar
mov al, 'p'
call pchar
mov al, 'o'
call pchar
mov al, 't'
call pchar
mov al, '-'
call pchar
mov al, 'O'
call pchar
mov al, 'S'
call pchar
mov al, ' '
call pchar
mov al, 'b'
call pchar
mov al, 'o'
call pchar
mov al, 'o'
call pchar
mov al, 't'
call pchar
mov al, 'i'
call pchar
mov al, 'n'
call pchar
mov al, 'g'
call pchar

; switch video mode to 640 x 480 graphical mode
call set_video_mode
call load_kernel
call switch_to_32bit
jmp $

pchar:
	mov ah, 0x0e
	int 0x10
	ret

set_video_mode:
	mov al, 0x13
	mov ah, 0
	int 0x10
	ret

%include "src/bootloader/disk.S"
%include "src/bootloader/gdt.S"
%include "src/bootloader/switch-to-32bit.S"

[bits 16]
load_kernel:
	mov bx, KERNEL_OFFSET  ; bx -> destination
	mov dh, 55             ; dh -> num sectors
	mov dl, [BOOT_DRIVE]   ; dl -> disk
	call disk_read
	ret

[bits 32]
BEGIN_32BIT:
	call KERNEL_OFFSET ; give control to the kernel
	jmp $ ; loop in case kernel returns

; boot drive variable
BOOT_DRIVE db 0

times 510-($-$$) db 0
db 0x55, 0xaa
