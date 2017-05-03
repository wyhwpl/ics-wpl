#include "cpu/exec/template-start.h"

#define instr xor

static void do_execute () {
	DATA_TYPE result = op_dest->val ^ op_src->val;
	OPERAND_W(op_dest, result);
    cpu.EFLAGS.bits.OF=0;
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
    cpu.EFLAGS.bits.SF=(result>>31)&0x1;
    cpu.EFLAGS.bits.CF=0;	
	/* TODO: Update EFLAGS. */
//	panic("please implement me");

	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
