typedef struct
{
  unsigned int r0;
  unsigned int r1;
  unsigned int r2;
  unsigned int r3;
  unsigned int r12;
  unsigned int lr;
  unsigned int pc;
  unsigned int sp;
}interrupt_stack_t;


void fault_skip_instruction(interrupt_stack_t* stack)
{
  /* detect if interrupted instruction is 16 or 32 bits */
  unsigned short ins = *((unsigned short*)stack->pc);
  if(((ins & 0xE000) == 0xE000) 
      && ((ins & 0x1800) != 0))
    stack->pc += 4; /* 32 bits */
  else
    stack->pc += 2; /* 16 bits */
}

static unsigned int m_reg = 0; /* register to fault, R0 by default */

/* only works for register = 0,1,2 or 3 (R0,R1,R2 or R3) */
void fault_clear_register(unsigned int* stack)
{
  stack[m_reg] = 0;
}
