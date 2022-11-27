
extern widths:ptr byte
extern gameExeDialogueLayoutWidthLookup1Return:ptr qword
extern gameExeDialogueLayoutWidthLookup2Return:ptr qword
extern gameExeDialogueLayoutWidthLookup3Return:ptr qword

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

end