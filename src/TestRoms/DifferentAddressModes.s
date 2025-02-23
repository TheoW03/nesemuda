

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
;     LDA #$42        ; Immediate Mode: Load the value $42 into A
;     LDA $2000       ; Absolute Mode: Load value from memory address $2000
;     LDA $20         ; Zero Page Mode: Load value from address $0020
;     LDA $20,X       ; Zero Page,X Mode: Load from address $0020 + X
;     LDA $2000,X     ; Absolute,X Mode: Load from $2000 + X
;     LDA $2000,Y     ; Absolute,Y Mode: Load from $2000 + Y
    LDA ($20,X)     ; Indirect,X Mode: Load from address stored at ($20 + X)
    LDA ($20),Y     ; Indirect,Y Mode: Load from address at ($20) + Y
nmi:
    rti