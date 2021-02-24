#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bits.h"

BITS *GetNewPiece(){
	BITS* piece=(BITS*)calloc(sizeof(BITS),1);
	return piece;	
}

BITS* AddTail(BITS* store,unsigned long long data,int nbit){
	BITS* cur=store;
	int start,shift;
	int i;
	unsigned long long *modify;
	while(cur->pNext)
		cur=cur->pNext; // Get last piece
	for(i=0;i<nbit;i++){
		cur=PushBit(cur,(data & ((1<<nbit)-1))>>(nbit-1-i));
	}
	return cur;
}

BITS* AddString(BITS* store, const char* bincode){
	int i;
	BITS* cur=store;
	for(i=0;bincode[i]!='\0';i++){
		if(bincode[i]=='1')
			cur=PushBit(cur,1);
		else if(bincode[i]=='0')
			cur=PushBit(cur,0);
		else {
			printf("Error input");
			exit(1);
		}
	}
	return cur;
}

BITS* PushBit(BITS* store,int bitdata){
	BITS* cur=store;
	if(store->nBits>0 && store->nBits%(CACHE_SIZE*8)==0){
		cur=GetNewPiece();
		cur->chData[0]=bitdata<<7;
		cur->nBits=1;
		store->pNext=cur;
	}else{
		int start=cur->nBits/8;
		int shift=8-cur->nBits%8-1;
		cur->chData[start]|=(bitdata<<shift);
		cur->nBits++;
	}
	return cur;
}

void PrtBits(BITS* start){
	int i;
	for(;start!=NULL;start=start->pNext){
		if(start->nBits<=0) continue;
		for(i=0;i<=(start->nBits-1)/8;i++)
			printf("%02x ",start->chData[i]);
		printf("\n");
	}
}

BITS* GetBit(BITS* cur,unsigned int* bit){
	int start;
	if(cur->nBits==0){
		cur=cur->pNext;
		if(cur==NULL || cur->nBits<1)
			return NULL;
	}
	start=(cur->nBits-1)/8;
	*bit=cur->chData[start]>>7;
	cur->chData[start]<<=1;
	cur->nBits--;
	return cur;
}
