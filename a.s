.SEGMENT "HEADER" 
	   .byte $4E, $45, $53, $1A  
 	   .byte 2
	   .byte 1
	   .byte $01,$00
	   .byte $00
	   .byte $00
	   .byte $00
.SEGMENT "VECTORS" 
.addr reset 
.addr nmi 
.SEGMENT "STARTUP" 
reset: 
lda #42
lda $2001 
lda $20
lda $20, X 
lda $2000, X 
lda $2000, Y 
lda ($20, X )
lda ($20), Y 
L0: 
jmp L0
nmi: 
rti 
