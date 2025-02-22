.SEGMENT "HEADER" 
	   .byte $4E, $45, $53, $1A  
 	   .byte 2
	   .byte 1
	   .byte $01,$00
	   .byte $00
	   .byte $00
	   .byte $00
.segment "VECTORS"
  ;; When an NMI happens (once per frame if enabled) the label nmi:
    .addr nmi
    ;; When the processor first turns on or is reset, it will jump to the label reset:
    .addr reset ; reset vector
.segment "STARTUP"
reset:
   lda #01
nmi:
    rti   
.segment "CHARS" ; for graphics
; .incbin  "rom.chr"