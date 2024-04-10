#include <stdio.h>
#include "slot.h"
#include "com.h"

int32_t receive_char()
{ 
	  int32_t c = getchar();
		return c;
}


void receive_command(unsigned char* com, unsigned int* len)
{
	unsigned int i = 0;
	unsigned char c;
	do
	{
		c = receive_char();
		if (c != 0xA) com[i] = c;
		i++;
	}	while(c != 0xA);
  com[i-1] = 0; // add terminal zero
	*len = i-1;
  printf((char const*)com); /* echo command */
  printf("\n");
}

void receive_and_process_command()
{
	unsigned char c[12];
	unsigned int size;
  receive_command(c, &size);
  slot_process_command(c, size);
}

void slot_error(int error)
{
  printf("error\n");
}

int main(int argc, char**argv)
{
        printf("ready...\n");
	while(1)
	{
		receive_and_process_command();
	}
}

typedef struct 
{
  unsigned int r0;
  unsigned int r1;
  unsigned int r2;
  unsigned int r3;
  unsigned int r12;
  unsigned int lr;
  unsigned int pc;
  unsigned int flags;
}saved_regs_t;

void dump_stack(saved_regs_t* regs) 
{
  printf("Stack dump\n");
  printf("PC: 0x%08x, SP: 0x%08x\n", regs->pc, (unsigned int)regs + sizeof(saved_regs_t));
  printf("R0: 0x%08x, R1: 0x%08x, R2: 0x%08x, R3: 0x%08x\n", regs->r0, regs->r1, regs->r2, regs->r3);
}

