//Test Code
#include "queue.h"
uint8_t tempBuf[] = {1,2,3,4,5,6,7,8,9,'A','B','C','D'};
void main(void){
  printf("Start\n");
  initQueue();
  enQue(14,tempBuf);
  enQue(4,&tempBuf[8]);
  enQue(5,&tempBuf[5]);
  insertData(getQueueHead(),5,&tempBuf[1]);
  for(int i =0; i<getQueCnt(); i++){
    printf("index :%d\n",i);
    QUEUE* tempQ =getQueueIndex(i); 
    printHexArray(tempQ->data.buf,tempQ->data.length);
  }
  int m = getQueCnt();
  for(int i =0; i < m;i++){
    printf("index :%d\n",i);
    QUEUE* tempQ = getQueueIndex(0);
    printHexArray(tempQ->data.buf,tempQ->data.length);
    delFirstQue();
  }
}