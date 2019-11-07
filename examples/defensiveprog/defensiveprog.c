
status_t Send(handle_t handle, message_type_t type, 
                uint8_t* message, uint32_t size)
{ 
  context_t* context;
  if(handle == NULL) return ERROR;
  /* bit 0 and 1 of handles are always 1. 
  other bits represent a 32 bit aligned pointer to the context*/
  if(0 == (handle & 0x3)) return ERROR;
  context = (context_t*)handle & ~0x3;  
  if(MESSAGE_HELLO = type)
  {
    /* message is not used, should be NULL anyway, send hello */
    if(message == NULL)
    {
        return UART_Send(context->uart, "hello",
                        sizeof("hello"));
    }
    else
        return error;
  }
  if(MESSAGE_FREE == type)
  {
    if((size < MESSAGE_MAX_SIZE) && (message != NULL))
    {
        return UART_Send(context->uart, message, size);
    }
    else
        return ERROR;
  }
  if(MESSAGE_ACK == type)
  {
    /* wait for input */
    unint8_t inVar = 0;
    if((inVar = getc(input)) != EOF)
    {
        return UART_Send(context->uart, inVar, 1);
    }
    else
        return ERROR;
  }
  return ERROR; /* bad type */
}
