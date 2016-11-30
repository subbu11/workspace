#include <stdint.h>

#define SERVER_PORT 8999

#define MSG_DATA_MAX_LEN (15000)

typedef struct MsgS
{
    int len;
    char data[MSG_DATA_MAX_LEN];
    uint64_t u64;
    uint32_t u32[2];
    uint8_t  u8[8];
} MsgT;
