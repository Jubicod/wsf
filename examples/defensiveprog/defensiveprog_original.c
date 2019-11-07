
status_t Send(handle_t handle, message_type_t type, 
                uint8_t* message, uint32_t size)
{ 
  context_t* context;
  assert(handle != NULL);
  /* bit 0 and 1 of handles are always 1. 
  other bits represent a 32 bit aligned pointer to the context*/
  context = (context_t*)handle & ~0x3;  
  if(type = MESSAGE_HELLO)
  {
    /* message is not used, should be NULL anyway, send hello */
    return UART_Send(context->uart, "hello",
                        sizeof("hello"));
  }
  if(type == MESSAGE_FREE)
  {
    if(size < MESSAGE_MAX_SIZE)
    {
        return UART_Send(context->uart, message, size);
    }
  }
  /* message should be MESSAGE_ACK */
  /* wait for input */
  {
    unint8_t inVar = 0;
    if(inVar = getc(input) != EOF)
    {
        return UART_Send(context->uart, inVar, 1);
    }
    else
        return ERROR;
  }
}
 

  