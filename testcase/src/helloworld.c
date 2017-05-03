#include <stdio.h>
#include <string.h>

#include "trap.h"
int main(void){
	printf("Hello,World!\n");
	nemu_assert(0);
	HIT_GOOD_TRAP;
	return 0;
}
