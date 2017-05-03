#include "cpu/exec/template-start.h"

#define instr call

static void do_execute()
{
	cpu.esp-=DATA_BYTE;
	MEM_W(REG(R_ESP),cpu.eip+DATA_BYTE);
//	cpu.eip+=op_src->val;
//swaddr_write(REG(R_ESP),DATA_BYTE,cpu.eip+DATA_BYTE);
// MEM_W(REG(R_ESP),cpu.eip+DATA_BYTE);
cpu.eip+=op_src->val;
print_asm_template1();
}
make_instr_helper(i)

#include "cpu/exec/template-end.h"
