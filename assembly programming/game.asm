[org 0x100]
jmp start


gamename: db 'CLASSIC CATCH EM!'
gamelength: dw 17
oldisr: dd 0
endgame: db 'END GAME'
endlength: dw 8
scoreis: db 'SCORE: '
scorelength: dw 7
startgame: db 'START GAME'
startlength: dw 10
tickcount: dw 0
minutes: dw 0
seconds: dw 0
oldkeyboardisr: dd 0
bucketStart: dw 0
objscore: dw 0
objstart: dw 0
objattribute: dw 0x5720
obj2start: dw 0
obj2score: dw 0
obj2attribute: dw 0x6720
delay: dw 0
random: dw 1,2,4,3,1,4,2,3,1,2,3,1,2,1,3,2,3,1,4,3,2,1,3,1,4,2,1,2,3,4,2,1,3,1,3,4,2,4,2,1,2,3,2,3,1,4,1,2,4,3,1,4,2,3,1
objchoice: dw 0
positionbomb: dw 330
positionmed: dw 450
positionmax: dw 364
positionmin: dw 400
checkcatch: dw 0
numobj: dw 0
score: dw 0

;------------------------------------------------
maxpoints:
push bp
mov bp,sp
mov cx,3         
mov bx,0         
mov ax,[bp+6]
mov si,[bp+4]

l1:
push si            
mov [es:si+bx],ax
add si,160
mov [es:si+bx],ax
pop si              
add bx,2
sub cx,1
jnz l1

pop bp
ret 4

;----------------------------------------------
clearbox:
push bp
mov bp,sp
mov cx,3         
mov bx,0         
mov ax,0x0720
mov si,[bp+4]

l9:
push si            
mov [es:si+bx],ax
add si,160
mov [es:si+bx],ax
pop si            
add bx,2
sub cx,1
jnz l9

pop bp
ret 2

;---------------------------------------------
printscore:

push bp
mov bp,sp

push si

mov ax,0xb800
mov es,ax
mov ax,[bp+4]
mov bx,10
mov cx,0

nextdigit3:
mov dx,0
div bx
add dl,0x30
push dx
inc cx
cmp ax,0
jnz nextdigit3

mov si,154

cmp cx,1
je secondstime3

nextpos3:
pop dx
mov dh,0x07
mov [es:si],dx
add si,2
loop nextpos3
jmp endofprintnum3

secondstime3:
mov word[es:si],0x0730
add si,2
pop dx
mov dh,0x07
mov [es:si],dx
add di,2
loop nextpos3

endofprintnum3:

pop si
pop bp
ret 2

;---------------------------------------------
printnum:

push bp
mov bp,sp

mov ax,0xb800
mov es,ax
mov ax,[bp+4]
mov bx,10
mov cx,0

nextdigit:
mov dx,0
div bx
add dl,0x30
push dx
inc cx
cmp ax,0
jnz nextdigit

mov di,6

cmp cx,1
je secondstime

nextpos:
pop dx
mov dh,0x07
mov [es:di],dx
add di,2
loop nextpos
jmp endofprintnum

secondstime:
mov word[es:di],0x0730
add di,2
pop dx
mov dh,0x07
mov [es:di],dx
add di,2
loop nextpos

endofprintnum:
pop bp
ret 2

;--------------------------------------------------
printnum2:

push bp
mov bp,sp

mov ax,0xb800
mov es,ax
mov ax,[bp+4]
mov bx,10
mov cx,0

nextdigit2:
mov dx,0
div bx
add dl,0x30
push dx
inc cx
cmp ax,0
jnz nextdigit2

mov si,2324

cmp cx,1
je secondstime2

nextpos2:
pop dx
mov dh,0x85
mov [es:si],dx
add si,2
loop nextpos2
jmp endofprintnum2

secondstime2:
mov word[es:si],0x0730
add si,2
pop dx
mov dh,0x85
mov [es:si],dx
add di,2
loop nextpos2

endofprintnum2:
pop bp
ret 2

;--------------------------------------------------
timer:
inc word[tickcount]

cmp word[tickcount],18
jnz endoftimer

add word[seconds],1
cmp word[minutes],2
je endofgame
;call objmovement
;call obj2movement

cmp word[seconds],60
jne noupdate
updatetime:
inc word[minutes]
cmp word[minutes],2
je endofgame

mov word[seconds],0
mov word[es:2],0x0731
push word[seconds]
call printnum

noupdate:
mov word[tickcount],0
push word[seconds]
call printnum

endoftimer:
mov al,0x20
out 0x20,al
iret

endofgame:

call ENDGAME

mov al,0x20
out 0x20,al
iret
;------------------------------------------------
bucket:
push bp
mov bp,sp

mov bp,[bp+4]
                           ;the left corner of bucket
mov ax,0x075B
mov [es:bp],ax
add bp,2
mov ax,0x075F
mov [es:bp],ax
add bp,2                   ;the middle of bucket
mov [es:bp],ax
add bp,2
mov [es:bp],ax
add bp,2
mov [es:bp],ax
add bp,2
mov [es:bp],ax
add bp,2
mov ax,0x075D                ;the right wall of bucket
mov [es:bp],ax

pop bp
ret 2

;-----------------------------------------------
clearBucket:

push bp
mov bp,sp

mov bp,[bp+4]
                        
mov ax,0x0720
mov [es:bp],ax
add bp,2
mov [es:bp],ax
add bp,2                 
mov [es:bp],ax
add bp,2
mov [es:bp],ax
add bp,2
mov [es:bp],ax
add bp,2
mov [es:bp],ax
add bp,2              
mov [es:bp],ax

pop bp
ret 2

;--------------------------------------------
bucketmovement:

mov ax,0xb800
mov es,ax

in al,0x60
cmp al,0x2A
je left

cmp al,0x36
je right
jmp nomatch

left:
cmp word[cs:bucketStart],3680
jz nobucketmovement

push word[cs:bucketStart]
call clearBucket
sub word[cs:bucketStart],2
push word[cs:bucketStart]
call bucket
jmp nomatch

right:
cmp word[cs:bucketStart],3824
jz nobucketmovement

push word[cs:bucketStart]
call clearBucket
add word[cs:bucketStart],2
push word[cs:bucketStart]
call bucket


nobucketmovement:
nomatch:
mov al,0x20
out 0x20,al
iret


;------------------------------------------------
objmovement:
push bp
mov bp,sp

mov ax,0xb800
mov es,ax

push word[cs:objstart]
call clearbox
add word[cs:objstart],320
cmp word[cs:objstart],3678
jae Generateobj

push word[cs:objattribute]
push word[cs:objstart]
call maxpoints
jmp outofbounds


Generateobj:
push si
mov si,[cs:objstart]
cmp word[es:si],0x0720
je Generate

cmp word[cs:objattribute],0x4720
jne checkmax
gg1:
jmp endofgame1

checkmax:
cmp word[cs:objattribute],0x5720
jne checkmed

mov si,[cs:objscore]
add word[cs:score],si
jmp Generate

checkmed:
cmp word[cs:objattribute],0x6720
jne checkmin

mov si,[cs:objscore]
add word[cs:score],si
jmp Generate

checkmin:
cmp word[cs:objattribute],0x3720
jne Generate

mov si,[cs:objscore]
add word[cs:score],si

Generate:
pop si

push word[cs:score]
call printscore

add word[cs:numobj],2
mov bx,[cs:numobj]

cmp word[cs:random+bx],1
je placemax
cmp word[cs:random+bx],2
je placemin
cmp word[cs:random+bx],3
je placemed
cmp word[cs:random+bx],4
je placebomb


placemax:
mov word[cs:objattribute],0x5720
mov word[cs:objstart],180
mov word[cs:objscore],30
jmp outofbounds

placemed:
mov word[cs:objattribute],0x6720
mov word[cs:objstart],260
mov word[cs:objscore],20
jmp outofbounds

placemin:
mov word[cs:objattribute],0x3720
mov word[cs:objstart],300
mov word[cs:objscore],10
jmp outofbounds

placebomb:
mov word[cs:objattribute],0x4720
mov word[cs:objstart],210
jmp outofbounds

outofbounds:
pop bp
ret

endofgame1:
pop si
mov word[cs:minutes],2
;call ENDGAME

pop bp
ret

;----------------------------------------------
obj2movement:
push bp
mov bp,sp

mov ax,0xb800
mov es,ax

push word[cs:obj2start]
call clearbox
add word[cs:obj2start],320
cmp word[cs:obj2start],3678
jae Generateobj2

push word[cs:obj2attribute]
push word[cs:obj2start]
call maxpoints
jmp outofbounds2


Generateobj2:

push si
mov si,[cs:obj2start]
cmp word[es:si],0x0720
je Generate1

cmp word[cs:obj2attribute],0x4720
jne checkmax2
gg:
jmp endofgame2

checkmax2:
cmp word[cs:obj2attribute],0x5720
jne checkmed2

mov si,[cs:obj2score]
add word[cs:score],si
jmp Generate1

checkmed2:
cmp word[cs:obj2attribute],0x6720
jne checkmin2

mov si,[cs:obj2score]
add word[cs:score],si
jmp Generate1

checkmin2:
cmp word[cs:obj2attribute],0x3720
jne Generate1

mov si,[cs:obj2score]
add word[cs:score],si


Generate1:
pop si

push word[cs:score]
call printscore

add word[cs:numobj],2
mov bx,[cs:numobj]


cmp word[cs:random+bx],1
je placemax2
cmp word[cs:random+bx],2
je placemin2
cmp word[cs:random+bx],3
je placemed2
cmp word[cs:random+bx],4
je placebomb2


placemax2:
mov word[cs:obj2attribute],0x5720
mov word[cs:obj2start],180
mov word[cs:obj2score],30
jmp outofbounds2

placemed2:
mov word[cs:obj2attribute],0x6720
mov word[cs:obj2start],260
mov word[cs:obj2score],20
jmp outofbounds2

placemin2:
mov word[cs:obj2attribute],0x3720
mov word[cs:obj2start],300
mov word[cs:obj2score],10
jmp outofbounds2

placebomb2:
mov word[cs:obj2attribute],0x4720
mov word[cs:obj2start],210
jmp outofbounds2


outofbounds2:
pop bp
ret

endofgame2:
pop si
mov word[cs:minutes],2
;call ENDGAME

pop bp
ret

;----------------------------------------------
STARTGAME:

mov ax,0xB800
mov es,ax
mov di,0
mov ax,0x0720
clrstart:                           ;clears screen
mov [es:di],ax
add di,2
cmp di,4000
jnz clrstart


mov di,1342
push word[cs:gamelength]
mov bx,gamename
push bx
call Printstr

mov dx,0xFFFF
Delay1:
sub dx,1
jnz Delay1


mov dx,0xFFFF
Delay2:
sub dx,1
jnz Delay2


mov dx,0xFFFF
Delay3:
sub dx,1
jnz Delay3


mov dx,0xFFFF
Delay4:
sub dx,1
jnz Delay4


mov dx,0xFFFF
Delay5:
sub dx,1
jnz Delay5


mov dx,0xFFFF
Delay6:
sub dx,1
jnz Delay6


mov dx,0xFFFF
Delay7:
sub dx,1
jnz Delay7


mov dx,0xFFFF
Delay8:
sub dx,1
jnz Delay8


mov dx,0xFFFF
Delay9:
sub dx,1
jnz Delay9


mov dx,0xFFFF
Delay10:
sub dx,1
jnz Delay10

mov di,1668
push word[startlength]
mov bx, startgame
push bx       
call Printstr             ;prints start game


loading:
mov di,1978                                
mov cx,7
loop1:                                          ;prints the loading sign
mov word[es:di],0x5020
add di,2
mov word[es:di],0x5020
add di,4

mov dx,0xFFFF
delayloadingsign:
sub dx,1
jnz delayloadingsign

mov dx,0xFFFF
delayloadingsign2:
sub dx,1
jnz delayloadingsign2

mov dx,0xFFFF
delayloadingsign3:
sub dx,1
jnz delayloadingsign3

mov dx,0xFFFF
delayloadingsign4:
sub dx,1
jnz delayloadingsign4

mov dx,0xFFFF
delayloadingsign5:
sub dx,1
jnz delayloadingsign5

mov dx,0xFFFF
delayloadingsign6:
sub dx,1
jnz delayloadingsign6

mov dx,0xFFFF
delayloadingsign7:
sub dx,1
jnz delayloadingsign7

mov dx,0xFFFF
delayloadingsign8:
sub dx,1
jnz delayloadingsign8

mov dx,0xFFFF
delayloadingsign9:
sub dx,1
jnz delayloadingsign9

mov dx,0xFFFF
delayloadingsign10:
sub dx,1
jnz delayloadingsign10

sub cx,1
jnz loop1

mov ax,0x3720                                  ;prints objects
mov di,3246
call BOX
mov ax,0x6720
mov di,3266
call BOX
mov ax,0x4720
mov di,3286
call BOX
mov ax,0x5720
mov di,3306
call BOX



scores:                                         ;pritns score of each object
mov di,3726                       
mov word[es:di],0x8524
add di,2
mov word[es:di],0x8531
add di,2
mov word[es:di],0x8530
add di,2

mov di,3746
mov word[es:di],0x8524
add di,2
mov word[es:di],0x8532
add di,2
mov word[es:di],0x8530
add di,2

mov di,3766
mov word[es:di],0x8558
add di,2
mov word[es:di],0x8558

mov di,3786
mov word[es:di],0x8524
add di,2
mov word[es:di],0x8533
add di,2
mov word[es:di],0x8530
add di,2

ret
;----------------------------------------------

BOX:
push bp
mov bp,sp
mov cx,3         ;for width of block
mov bx,0         ;pointer

loopbox:
push di             ;stores old di value
mov [es:di+bx],ax
add di,160
mov [es:di+bx],ax
pop di              ;restores value
add bx,2
sub cx,1
jnz loopbox

pop bp
ret
;----------------------------------------------
Printstr:
push bp
mov bp,sp

mov si,[BP+4]
mov cx,[BP+6]
mov ah,0x85

nextchar:
mov al,[si]
mov [es:di],ax
add di,2
add si,1
loop nextchar

pop bp
ret 4
;----------------------------------------------
ENDGAME:

mov ax,0
mov es,ax
mov dx,[cs:oldisr]
mov [es:9*4],dx
mov dx,[cs:oldisr+2]
mov [es:9*4+2],dx

mov ax,0xB800
mov es,ax
mov di,0
mov ax,0x0720
clrend:                           ;clears screen
mov [es:di],ax
add di,2
cmp di,4000
jnz clrend

mov di,1992
push word[endlength]
mov bx, endgame
push bx       
call Printstr

mov di,2312
push word[scorelength]
mov bx, scoreis
push bx       
call Printstr

push word[cs:score]
call printnum2

ret

;----------------------------------------------
start:
call STARTGAME

int16:
mov ah,0
int 0x16
cmp ah,0
je int16

mov ax,0xb800
mov es,ax
mov di,0
mov ax,0x0720
clr:
mov [es:di],ax
add di,2
cmp di,4000
jnz clr

score1:                      
mov ax,0x0730
mov di,156
mov [es:di],ax
mov ax,0x0730
sub di,2
mov [es:di],ax

mov ax,0x073A
sub di,2
mov [es:di],ax
mov ax,0x0765
sub di,2
mov [es:di],ax
mov ax,0x0772
sub di,2
mov [es:di],ax
mov ax,0x076F
sub di,2
mov [es:di],ax
mov ax,0x0763
sub di,2
mov [es:di],ax
mov ax,0x0753
sub di,2
mov [es:di],ax


mov di,0
mov word[es:di],0x0730
add di,2
mov word[es:di],0x0730
add di,2
mov word[es:di],0x073A
add di,2
mov word[es:di],0x0730
add di,2
mov word[es:di],0x0730

;--------MAKE BUCKET---------
mov word[bucketStart],3760
push word[bucketStart]
call bucket

;--------MAKE FIRST 2 OBJECTS-------
mov word[objstart],180
mov word[objscore],30
push word[cs:objattribute]
push word[objstart]
call maxpoints

mov word[obj2start],1860
mov word[cs:obj2score],20
push word[cs:obj2attribute]
push word[obj2start]
call maxpoints

xor ax,ax
mov es,ax
mov si,0

;-----------HOOKING------------------

cli
mov dx,[es:9*4]
mov [cs:oldisr],dx
mov dx,[es:9*4+2]
mov [cs:oldisr+2],dx

mov word[es:9*4],bucketmovement
mov [es:9*4+2],cs
sti


cli
mov word[es:8*4],timer
mov [es:8*4+2],cs
sti

ll:

cmp word[cs:minutes],2
jz endofmaingame

mov dx,0xFFFF
delayloadingsign11:
sub dx,1
jnz delayloadingsign11

mov dx,0xFFFF
delayloadingsign12:
sub dx,1
jnz delayloadingsign12

mov dx,0xFFFF
delayloadingsign13:
sub dx,1
jnz delayloadingsign13

mov dx,0xFFFF
delayloadingsign14:
sub dx,1
jnz delayloadingsign14

mov dx,0xFFFF
delayloadingsign15:
sub dx,1
jnz delayloadingsign15

mov dx,0xFFFF
delayloadingsign16:
sub dx,1
jnz delayloadingsign16

mov dx,0xFFFF
delayloadingsign17:
sub dx,1
jnz delayloadingsign17

mov dx,0xFFFF
delayloadingsign18:
sub dx,1
jnz delayloadingsign18

mov dx,0xFFFF
delayloadingsign19:
sub dx,1
jnz delayloadingsign19

mov dx,0xFFFF
delayloadingsign20:
sub dx,1
jnz delayloadingsign20

call objmovement
call obj2movement

endofmaingame:
jmp ll


mov ax,0x4c00
int 0x21