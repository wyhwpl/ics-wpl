#include "cpu/exec/template-start.h"

#define instr jmp

static void do_execute()
{
	if(op_src->type==OP_TYPE_IMM)
				 cpu.eip=cpu.eip+op_src->val;
		if(DATA_BYTE==2)
					cpu.eip=cpu.eip&0xffff;
//	cpu.eip=cpu.eip+op_src->val;
  
	print_asm_template1();
}

make_instr_helper(i)

#include "cpu/exec/template-end.h"
