#ifndef __BITS_H__
#define __BITS_H__
#include <stdio.h>

#define CACHE_SIZE 4096

typedef struct _BITS{
	unsigned char chData[CACHE_SIZE];
	int nBits;
	struct _BITS *pNext;
}BITS;

BITS *GetNewPiece();
BITS* AddTail(BITS* store, unsigned long long add, int count);
BITS* AddString(BITS* store, const char* bincode);
BITS* PushBit(BITS* store,int bitdata);
BITS* WriteFile(FILE *fp, int flushlast,int needfree);
BITS* GetBit(BITS* cur,unsigned int* bit);

void PrtBits(BITS* start);

#endif
