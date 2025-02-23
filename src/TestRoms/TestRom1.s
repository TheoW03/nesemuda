; sekelton if you want to add on to the tests

; for testing the CRT affect shader
.segment "HEADER"
  ; .byte "NES", $1A      ; iNES header identifier
  .byte $4E, $45, $53, $1A
  .byte 2               ; 2x 16KB PRG code
  .byte 1               ; 1x  8KB CHR data
  .byte $01, $00        ; mapper 0, vertical mirroring
.segment "VECTORS"
  ;; When an NMI happens (once per frame if enabled) the label nmi:
    .addr nmi
    ;; When the processor first turns on or is reset, it will jump to the label reset:
    .addr reset ; reset vector
.segment "STARTUP"
reset:
  LDA #42        ; Immediate Mode: Load the value $42 into A
    LDA $2001       ; Absolute Mode: Load value from memory address $2000
    LDA $20         ; Zero Page Mode: Load value from address $0020
    LDA $20,X       ; Zero Page,X Mode: Load from address $0020 + X
    LDA $2000,X     ; Absolute,X Mode: Load from $2000 + X
    LDA $2000,Y     ; Absolute,Y Mode: Load from $2000 + Y
    LDA ($20,X)     ; Indirect,X Mode: Load from address stored at ($20 + X)
    LDA ($20),Y 
    l2:
      jmp l2
nmi:
    rti   
.segment "CHARS" ; for graphics
; .incbin  "rom.chr"