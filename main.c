//Test Code
#include "queue.h"
#include "stdio.h"
void printHexArray(uint8_t* buf,uint16_t size);
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
  for(int i =0; i < getQueCnt(); i++){
    printf("index :%d\n",i);
    QUEUE* tempQ = getQueueIndex(0);
    printHexArray(tempQ->data.buf,tempQ->data.length);
    delFirstQue();
  }
}
void printHexArray(uint8_t* buf,uint16_t size){
  for(int j = 0; j<size;j++){
    printf("%.2X",buf[j]);
    if(3 == (j%4)){printf(" ");}
    if(15 == (j%16)){printf("\n");}
  }
  printf("\n");
}