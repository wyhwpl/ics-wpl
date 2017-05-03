#include "cpu/exec/template-start.h"

#define instr jbe

static void do_execute()
{
	if(cpu.EFLAGS.bits.CF==1||cpu.EFLAGS.bits.ZF==1)
	{
		cpu.eip=cpu.eip+(DATA_TYPE_S)op_src->val;
//		cpu.eip=cpu.eip+op_src->val;
 		if(DATA_BYTE==2)
		{
			cpu.eip&=0xffff;
		}
	}
/*if(cpu.EFLAGS.bits.CF==1||cpu.EFLAGS.bits.ZF==1)
{	cpu.eip+=(DATA_TYPE_S)op_src->simm;
if(DATA_BYTE==2)
cpu.eip=cpu.eip&0xffff;
}*/
	print_asm_template1();
}

make_instr_helper(i)

#include "cpu/exec/template-end.h"
