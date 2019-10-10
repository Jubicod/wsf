#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"

#if 0
volatile int32_t ITM_RxBuffer = ITM_RXBUFFER_EMPTY;
int fputc(int c, FILE* f)
{
	return (ITM_SendChar(c));
}
#endif

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
		//ITM_SendChar(c);
		if (c != 0xA) com[i] = c;
		i++;
	}	while(c != 0xA);
  com[i-1] = 0; // add terminal zero
	*len = i-1;
  printf((char const*)com); /* echo command */
  printf("\n");
}
