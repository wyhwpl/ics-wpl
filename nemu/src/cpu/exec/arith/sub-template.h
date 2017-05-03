#include "cpu/exec/template-start.h"

#define instr sub

static void do_execute()
{
 DATA_TYPE result=op_dest->val-op_src->val;
 cpu.EFLAGS.bits.CF=op_dest->val<op_src->val;
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
 cpu.EFLAGS.bits.OF=((op_dest->val>>31)^(op_src->val>>31))&((op_dest->val>>31)^(result>>31))&1;
/*DATA_TYPE result=op_dest->val-op_src->val;
cpu.EFLAGS.bits.CF=op_dest->val<op_src->val;
cpu.EFLAGS.bits.ZF=(result==0);
cpu.EFLAGS.bits.OF=((op_dest->val>>31)^(op_src->val>>31))&((op_dest->val>>31)^(result>>31))&1;
cpu.EFLAGS.bits.SF=(result>>31)&1;
uint32_t pf=(result&255);
pf=(pf>>4)&pf;
pf=(pf>>2)&pf;
pf=(pf>>1)&pf;
cpu.EFLAGS.bits.PF=(pf&1);*/
 OPERAND_W(op_dest,result);
 print_asm_template2();
}
make_instr_helper(i2rm)
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(si2rm)
#endif
make_instr_helper(rm2r)
#include "cpu/exec/template-end.h"
