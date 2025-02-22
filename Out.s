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
.SEGMENT "STARTUP" 
reset: 
lda #1
nmi: 
