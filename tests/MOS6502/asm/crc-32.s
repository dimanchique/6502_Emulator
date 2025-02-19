CRC    = $6          	 ; 4 bytes in ZP
CRCT0  = $8000       	 ; Four 256-byte tables
CRCT1  = $8100       	 ; (should be page-aligned for speed)
CRCT2  = $8200
CRCT3  = $8300

  .ORG   $2000
MAKECRCTABLE:
         LDX #0          ; X counts from 0 to 255
BYTELOOP LDA #0          ; A contains the high byte of the CRC-32
         STA CRC+2       ; The other three bytes are in memory
         STA CRC+1
         STX CRC
         LDY #8          ; Y counts bits in a byte
BITLOOP  LSR             ; The CRC-32 algorithm is similar to CRC-16
         ROR CRC+2       ; except that it is reversed (originally for
         ROR CRC+1       ; hardware reasons). This is why we shift
         ROR CRC         ; right instead of left here.
         BCC NOADD       ; Do nothing if no overflow
         EOR #$ED        ; else add CRC-32 polynomial $EDB88320
         PHA             ; Save high byte while we do others
         LDA CRC+2
         EOR #$B8        ; Most reference books give the CRC-32 poly
         STA CRC+2       ; as $04C11DB7. This is actually the same if
         LDA CRC+1       ; you write it in binary and read it right-
         EOR #$83        ; to-left instead of left-to-right. Doing it
         STA CRC+1       ; this way means we won't have to explicitly
         LDA CRC         ; reverse things afterwards.
         EOR #$20
         STA CRC
         PLA             ; Restore high byte
NOADD    DEY
         BNE BITLOOP     ; Do next bit
         STA CRCT3,X     ; Save CRC into table, high to low bytes
         LDA CRC+2
         STA CRCT2,X
         LDA CRC+1
         STA CRCT1,X
         LDA CRC
         STA CRCT0,X
         INX
         BNE BYTELOOP    ; Do next byte
         RTS

UPDCRC:
         EOR CRC         ; Quick CRC computation with lookup tables
         TAX
         LDA CRC+1
         EOR CRCT0,X
         STA CRC
         LDA CRC+2
         EOR CRCT1,X
         STA CRC+1
         LDA CRC+3
         EOR CRCT2,X
         STA CRC+2
         LDA CRCT3,X
         STA CRC+3
         RTS

  .ORG   $F000
CODE:
         JSR MAKECRCTABLE
         LDY #$FF
         STY CRC
         STY CRC+1
         STY CRC+2
         STY CRC+3
         INY
LOOP     LDA $1000,Y
         JSR UPDCRC
         INY
         BNE LOOP
         LDY #3
COMPL    LDA CRC,Y
         EOR #$FF
         STA CRC,Y
         DEY
         BPL COMPL
EXIT     .BYTE $2        ; ReSim 6502 EXIT CODE
  
  .ORG   $0000
  .ORG   $FFFC
  .WORD  CODE
