#include "cpu/exec/template-start.h"

#define instr ret

make_helper(concat(ret_,SUFFIX))
{
//	REG(R_ESP)=REG(R_EBP);
  #if DATA_BYTE==2
	cpu.ip=MEM_R(REG(R_ESP));
	cpu.eip&=0xffff;
  #elif DATA_BYTE==4
	cpu.eip=MEM_R(REG(R_ESP));
  #endif
    cpu.esp=cpu.esp+DATA_BYTE;
	print_asm("ret");
//	print_asm_template1();
//	printf("ret's eip:%x  esp:%x\n",cpu.eip,cpu.esp);
	return 1;
}

#include "cpu/exec/template-end.h"
