#include "cpu/exec/template-start.h"

#define instr jne

static void do_execute()
{
	if(cpu.EFLAGS.bits.ZF==0)
	{
	 cpu.eip+=(DATA_TYPE_S)op_src->val;
	}
#if DATA_BYTE==2
	cpu.eip&=0xffff;
#endif
	print_asm_template1();
}
make_instr_helper(i)

#include "cpu/exec/template-end.h"

