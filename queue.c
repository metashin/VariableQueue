#include "queue.h"
char NullChar = 0;
QUEUE* First = NULL;
QUEUE* Last = NULL;
uint16_t qCnt = 1;

void initQueue(void){
  First = Last = createQueue();
}
QUEUE* createQueue(void){
  QUEUE* tempQ = NULL;
  tempQ = (QUEUE*)MMALLOC(sizeof(QUEUE*));
  tempQ->data.buf = &NullChar;
  tempQ->data.length = 0;
  tempQ->next=NULL;
  tempQ->prev=NULL;
}
void enQue(uint16_t size, uint8_t* Data){
  if(MAXBUF_SIZE < size){return;}
  if(MAX_N_OF_Q < qCnt){return;}
  if(0 == size){return;}  
  QUEUE* newQ = createQueue();
  newQ->data.buf = (uint8_t*)MMALLOC(size);
  newQ->data.length = size;
  memcpy(newQ->data.buf, Data, size);
  appendQueue(newQ);
  qCnt++;
}
void delLastQue(void){
  QUEUE *tempQ = Last;
  if(2 > qCnt){return;}
  if(NULL == Last){return;}
  Last->data.length=0;
  Last = Last->prev;
  Last->next = NULL;
  MMFREE(tempQ);
  qCnt--;
}
void delFirstQue(void){
  QUEUE *tempQ = First;
  if(2 > qCnt){return;}
  if(NULL == First){return;}
  First->data.length=0;
  First = First->next;
  First->prev=NULL;
  MMFREE(tempQ);
  MMFREE(tempQ->data.buf);
  qCnt--;
}
void delQue(uint8_t index){
  if(2 > qCnt){return;}
  if((index+1) > qCnt){return;}
  if(0 == index){delFirstQue();return;}  
  if((index+1) == qCnt){delLastQue();return;}
  QUEUE* tempQ = getQueueIndex(index);
  tempQ->prev->next = tempQ->next;
  tempQ->next->prev = tempQ->prev;
  if(NULL != tempQ->data.buf){
    MMFREE(tempQ->data.buf);
    tempQ->data.length=0;
  }
  MMFREE(tempQ);
  qCnt--;
}
void insertData(QUEUE* pQue,uint16_t size, uint8_t*Dat){
  if(0 == size){return;}
  if(0 != pQue->data.length){
    MMFREE(pQue->data.buf);
  }
  pQue->data.length = size;
  pQue->data.buf = (uint8_t*)MMALLOC(size);
  memcpy(pQue->data.buf, Dat, size);
}
void appendQueue(QUEUE* newq){
  Last->next = newq;
  newq->prev = Last;
  newq->next = NULL;
  Last = newq;
}
QUEUE* getQueueTail(void){
  return Last;
}
QUEUE* getQueueHead(void){
  return First;
}
QUEUE* getQueueIndex(uint8_t index){
  if(index > qCnt){return NULL;}
  uint8_t ind =0;
  QUEUE* pQ=First;
  for(;ind != index;ind++){
    if(pQ->next == NULL){return pQ;}
    pQ = pQ->next;
  }
  return pQ;
}
uint8_t* getBufTail(void){
  return Last->data.buf;
}
uint16_t getBufSizeTail(void){
  return Last->data.length;
}
uint8_t* getBuf(uint8_t index){
  return getQueueIndex(index)->data.buf;
}
uint16_t getBufSize(uint8_t index){
  return getQueueIndex(index)->data.length;
}
uint16_t getQueCnt(void){
  return qCnt;
}


