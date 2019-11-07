#define TAG_SIZE  32
#define KEY_SIZE  16

#define MODE_DEBUG      0x00000000
#define MODE_NORMAL    0x00000001
#define MODE_RETURN    0x00000003

typedef struct
{
    unsigned char*  address;
    unsigned int    size;
    unsigned char   tag[TAG_SIZE];
}firmware_header_t;

void firmware(void)
{
  /* !!! */ 
  while(1);
}


/* flash data */
const firmware_header_t FirmwareHeader = 
{
  .address = (unsigned char*)firmware,
  .size = 50,
  .tag = {0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00}
};

void recovery(void)
{
  /* FULL ACCESS */
  while(1);
}

/* OTP data */
const firmware_header_t RecoveryFirmwareHeader = 
{
  .address = (unsigned char*)recovery,
  .size = 0,
  .tag = {0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00}
}; 
const unsigned char Key[KEY_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x00, 0x01, 0x02, 0x03, 0x00, 0x01, 0x02, 0x03, 0x00, 0x01, 0x02, 0x03};
const unsigned int Mode = MODE_NORMAL; /* in OTP */

unsigned int GetMode(void)
{
    return Mode;
}


unsigned int IsEqual(const unsigned char* s1, const unsigned char* s2, unsigned int size)
{
    unsigned int i;
    unsigned int res = 0;
    for(i=0;i<size;i++)
    {
        res |= s1[i] ^ s2[i]; 
    }
    return (res == 0);
}

void ComputeTag(const unsigned char* message, unsigned int size, unsigned char* tag)
{
    unsigned int i;
    for(i=0;i<size;i++)
    {
        tag[i % TAG_SIZE] = i 
                            ^ Key[i % KEY_SIZE] 
                            ^ message[i] 
                            ^ message[(i+1) % size]
                            ^ message[(i+2) % size]; 
    }
}
unsigned int IsFWValid(const firmware_header_t* firmware)
{
    unsigned char tag[TAG_SIZE];
    ComputeTag(firmware->address, firmware->size, tag);
    return IsEqual(firmware->tag, tag, TAG_SIZE);
}

void ExecuteFW(const firmware_header_t* firmware)
{
  ((void (*)(void)) firmware->address)();
  /* should not come back here */
}


void main(void)
{
    unsigned int mode = GetMode();
    if(mode == MODE_NORMAL)
    {
        if(IsFWValid(&FirmwareHeader))
        {
            ExecuteFW(&FirmwareHeader);
            /* should not return here */
        }
        else
        {
            while(1); /* infinite loop if FW is not valid */
        }
    }
    if(mode != MODE_RETURN)
    {
      ExecuteFW(&FirmwareHeader); /* DEBUG mode */
      /* should not return here */
    }
    ExecuteFW(&RecoveryFirmwareHeader); /* RETURN mode */
}
