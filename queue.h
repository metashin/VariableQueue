#include "stdint.h"
#include "stdlib.h"
#include "string.h"


#define MAXBUF_SIZE 1024
#define MAX_N_OF_Q 256
#ifndef MMALLOC
  #define MMALLOC malloc
#endif
#ifndef MMFREE
  #define MMFREE  free
#endif
typedef struct _QBUF QBUF;
struct _QBUF{
    uint16_t length;
    uint8_t* buf;
};

typedef struct _QUEUE QUEUE;
struct _QUEUE{
  QUEUE * prev;
  QUEUE * next;
  QBUF data;
};

void initQueue(void);
QUEUE* createQueue(void);
void enQue(uint16_t size, uint8_t* Data);
void delLastQue(void);
void delFirstQue(void);
void delQue(uint8_t index);
void insertData(QUEUE* pQue,uint16_t size, uint8_t*Dat);
void appendQueue(QUEUE* newq);
QUEUE* getQueueTail(void);
QUEUE* getQueueHead(void);
QUEUE* getQueueIndex(uint8_t index);
uint8_t* getBufTail(void);
uint16_t getBufSizeTail(void);
uint8_t* getBuf(uint8_t index);
uint16_t getBufSize(uint8_t index);
uint16_t getQueCnt(void);


