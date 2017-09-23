/***************************************************************************************************
**CPU：   BM3803
**Author: Jamza
**Data:   20150130
**
***************************************************************************************************/


/*************************************************陷阱/中断向量表**********************************/

#define TRAPL(H)          mov %g0, %l0; sethi %hi(H), %l4; jmp %l4+%lo(H); nop;
#define TRAP(H)           mov %psr,%l0; sethi %hi(H), %l4; jmp %l4+%lo(H); nop;
#define TRAP_ENTRY(H)     mov %psr,%l0; sethi %hi(H), %l4; jmp %l4+%lo(H); mov %tbr, %l3;
#define BAD_TRAP          ta 0; nop; nop; nop;
#define SOFT_TRAP         BAD_TRAP

    .text
    .global _trap_table, _hardreset
    .global _start
    .global _userinit, main, _end
    .global _window_overflow,  _window_underflow,  _fp_disable
    .global _ISR_Handler
    
_trap_table:
	
/*-----------------------陷阱向量----------------*/
_hardreset:
    TRAPL(_start);                              ! tt=00 reset trap
    BAD_TRAP;			                              ! tt=01 instruction_access_exception
    BAD_TRAP;			                              ! tt=02 illegal_instruction
    BAD_TRAP;			                              ! tt=03 priveleged_instruction
    BAD_TRAP;		                                ! tt=04 fp_disabled
    TRAP(_window_overflow);	                    ! tt=05 window_overflow
    TRAP(_window_underflow);	                  ! tt=06 window_underflow
    BAD_TRAP;			                              ! tt=07 memory_address_not_aligned
    BAD_TRAP;			                              ! tt=08 fp_exception
    BAD_TRAP;			                              ! tt=09 data_access_exception
    BAD_TRAP;			                              ! tt=0A tag_overflow
    BAD_TRAP;			                              ! tt=0B watchpoint_detected
    BAD_TRAP;			                              ! tt=0C undefined
    BAD_TRAP;			                              ! tt=0D undefined
    BAD_TRAP;			                              ! tt=0E undefined
    BAD_TRAP;			                              ! tt=0F undefined
    BAD_TRAP;			                              ! tt=10 undefined


/*-----------------------中断向量----------------*/


    TRAP_ENTRY(_ISR_Handler)                    ! tt=0x11 level 1 , AHB bus error
    TRAP_ENTRY(_ISR_Handler)                    ! tt=0x12 level 2 , Uart2
    TRAP_ENTRY(_ISR_Handler)                    ! tt=0x13 level 3 , Uart1
    TRAP_ENTRY(_ISR_Handler)                    ! tt=0x14 level 4 , IO[0]
    TRAP_ENTRY(_ISR_Handler)                    ! tt=0x15 level 5 , IO[1]
    TRAP_ENTRY(_ISR_Handler)                    ! tt=0x16 level 6 , IO[2]
    TRAP_ENTRY(_ISR_Handler)                    ! tt=0x17 level 7 , IO[3]
    TRAP_ENTRY(_ISR_Handler)                    ! tt=0x18 level 8 , timer1
    TRAP_ENTRY(_ISR_Handler)                    ! tt=0x19 level 9 , timer2
    TRAP_ENTRY(_ISR_Handler)                    ! tt=0x1A level 10, unused
    TRAP_ENTRY(_ISR_Handler)                    ! tt=0x1B level 11, DSU
    TRAP_ENTRY(_ISR_Handler)                    ! tt=0x1C level 12, Uart3
    TRAP_ENTRY(_ISR_Handler)                    ! tt=0x1D level 13, unused
    TRAP_ENTRY(_ISR_Handler)                    ! tt=0x1E level 14, PCI
    TRAP_ENTRY(_ISR_Handler)                    ! tt=0x1F level 15, unused

    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! tt=20 - 23 undefined
    BAD_TRAP;		                                ! tt=24      cp_disabled
    BAD_TRAP; BAD_TRAP; BAD_TRAP;	              ! tt=25 - 27 undefined
    BAD_TRAP;		                                ! tt=28      cp_exception

    
/*-----------------------未定义向量--------------*/


    BAD_TRAP; BAD_TRAP; BAD_TRAP;	              ! 29 - 2B undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 2C - 2F undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 30 - 33 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 34 - 37 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 38 - 3B undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 3C - 3F undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 40 - 43 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 44 - 47 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 48 - 4B undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 4C - 4F undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 50 - 53 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 54 - 57 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 58 - 5B undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 5C - 5F undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 60 - 63 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 64 - 67 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 68 - 6B undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 6C - 6F undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 70 - 73 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 74 - 77 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 78 - 7B undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 7C - 7F undefined

    
/*-----------------------软件异常指令向量-------*/    
    
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; ! 80 - 83
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! 84 - 87
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! 88 - 8B
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! 8C - 8F
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! 90 - 93
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! 94 - 97
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! 98 - 9B
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! 9C - 9F
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! A0 - A3
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! A4 - A7
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! A8 - AB
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! AC - AF
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! B0 - B3
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! B4 - B7
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! B8 - BB
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! BC - BF
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! C0 - C3
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! C4 - C7
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! C8 - CB
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! CC - CF
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! D0 - D3
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! D4 - D7
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! D8 - DB
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! DC - DF
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! E0 - E3
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! E4 - E7
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! E8 - EB
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! EC - EF
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! F0 - F3
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! F4 - F7
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! F8 - FB
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! FC - FF

/*************************************************初始化设置***************************************/

#define PSR_INIT   0x10c0                     /*CWP=0，ET=0，S=1，PS=0，EF=0，PIL=0*/
#define PREGS      0x80000000                 /*CPU寄存器基地址*/
#define cachectrl  0x14                       /*cache控制寄存器*/
#define mcfg1      0x00                       /* 存储器控制寄存器1*/
#define mcfg2      0x04                       /* 存储器控制寄存器2*/
#define mecfg1     0x100                      /* 存储器容错配置寄存器1*/

#define irqmask    0x90                       /* 中断级别、屏蔽寄存器*/
#define irqpend    0x94                       /* 中断请求寄存器*/
#define irqforce   0x98                       /* 中断强制寄存器*/
#define irqclear   0x9C                       /* 中断清除寄存器*/

#define wpr1       0x1c                       /* 写保护寄存器1*/
#define wpr2       0x20                       /* 写保护寄存器1*/

#define stack_INIT 0x4017fff0                 /* 堆栈初始化值*/


/*-------------初始化CPU系统寄存器-----------*/

_start:
        
        mov   %g0, %asr16
        nop
        nop
        nop
        mov   %g0, %asr17
        nop 
        nop
        nop                                    ! 关闭造错功能
        
        set   PSR_INIT, %g1
        mov   %g1, %psr
        nop
        nop
        nop                                     ! 禁止陷阱，关闭浮点处理器，设置管理态
        
        mov   %g0, %wim
        nop
        nop
        nop                                     ! 设置窗口均有效，避免上下溢出
        
        mov   %g0, %g1
        mov   %g0, %g2
        mov   %g0, %g3
        mov   %g0, %g4
        mov   %g0, %g5
        mov   %g0, %g6
        mov   %g0, %g7                          ! 全局寄存器清零
        
        mov   0x08, %g1
1:      mov   %g0, %l0
        mov   %g0, %l1
        mov   %g0, %l2
        mov   %g0, %l3
        mov   %g0, %l4
        mov   %g0, %l5
        mov   %g0, %l6
        mov   %g0, %l7
        mov   %g0, %i0
        mov   %g0, %i1
        mov   %g0, %i2
        mov   %g0, %i3
        mov   %g0, %i4
        mov   %g0, %i5
        mov   %g0, %i6
        mov   %g0, %i7
        subcc %g1,1,%g1
        save
        bne   1b
        flush
        nop                                     ! 八个窗口的loacl，in与out寄存器清零
        
        set   2, %g1
        mov   %g1, %wim
        nop
        nop
        nop                                     ! 设置WIM未窗口1，即窗口1当前使用，其余窗口均有效
        
        sethi %hi(_trap_table), %g1
        mov   %g1, %tbr
        nop
        nop
        nop                                     ! 设置中断系统的基地址，即为向量表的起始地址，即0x40000000


				mov %g0, %y
				nop
				nop
				nop                                     ! Y寄存器清零
				
				
				mov %g0,%asr24
        nop;nop;nop
        mov %g0,%asr25
		    nop;nop;nop
        mov %g0,%asr26
				nop;nop;nop
				mov %g0,%asr27
				nop;nop;nop
				mov %g0,%asr28
				nop;nop;nop
				mov %g0,%asr29
				nop;nop;nop
				mov %g0,%asr30
				nop;nop;nop
				mov %g0,%asr31
				nop;nop;nop                             ! 辅助寄存器清零


/*--------存储器控制寄存器配置-------*/
 /*             
                set PREGS, %g1
				ld [%g1+mcfg2], %g2                
                or    %g2, 0x4f, %g2
                st %g2, [%g1+mcfg2]
                nop
 */
               
				set PREGS, %g1
				ld [%g1+mcfg2], %g2
				!set 0x7806f, %g2                       !对SRAM bank的大小，需配置为1001， 
				set 0x7926f, %g2
				st %g2, [%g1+mcfg2]
				nop                                     ! 配置SRAM读等待周期最长，读改写方式使能

				ld [%g1+mcfg1], %g2
				set 0x1cf9f01f, %g2
				st %g2, [%g1+mcfg1]
				nop 
				
/*				
				ld [%g1+mcfg1], %g2
				sethi %hi(0xcf80000),%g3
				or %g3,%lo(0xcf80000),%g3                 !打开IO使能
				or %g2, %g3, %g2
				st %g2, [%g1+mcfg1]
				nop 
*/				
				ld [%g1+mecfg1], %g2
			    sethi %hi(0x0fffffff), %g3
			    or %g3, %lo(0x0fffffff), %g3
			    and %g2, %g3, %g2
			    st %g2, [%g1+mecfg1]
			    nop
			    nop
			    nop
				


/*--------Cache功能配置-------------*/
                set 0x81000f, %g2
				st %g2, [%g1+cachectrl]
				nop                                     ! 禁止Cache功能
				
/*--------中断控制寄存器配置-------*/

    		st %g0, [%g1+irqmask]
    		nop                                     ! 设置15路中断均为低优先级，15路中断均屏蔽
    		st %g0, [%g1+irqforce]                  
    		nop																			! 设置中断强制寄存器清零
    		
    		set 0xffff, %g2
    		st %g2, [%g1+irqclear]
    		nop                                     ! 设置中断清除寄存器
    		
/*------写保护寄存器配置----------*/
				st %g0, [%g1+wpr1]
				nop
				st %g0, [%g1+wpr2]
				nop                                     ! 写保护寄存器初始化

/*------堆栈初始设置--------------*/
				set stack_INIT, %g2
				mov %g2, %sp
				nop
/*-------清除bss区域--------------*/	



/*-------初始化浮点寄存器----------*/

        set    _fsrinit,%g1               !!!be careful of the initial value of fsr
        ld     [%g1] , %fsr
        nop
        nop
        nop

        ! initialize the FPU %f register
        set    _fpdata,%g1
        ldd    [%g1], %f0
        ldd    [%g1], %f2
        ldd    [%g1], %f4
        ldd    [%g1], %f6
        ldd    [%g1], %f8
        ldd    [%g1], %f10
        ldd    [%g1], %f12
        ldd    [%g1], %f14
        ldd    [%g1], %f16
        ldd    [%g1], %f18
        ldd    [%g1], %f20
        ldd    [%g1], %f22
        ldd    [%g1], %f24
        ldd    [%g1], %f26
        ldd    [%g1], %f28
        ldd    [%g1], %f30
		nop


				
/*-------调用主函数--------------*/	

        set   PSR_INIT|0x20,%g1     ! 0x10E0
        mov   %g1,%psr
        nop
        nop
        nop

				
                nop
				nop
				nop
				call main
				nop
				nop
				nop
				ta 0
				nop			


/*************************************************窗口上溢处理***************************************
*SAVE指令使得当前窗口指针（CWP）指向无效窗口（WIM中值为1的窗口）时引起的陷阱
*
****************************************************************************************************/

#define  NWINDOWS   8
 .global _window_overflow
_window_overflow:
				mov  %wim, %l3                            ! l3 = WIM
				mov  %g1, %l7                             ! save g1
				srl  %l3, 1, %g1                          ! g1 = WIM >> 1
				sll  %l3, NWINDOWS-1 , %l4	              ! l4 = WIM << (Number Windows - 1)
				or   %l4, %g1, %g1                        ! g1 = (WIM >> 1) | (WIM << (Number Windows - 1))	
				save                                      ! Get into window to be saved.
				mov  %g1, %wim                            ! now safe to load new WIM
	  		nop; nop; nop                             ! 3 slot delay

				std  %l0, [%sp + 0x00]           					! save local register set
				std  %l2, [%sp + 0x08]
				std  %l4, [%sp + 0x10]
				std  %l6, [%sp + 0x18]
				std  %i0, [%sp + 0x20]           					! save input register set
				std  %i2, [%sp + 0x28]
				std  %i4, [%sp + 0x30]
				std  %i6, [%sp + 0x38]	
				restore                          					! Go back to trap window.
				nop
				mov  %l7, %g1                    					! restore g1
				jmp  %l1                         					! return old PC
				rett %l2                                  ! return old nPC
				nop
				nop		
				

/*************************************************窗口下溢处理***************************************
*RESTORE或者RETT指令使得当前窗口指针（CWP）指向无效窗口（WIM中值为1的窗口）时引起的陷阱
*
****************************************************************************************************/

.global _window_underflow
_window_underflow:
        mov  %wim, %l3                   ! Calculate next WIM
        sll  %l3, 1, %l4
        srl  %l3, NWINDOWS-1, %l5
        or   %l5, %l4, %l5
        mov  %l5, %wim
        nop; nop;nop
        restore                          ! Two restores to get into the
        restore                          ! window to restore
        ldd   [%sp + 0], %l0             ! Restore window from the stack
        ldd   [%sp + 8], %l2
        ldd   [%sp + 16], %l4
        ldd   [%sp + 24], %l6
        ldd   [%sp + 32], %i0
        ldd   [%sp + 40], %i2
        ldd   [%sp + 48], %i4
        ldd   [%sp + 56], %i6
        save                             ! Get back to the trap window.
        save
        jmp  %l1                         ! Re-execute restore.
        rett %l2
        nop
				nop
				
/*************************************************中断处理函数***************************************
*中断处理流程：
*1、记录中断现场的部分信息，即记录%psr与%tbr的值；
*2、判断中断时窗口是否溢出。在中断发生时系统自动将窗口cwp-1，需先判断窗口是否溢出，若溢出需先保存窗口；
*3、保存中断现场。保存特殊寄存器、全局寄存器、输入寄存器、以及相关信息；
*4、保存原先的中断设置，更新当前中断服务时的中断设置。通过中断控制器与PIL设置更新，实现中断优先级与嵌套等；
*5、打开中断处理使能位。即设置%psr.ET=1,允许用户中断处理时可以发生其他中断；
*6、跳转到用户中断处理程序；
*7、运行用户中断处理程序；
*8、从用户中断处理程序返回，恢复现场。设置%psr.ET=0.进行现场恢复，包括中断设置，IU寄存器等；
*9、判断窗口是否溢出；
*10、返回到被中断的代码指令，继续执行。
*
*
****************************************************************************************************/
.global _ISR_Handler
_ISR_Handler:

#define SPARC_NUMBER_OF_REGISTER_WINDOWS 8

#define SPARC_PSR_CWP_MASK  0x07        /* bits  0 -  4 */
#define SPARC_PSR_ET_MASK   0x00000020  /* bit   5 */
#define SPARC_PSR_S_MASK    0x00000080  /* bit   7 */
#define SPARC_PSR_PIL_MASK  0x00000F00  /* bits  8 - 11 */
#define SPARC_PSR_EF_MASK   0x00001000  /* bit  12 */
#define SPARC_PSR_EC_MASK   0x00002000  /* bit  13 */
#define SPARC_PSR_ICC_MASK  0x00F00000  /* bits 20 - 23 */
#define SPARC_PSR_VER_MASK  0x0F000000  /* bits 24 - 27 */
#define SPARC_PSR_IMPL_MASK 0xF0000000  /* bits 28 - 31 */


#define CPU_STACK_FRAME_L0_OFFSET             0x00
#define CPU_STACK_FRAME_L2_OFFSET             0x08
#define CPU_STACK_FRAME_L4_OFFSET             0x10
#define CPU_STACK_FRAME_L6_OFFSET             0x18
#define CPU_STACK_FRAME_I0_OFFSET             0x20
#define CPU_STACK_FRAME_I2_OFFSET             0x28
#define CPU_STACK_FRAME_I4_OFFSET             0x30
#define CPU_STACK_FRAME_I6_FP_OFFSET          0x38
#define CPU_STRUCTURE_RETURN_ADDRESS_OFFSET   0x40
#define CPU_STACK_FRAME_SAVED_ARG0_OFFSET     0x44
#define CPU_STACK_FRAME_SAVED_ARG1_OFFSET     0x48
#define CPU_STACK_FRAME_SAVED_ARG2_OFFSET     0x4c
#define CPU_STACK_FRAME_SAVED_ARG3_OFFSET     0x50
#define CPU_STACK_FRAME_SAVED_ARG4_OFFSET     0x54
#define CPU_STACK_FRAME_SAVED_ARG5_OFFSET     0x58
#define CPU_STACK_FRAME_PAD0_OFFSET           0x5c
#define CPU_MINIMUM_STACK_FRAME_SIZE          0x60
#define ISF_STACK_FRAME_OFFSET 0x00

#define ISF_PSR_OFFSET         CPU_MINIMUM_STACK_FRAME_SIZE + 0x00
#define ISF_PC_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0x04
#define ISF_NPC_OFFSET         CPU_MINIMUM_STACK_FRAME_SIZE + 0x08
#define ISF_G1_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0x0c
#define ISF_G2_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0x10
#define ISF_G4_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0x18
#define ISF_G6_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0x20
#define ISF_I0_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0x28
#define ISF_I2_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0x30
#define ISF_I4_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0x38
#define ISF_I6_FP_OFFSET       CPU_MINIMUM_STACK_FRAME_SIZE + 0x40
#define ISF_Y_OFFSET           CPU_MINIMUM_STACK_FRAME_SIZE + 0x48
#define ISF_TPC_OFFSET         CPU_MINIMUM_STACK_FRAME_SIZE + 0x4c

#define ISF_F0_OFFSET           CPU_MINIMUM_STACK_FRAME_SIZE + 0x50 
#define ISF_F2_OFFSET           CPU_MINIMUM_STACK_FRAME_SIZE + 0x58 
#define ISF_F4_OFFSET           CPU_MINIMUM_STACK_FRAME_SIZE + 0x60 
#define ISF_F6_OFFSET           CPU_MINIMUM_STACK_FRAME_SIZE + 0x68 

#define ISF_F8_OFFSET           CPU_MINIMUM_STACK_FRAME_SIZE + 0x70 
#define ISF_F10_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0x78 
#define ISF_F12_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0x80
#define ISF_F14_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0x88
                                                                    
#define ISF_F16_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0x90
#define ISF_F18_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0x98
#define ISF_F20_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0xa0
#define ISF_F22_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0xa8
                                                                    
#define ISF_F24_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0xb0
#define ISF_F26_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0xb8
#define ISF_F28_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0xc0
#define ISF_F30_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0xc8

#define ISF_FSR_OFFSET          CPU_MINIMUM_STACK_FRAME_SIZE + 0xd0

#define CONTEXT_CONTROL_INTERRUPT_FRAME_SIZE CPU_MINIMUM_STACK_FRAME_SIZE + 0x50 


/*--------------------1、记录中断现场%psr与%tbr的值--------------------------*/
/*
 
 #define TRAP_ENTRY(H)     mov %psr,%l0; sethi %hi(H), %l4; jmp %l4+%lo(H); mov %tbr, %l3;
 宏定义中已经保存了中断现场的%psr与%tbr的数值
 
 即：%l0=%psr
 		 %l1=%PC
 		 %l2=%nPC
 		 %l3=%tbr
 
*/


/*--------------------2、判断窗口是否上溢-----------------------------------*/

win_ovflow:
	
				mov %g4, %l4
				mov %g5, %l5                            !保存全局寄存器g4与g5
				
				rd %wim, %g4                            !g4=wim
				srl %g4, %l0, %g5                       !g5=wim>>cwp
																								!srl指令只右移%l0寄存器低5位数值
																								!cwp为%psr的低5位
				cmp %g5, 1                              !cwp指向的窗口在wim中对应位是否为1，即是否是无效
				bne dont_do_the_window                  !窗口有效，跳转至dont_do_the_window
				nop
				
				srl %g4, 1, %g5
				sll %g4, NWINDOWS-1, %g4
				or %g4, %g5, %g4                        ! g4 = (WIM >> 1) |
                                         				!(WIM << (Number Windows - 1))
        
        save
        wr %g4, 0, %wim                         !new wim
        nop
        nop
        nop

SAVE_WINDOW:                                    !wim-1窗口内容入堆栈
				std %l0, [%sp + CPU_STACK_FRAME_L0_OFFSET]
        std %l2, [%sp + CPU_STACK_FRAME_L2_OFFSET]
        std %l4, [%sp + CPU_STACK_FRAME_L4_OFFSET]
        std %l6, [%sp + CPU_STACK_FRAME_L6_OFFSET]

        std %i0, [%sp + CPU_STACK_FRAME_I0_OFFSET]
        std %i2, [%sp + CPU_STACK_FRAME_I2_OFFSET]
        std %i4, [%sp + CPU_STACK_FRAME_I4_OFFSET]
        std %i6, [%sp + CPU_STACK_FRAME_I6_FP_OFFSET]

        restore                                 !返回wim对应的窗口
        nop

/*--------------------3、保存中断现场-----------------------------------*/
        
dont_do_the_window:
	
save_isf:				
				sub  %fp, CONTEXT_CONTROL_INTERRUPT_FRAME_SIZE, %sp
                                            ! make space for ISF
        std  %l0, [%sp + ISF_PSR_OFFSET]    ! save psr, PC
        st   %l2, [%sp + ISF_NPC_OFFSET]    ! save nPC
        st   %g1, [%sp + ISF_G1_OFFSET]     ! save g1
        std  %g2, [%sp + ISF_G2_OFFSET]     ! save g2, g3
        std  %l4, [%sp + ISF_G4_OFFSET]     ! save g4, g5 
        std  %g6, [%sp + ISF_G6_OFFSET]     ! save g6, g7
        std  %i0, [%sp + ISF_I0_OFFSET]     ! save i0, i1
        std  %i2, [%sp + ISF_I2_OFFSET]     ! save i2, i3
        std  %i4, [%sp + ISF_I4_OFFSET]     ! save i4, i5
        std  %i6, [%sp + ISF_I6_FP_OFFSET]  ! save i6/fp, i7
        rd   %y, %g1
        st   %g1, [%sp + ISF_Y_OFFSET]      ! save y
        st   %l6, [%sp + ISF_TPC_OFFSET]    ! save real trapped pc

/*--------------------4、5、更新中断设置，打开中断使能-----------------------------------*/

GET_TT:                                 		!取得trap号,保存在%o0
    		and	%l3, 0x0FF0, %l3								!l3 is value of tbr
    		srl	%l3, 4, %l3             
    		sub	%l3, 16, %o0										!interrupt number (1 thru 15) in %o0
fix_pil:
        mov %l0,%g5													!l0 is value of psr
        or  %g5, SPARC_PSR_PIL_MASK, %g5    !不要求中断嵌套   	
        wr  %g5, SPARC_PSR_ET_MASK, %psr 		!打开中断使能
        nop
        nop
        nop

/*--------------------6、7、跳转、运行用户中断处理程序-----------------------------------*/

				call	CPUDispatchIRQ			
        nop

/*-----------------------8、恢复现场--------------------------------------------------*/

				mov %l0, %psr              ! **** DISABLE TRAPS ****
        nop
        nop
        nop

simple_return:  
        ld   [%sp + ISF_Y_OFFSET], %l5      ! restore y
        wr   %l5, 0, %y

        ldd  [%sp + ISF_PSR_OFFSET], %l0    ! restore psr, PC
        ld   [%sp + ISF_NPC_OFFSET], %l2    ! restore nPC
        rd   %psr, %l3
        and  %l3, SPARC_PSR_CWP_MASK, %l3   ! want "current" CWP
        andn %l0, SPARC_PSR_CWP_MASK, %l0   ! want rest from task
        or   %l3, %l0, %l0                  ! install it later...
        andn %l0, SPARC_PSR_ET_MASK, %l0

        ld   [%sp + ISF_G1_OFFSET], %g1    ! restore g1                                      ! g1 is restored later
        ldd  [%sp + ISF_G2_OFFSET], %g2    ! restore g2, g3
        ldd  [%sp + ISF_G4_OFFSET], %g4    ! restore g4, g5
        ldd  [%sp + ISF_G6_OFFSET], %g6    ! restore g6, g7

        ldd  [%sp + ISF_I0_OFFSET], %i0    ! restore i0, i1
        ldd  [%sp + ISF_I2_OFFSET], %i2    ! restore i2, i3
        ldd  [%sp + ISF_I4_OFFSET], %i4    ! restore i4, i5
        ldd  [%sp + ISF_I6_FP_OFFSET], %i6 ! restore i6/fp, i7


/*--------------------9、判断窗口是否下溢-----------------------------------*/

				mov  %l0, %psr                  	 !  **** DISABLE TRAPS ****
        nop
        nop
        nop
        rd   %wim, %l4
        add  %l0, 1, %l6                   ! l6 = cwp + 1
        and  %l6, SPARC_PSR_CWP_MASK, %l6  ! do the modulo on it
        srl  %l4, %l6, %l5                 ! l5 = win >> cwp + 1 ; shift count
                                           !  and CWP are conveniently LS 5 bits
        cmp  %l5, 1                        ! Is tasks window invalid?
        bne  good_task_window

				sll  %l4, 1, %l5                	 ! l5 = WIM << 1
        srl  %l4, NWINDOWS-1 , %l4         ! SPARC_NUMBER_OF_REGISTER_WINDOWS
                                           ! l4 = WIM >> (Number Windows - 1)
        or   %l4, %l5, %l4                 ! l4 = (WIM << 1) |
                                           !      (WIM >> (Number Windows - 1))

				wr   %l4, 0, %wim               	 ! WIM = new WIM
        nop                                ! must delay after writing WIM
        nop
        nop
        restore                            ! now into the tasks window

        ldd  [%sp + CPU_STACK_FRAME_L0_OFFSET], %l0
        ldd  [%sp + CPU_STACK_FRAME_L2_OFFSET], %l2
        ldd  [%sp + CPU_STACK_FRAME_L4_OFFSET], %l4
        ldd  [%sp + CPU_STACK_FRAME_L6_OFFSET], %l6
        ldd  [%sp + CPU_STACK_FRAME_I0_OFFSET], %i0
        ldd  [%sp + CPU_STACK_FRAME_I2_OFFSET], %i2
        ldd  [%sp + CPU_STACK_FRAME_I4_OFFSET], %i4
        ldd  [%sp + CPU_STACK_FRAME_I6_FP_OFFSET],%i6
                                           ! reload of sp clobbers ISF
        save                               ! Back to ISR dispatch window

good_task_window:

        mov     %l0, %psr                  !  **** DISABLE TRAPS ****
	    	nop
        nop
        nop
        
        
        
/*--------------------10、返回被中断打断的代码-----------------------------------*/

  			jmp   %l1                         ! transfer control and
        rett  %l2                         ! go back to tasks window
        nop

/*-------------------------------END------------------------------------------------*/
    
    .global  OS_DisableInt
	.global	 OS_EnableInt


OS_DisableInt:
	rd      %psr, %o0
	andn		%o0, 0xFFFFFFDF, %o0    /* disable hardware ints */
	wr      %o0, %g0, %psr
	nop
	nop
	nop
	retl						/* return to caller */
	nop
	
OS_EnableInt:
	rd		%psr, %o0
	or		%o0, 0x20, %o0       	/* interrupts enabled */
	wr		%o0, %g0, %psr
	nop
	nop
	nop
	retl						/* return to caller */
	nop




.data
	.global _fsrinit, _fpdata
.align 8
_fsrinit:
	.word 0

.align 8
_fpdata:
    .word 0,0

