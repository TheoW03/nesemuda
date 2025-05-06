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
    LDA $2000, X     ; Absolute,X Mode: Load from $2000 + X
    LDA $2000,Y     ; Absolute,Y Mode: Load from $2000 + Y
    LDA ($20,X)     ; Indirect,X Mode: Load from address stored at ($20 + X)
    LDA ($20),Y 
    LDA t2
;     LDA #42        ; Immediate Mode: Load the value $42 into A
;     LDA $2001       ; Absolute Mode: Load value from memory address $2000
;     LDA $20         ; Zero Page Mode: Load value from address $0020
;     LDA $20,X       ; Zero Page,X Mode: Load from address $0020 + X
;     LDA $2000, X     ; Absolute,X Mode: Load from $2000 + X
;     LDA $2000,Y     ; Absolute,Y Mode: Load from $2000 + Y
;     LDA ($20,X)     ; Indirect,X Mode: Load from address stored at ($20 + X)
;     LDA ($20),Y 
;   lda test
;   ; jmp test
;   ; jsr test
;   ldx #1
;   ldy #1
;   jsr test
;   jmp test
;       .byte $12, $32, $22, $32

;   ; jsr test
;   ; .byte $12, $32, $22, $32 T

; ; reset:

;     ; jsr test

; ;     ; LDY #1
; ;     ; LDY $20
; ;     ; LDY $20, X
; ;     ; LDY $2000
; ;     ; LDY $2000, X


; ;     ; LDX #1
; ;     ; LDX $20
;     ; LDX $20, Y
; ;     ; LDX $2000
; ;     ; LDX $2000, Y

; ;     clc
; ;     sec
; ;     cld
; ;     sed
; ;     cli
; ;     sei
; ;     clv

; ;     jmp reset 
; ;     l3: 
; ;       lda #1
; ;       ; rti
; ;       ; jmp l2
; ;       L4:
; ;       bne L4
; ;       bpl nmi
; ;       bcc nmi
; ;       bcs nmi
; ;       bmi nmi
; ;       jmp l2
; ;       ; lda #1
; ;     ; .byte $82, $29
; ;     ; .byte $1
; nmi:
; lda #1
; lda #2
; lda #1
jmp test
nmi:
lda t2
; jmp test2
rti
t2:
  lda #32
  lda #11
test:
  lda #64
  jmp t2

test2:
  jmp test

; l2:      
;   lda $01
;   ; jmp l3
;   beq nmi
;   bne nmi
;   jmp l3

; test:
  ; lda #1
  ; rts
.segment "CHARS" ; for graphics
; .incbin  "rom.chr"