    .section .text, "ax"
    .global OutputString, MoveCursor, ReadController, InitializeTimer, GetTimerTicks
	.text
	.globl	ScreenOffset,TimerTicks
	.section	.sdata,"aw"
	.align	2
	.type	ScreenOffset, @object
	.size	ScreenOffset, 4
ScreenOffset:
	.word	0
    .type	TimerTicks, @object
	.size	TimerTicks, 4
TimerTicks:
	.word	1
	.text
	.text
	.align	2

OutputString:
    # Your code here
    la      a1, 0x500FE800
    # a1 is VIDEO_MEMORY load address
    lui     a5,%hi(ScreenOffset)
    #LUI rd, imm20
    #load upper imm rd ← imm20 << 12
    lw      a3,%lo(ScreenOffset)(a5)
    #LW rd, imm12(rs1)
    #load word rd ← mem[rs1 + imm12]
    add     a1,a1,a3
    # a1+a3
    j       OSL2
OSL1:
    sb      a2,0(a1)
    # SB rs2, imm12(rs1)
    #Store byte rs2(7:0) → mem[rs1 + imm12]
    addi    a0,a0,1
    #ADDI rd, rs1, imm12
    addi    a1,a1,1
    addi    a3,a3,1
OSL2: 
    
    lb      a2,0(a0)
    #LB rd, imm12(rs1)
    # load byte (8bits)a2 = M[rs1+imm][0:7]
    #rd ← mem[rs1 + imm12]
    bnez    a2,OSL1
    #Branch if a2 != 0
    sw      a3,%lo(ScreenOffset)(a5)
    #SW rs2, imm12(rs1)
    #store word rs2(31:0) → mem[rs1 + imm12]
    ret

MoveCursor:
    # Your code here
    slli    a1,a1,6
    #Shift left logical immediate
    #SLLI rd, rs1, shamt    rd ← rs1 << shamt
    add     a0,a0,a1
    
    lui     a5,%hi(ScreenOffset)
    #LUI rd, imm20
    #load upper imm rd ← imm20 << 12
    sw      a0,%lo(ScreenOffset)(a5)
    #store words
    #store word rs2(31:0) → mem[rs1 + imm12]
    ret

ReadController:
    # Your code here
    la      a1,0x40000018
    lw      a0,0(a1)
    ret

InitializeTimer:
    la    a0,0x40000010
    li    a1,0x40000040
    li    t0,100000
    div   t1,t0,a1
    sw    t1,0(a0)
    sw    zero,4(a0)
    li    t0,0x8
    csrw mstatus,t0
    li   t0,0x80
    csrw mie,t0

    ret

GetTimerTicks:
    lui     a5,%hi(TimerTicks)
        #LUI rd, imm20
    #load upper imm rd ← imm20 << 12
    lw      a0,%lo(TimerTicks)(a5)
    #LW rd, imm12(rs1)
    #load word rd ← mem[rs1 + imm12]

    sw      a0,%lo(TimerTicks)(a5)
     #store words
    #store word rs2(31:0) → mem[rs1 + imm12]
    ret
