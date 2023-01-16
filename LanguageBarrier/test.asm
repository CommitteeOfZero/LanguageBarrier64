
extern widths:ptr byte
extern gameExeDialogueLayoutWidthLookup1Return:ptr qword
extern gameExeDialogueLayoutWidthLookup2Return:ptr qword
extern gameExeDialogueLayoutWidthLookup3Return:ptr qword
extern gameExeDialogueLayoutWidthLookup4Return:ptr qword
extern gameExeTipContentHeight: dword
extern gameExeSetTipContentHeightReturn:ptr qword
extern gameExeSetTipContentHeight2Return:ptr qword
extern gameExeSetTipCountReturn:ptr qword
extern gameExeSetTipCountReturn2:ptr qword
extern BlueSkyPromptFixReturn:ptr qword

extern gameExeSkipCHNOffset:ptr qword

extern gameExeLineHeight:ptr qword
extern gameExeRsi:ptr qword




.code
dialogueLayoutWidthLookup1Hook proc
	 push r9
	 lea r9, widths
	 movzx edx, byte ptr [r9+r10]
	 pop r9
	 jmp gameExeDialogueLayoutWidthLookup1Return
dialogueLayoutWidthLookup1Hook endp


dialogueLayoutWidthLookup2Hook proc
	 push r9
	 lea r9, widths
	 movzx eax, byte ptr [r9+rcx]
	 pop r9
	 jmp gameExeDialogueLayoutWidthLookup2Return
dialogueLayoutWidthLookup2Hook endp

dialogueLayoutWidthLookup3Hook proc
	 push r9
	 lea r9, widths
	 movzx eax, byte ptr [r9+rcx]
	 pop r9
	 jmp gameExeDialogueLayoutWidthLookup3Return
dialogueLayoutWidthLookup3Hook endp


dialogueLayoutWidthLookup4Hook proc
	 push r9
	 lea r9, widths
	 movzx r8d, byte ptr [r9+rcx]
	 pop r9
	 jmp gameExeDialogueLayoutWidthLookup4Return
dialogueLayoutWidthLookup4Hook endp


setTipContentHeightHook proc
	  mov eax, [gameExeTipContentHeight]
	  jmp gameExeSetTipContentHeightReturn
	  setTipContentHeightHook endp
setTipContentHeightHook2 proc
	  mov eax, [gameExeTipContentHeight]
	  jmp gameExeSetTipContentHeight2Return
	  setTipContentHeightHook2 endp

chatSIMDMove proc
	  mov [gameExeLineHeight], rbx
	  mov [gameExeRsi], rsi

	  ret
chatSIMDMove endp


chatSIMDMoveRestore proc
	  mov rbx, [gameExeLineHeight]
	  mov rsi, [gameExeRsi]

	  ret
chatSIMDMoveRestore endp

 SkipCHNFixJumpHook proc
 jmp [gameExeSkipCHNOffset]
  SkipCHNFixJumpHook endp


   BlueSkyPromptFixHook proc
mov     dword ptr [rsp+0A4h], 430c0000h
jmp [BlueSkyPromptFixReturn]
  BlueSkyPromptFixHook endp


 setTipCountHook proc
		cmp     rdi, 141   ; 0000008dH
		jl      SHORT $LN4@setTipCountHook
		cmp     rdi, 145   ; 00000091H
		jle     SHORT $LN2@setTipCountHook
$LN4@setTipCountHook:
		stc
		jmp     SHORT $LN1@setTipCountHook
		jmp     SHORT $LN1@setTipCountHook
$LN2@setTipCountHook:
		clc
$LN1@setTipCountHook:
 jmp [gameExeSetTipCountReturn]
  setTipCountHook endp


 


 setTipCountHook2 proc
		cmp     rdi, 141   ; 0000008dH
		jl      SHORT $LN4@setTipCountHook2
		cmp     rdi, 145   ; 00000091H
		jle     SHORT $LN2@setTipCountHook2
$LN4@setTipCountHook2:
		stc
		jmp     SHORT $LN1@setTipCountHook2
		jmp     SHORT $LN1@setTipCountHook2
$LN2@setTipCountHook2:
		clc
$LN1@setTipCountHook2:
 jmp [gameExeSetTipCountReturn2]
  setTipCountHook2 endp




end