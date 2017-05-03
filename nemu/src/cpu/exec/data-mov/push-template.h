#include "cpu/exec/template-start.h"

#define instr push

static void do_execute()
{
	cpu.esp-=DATA_BYTE;
	swaddr_write(cpu.esp,DATA_BYTE,op_src->val);
/*#if DATA_BYTE==1
cpu.esp-=4;
uint32_t t=op_src->val;
swaddr_write(cpu.esp,4,t);
#endif
#if DATA_BYTE==2||DATA_BYTE==4
cpu.esp-=DATA_BYTE;
swaddr_write(cpu.esp,DATA_BYTE,op_src->val);
#endif*/
    print_asm_template1();
//	printf("push's eip:%x esp:%x op_src->val:%x\n",cpu.eip,cpu.esp,op_src->val);
}

make_instr_helper(r)
make_instr_helper(rm)
make_instr_helper(i)
#include "cpu/exec/template-end.h"
