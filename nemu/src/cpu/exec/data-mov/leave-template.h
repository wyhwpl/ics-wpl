#include "cpu/exec/template-start.h"

#define instr leave

make_helper(concat(leave_,SUFFIX))
{
    cpu.esp=cpu.ebp;
 #if DATA_BYTE==2
	REG(R_BP)=MEM_R(cpu.esp);
 #elif DATA_BYTE==4
    cpu.ebp=MEM_R(cpu.esp);
 #endif
	cpu.esp=cpu.esp+DATA_BYTE;
//	printf("leava's eip:%x esp:%x ebp:%x\n",cpu.eip,cpu.esp,cpu.ebp);
//    print_asm_template1();
//    print_asm("leave");
	return 1;
}

#include "cpu/exec/template-end.h"
