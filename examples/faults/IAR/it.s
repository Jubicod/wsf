        SECTION .text:CODE:NOROOT:REORDER(1)
        THUMB
        PUBWEAK NMI_Handler
        IMPORT fault_skip_instruction
NMI_Handler
        MOV  R0, SP
        B fault_skip_instruction
        PUBWEAK SVC_Handler
        IMPORT fault_clear_register
SVC_Handler
        MOV  R0, SP
        B fault_clear_register
        END
