#define gbuf plotsscreen    ;what ion.inc defines the screen buffer as
#define NUMBER_OF_LIBRARIES		8
libraryVectors		=cmdshad+80
#define	randData	libraryVectors+(3*NUMBER_OF_LIBRARIES)

;code for ionfastcopy "borrowed" from ionf.z80


;#define smc    ;uncomment if you are using SMC
rand16:
;;collaboration by Zeda with Runer112
;;160cc or 148cc if using SMC
;;26 bytes
;;cycle: 4,294,901,760 (almost 4.3 billion)
#ifdef smc
seed1=$+1
    ld hl,9999
#else
    ld hl,(seed1)
#endif
    ld b,h
    ld c,l
    add hl,hl
    add hl,hl
    inc l
    add hl,bc
    ld (seed1),hl
#ifdef smc
seed2=$+1
    ld hl,9999
#else
    ld hl,(seed2)
#endif
    add hl,hl
    sbc a,a
    and %00101101
    xor l
    ld l,a
    ld (seed2),hl
    add hl,bc
    ret
	
	
ionFastCopy:
fastCopy:
 di
 ld    a,$80                ; 7
 out    ($10),a                ; 11
 ld    hl,gbuf-12-(-(12*64)+1)        ; 10
 ld    a,$20                ; 7
 ld    c,a                ; 4
 inc    hl                ; 6 waste
 dec    hl                ; 6 waste
fastCopyAgain:
 ld    b,64                ; 7
 inc    c                ; 4
 ld    de,-(12*64)+1            ; 10
 out    ($10),a                ; 11
 add    hl,de                ; 11
 ld    de,10                ; 10
fastCopyLoop:
 add    hl,de                ; 11
 inc    hl                ; 6 waste
 inc    hl                ; 6 waste
 inc    de                ; 6
 ld    a,(hl)                ; 7
 out    ($11),a                ; 11
 dec    de                ; 6
 djnz    fastCopyLoop            ; 13/8
 ld    a,c                ; 4
 cp    $2B+1                ; 7
 jr    nz,fastCopyAgain        ; 10/1
 ret                    ; 10
 ret
;-----> Draw a sprite
; b=size of sprite
; l=yc
; a=xc
; ix holds pointer 
ionPutSprite:
putSprite:
	ld	e,l
	ld	h,$00
	ld	d,h
	add	hl,de
	add	hl,de
	add	hl,hl
	add	hl,hl
	ld	e,a
	and	$07
	ld	c,a
	srl	e
	srl	e
	srl	e
	add	hl,de
	ld	de,gbuf
	add	hl,de
putSpriteLoop1:
sl1:	ld	d,(ix)
	ld	e,$00
	ld	a,c
	or	a
	jr	z,putSpriteSkip1
putSpriteLoop2:
	srl	d
	rr	e
	dec	a
	jr	nz,putSpriteLoop2
putSpriteSkip1:
	ld	a,(hl)
	xor	d;change
	ld	(hl),a
	inc	hl
	ld	a,(hl)
	xor	e;change
	ld	(hl),a
	ld	de,$0B
	add	hl,de
	inc	ix
	djnz	putSpriteLoop1
	ret
	ret
