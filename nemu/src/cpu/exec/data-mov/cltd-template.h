#include "cpu/exec/template-start.h"

#define instr cltd

make_helper(concat(cltd_,SUFFIX))
{
	if(REG(R_EAX)<0) cpu.edx=0xffffffff;
	else cpu.edx=0;
	print_asm_template1();
    return 1;
}

#include "cpu/exec/template-end.h"

