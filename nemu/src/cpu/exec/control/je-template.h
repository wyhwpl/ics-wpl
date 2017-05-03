#include "cpu/exec/template-start.h"

#define instr je

static void do_execute()
{
//	printf("%x %x\n",cpu.eip,op_src->val);

if (cpu.EFLAGS.bits.ZF==1)
 {
//	cpu.eip=cpu.eip+(DATA_TYPE_S)op_src->simm;
	cpu.eip=cpu.eip+op_src->val;
	if(DATA_BYTE==2)
	{
		cpu.eip&=0xffff;
 	}
//printf("%x %x\n",cpu.eip,op_src->val);

}
//printf("%x %x\n",cpu.eip,op_src->val);
print_asm_template1();
}
make_instr_helper(i)

#include "cpu/exec/template-end.h"
