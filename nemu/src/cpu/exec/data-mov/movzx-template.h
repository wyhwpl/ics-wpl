#include "cpu/exec/template-start.h"

#define instr movzb

static void do_execute()
{
	DATA_TYPE result=op_src->val&0xffff;
	OPERAND_W(op_dest,result);
	print_asm_template1();
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
