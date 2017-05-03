#include "cpu/exec/template-start.h"

#define instr test

static void do_execute()
{
	DATA_TYPE result=op_src->val&op_dest->val;
    cpu.EFLAGS.bits.ZF=(result==0);
	cpu.EFLAGS.bits.SF=(result>>31)&1;		
    //cpu.EFLAGS.bits.SF=MSB(result);
	uint32_t pf=(result&0xff);
	pf=(pf>>4)&pf;
	pf=(pf>>2)&pf;
	pf=(pf>>2)&pf;
	cpu.EFLAGS.bits.PF=pf&1;
	cpu.EFLAGS.bits.CF=0;
    cpu.EFLAGS.bits.OF=0;
/*DATA_TYPE result=op_dest->val&op_src->val;
cpu.EFLAGS.bits.CF=0;
uint32_t pf=(result&0xff);
int i;
int flag=1;
for(i=0;i<8;i++)
{
	if(((pf>>i)&0x1)==1)
	{
		if(flag==1) flag=0;
		else flag=1;
	}
}
if(flag==1) pf=1;
if(flag==0) pf=0;
cpu.EFLAGS.bits.PF=pf;
cpu.EFLAGS.bits.ZF=(result==0);
cpu.EFLAGS.bits.SF=(result>>31)&1;
cpu.EFLAGS.bits.OF=0;*/
print_asm_template1();
}
make_instr_helper(r2rm)
#include "cpu/exec/template-end.h"
