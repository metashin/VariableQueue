#include "queue.h"
QUEUE* First = NULL;
QUEUE* Last = NULL;
uint16_t qCnt = 1;

void initQueue(void){
  First = Last = createQueue();
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
  if(2 > qCnt){
    freeBufInQueue(tempQ);
    return;
  }
  if(NULL == Last){return;}
  freeBufInQueue(tempQ);
  Last = Last->prev;
  Last->next=NULL;
  MFREE(tempQ);
  tempQ=NULL;
  qCnt--;
}
void delFirstQue(void){
  QUEUE *tempQ = First;
  if(2 > qCnt){
    freeBufInQueue(tempQ);
    return;
  }
  if(NULL == First){return;}
  freeBufInQueue(tempQ);
  First = First->next;
  First->prev=NULL;
  MFREE(tempQ);
  tempQ=NULL;
  qCnt--;
}
void delQue(uint8_t index){
  if(2 > qCnt){
    
    return;
  }
  if((index+1) > qCnt){return;}
  QUEUE* tempQ = getQueueIndex(index);
  tempQ->prev->next = tempQ->next;
  tempQ->next->prev = tempQ->prev;
  freeBufInQueue(tempQ);
  MFREE(tempQ);
  tempQ=NULL;
  qCnt--;
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

void printHexArray(uint8_t* buf,uint16_t size){
  for(int j = 0; j<size;j++){
    printf("%.2X",buf[j]);
    if(3 == (j%4)){printf(" ");}
    if(15 == (j%16)){printf("\n");}
  }
  printf("\n");
}
void setFirst(QUEUE* pQ){
  First = pQ;
}
void setLast(QUEUE* pQ){
  Last = pQ;
}
void setQcnt(uint16_t var){
  if(var > MAX_N_OF_Q){return;}
  qCnt=var;
}

QUEUE* createQueue(void){
  QUEUE* tempQ = NULL;
  tempQ = (QUEUE*)MMALLOC(sizeof(QUEUE));
  tempQ->data.buf = NULL;
  tempQ->data.length = 0;
  tempQ->next=NULL;
  tempQ->prev=NULL;
  return tempQ;
}
void insertData(QUEUE* pQue,uint16_t size, uint8_t*Dat){
  if(0 == size){return;}
  if(0 != pQue->data.length){
    MFREE(pQue->data.buf);
  }
  pQue->data.length = size;
  pQue->data.buf = (uint8_t*)MMALLOC(size);
  memcpy(pQue->data.buf, Dat, size);
}
void freeBufInQueue(QUEUE* pQ){
  if(NULL == pQ->data.buf){return;}
  MFREE(pQ->data.buf);
  pQ->data.buf=NULL;
  pQ->data.length=0;
}


void enQueLocal(QUEUE* pQ,uint16_t size, uint8_t* Data){
  uint16_t localQcnt = calQueCnt(pQ);
  if(MAXBUF_SIZE < size){return;}
  if(MAX_N_OF_Q < localQcnt){return;}
  if(0 == size){return;}  
  QUEUE* newQ = createQueue();
  newQ->data.buf = (uint8_t*)MMALLOC(size);
  newQ->data.length = size;
  memcpy(newQ->data.buf, Data, size);
  appendQueueLocal(pQ,newQ);
  qCnt++;
}
uint16_t calQueCnt(QUEUE* pQ){  
  uint16_t i =1;
  for(;pQ->next !=NULL;pQ=pQ->next){
    if(i>MAX_N_OF_Q){return 0x1000;}//0x1000for Error
    i=i+1;
  }
  return i;
}
void appendQueueLocal(QUEUE* localQ, QUEUE* newq){
  QUEUE* lastQ = getQueueTailLocal(localQ);
  lastQ->next = newq;
  newq->prev = lastQ;
  newq->next = NULL;
  lastQ = newq;
}
QUEUE* getQueueTailLocal(QUEUE* pQ){
  uint16_t k = calQueCnt(pQ);
  QUEUE* tempQ = pQ;
  for(;tempQ->next !=NULL;tempQ=tempQ->next){
    if(k>MAX_N_OF_Q){return NULL;}
    k--;
  }
  return tempQ;
}
QUEUE* getQueueHeadLocal(QUEUE* pQ){
  uint16_t k = calQueCnt(pQ);
  QUEUE* tempQ = pQ;
  for(;tempQ->prev !=NULL;tempQ=tempQ->prev){
    if(k>MAX_N_OF_Q){return NULL;}
    k--;
  }
  return tempQ;
}

void changeQue(QUEUE* pQ){
  QUEUE* tempQ = pQ;
  uint16_t cnt = 0;
  setLast(pQ);
  tempQ = getQueueHeadLocal(pQ);
  cnt = calQueCnt(tempQ);
  setFirst(tempQ);
  setQcnt(cnt);
}
