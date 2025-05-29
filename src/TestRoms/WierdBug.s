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
beq L81
L81: 
lda $204 
cmp $210 
bcs L80
lda $204 
cmp $210 
beq L80
jmp reset
L80: 
lda $203 
cmp $213 
beq L90
lda $207 
cmp $213 
beq L90

L90: 
jsr awa
jsr awa
ldx #1
stx $25
jmp nmi

awa:
    rts
nmi:
    rti

.SEGMENT "CHARS"