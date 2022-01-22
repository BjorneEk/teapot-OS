; bootloader

jmp $

times 510-($-$$) db 0 ; fill 510 bytes - code above with 0
db 0x55, 0xaf         ; set last 2 bytes making the total 512
