#ifndef __FILE_H__
#define __FILE_H__
#include "huffman.h"

typedef struct _SPNODE{
	unsigned char data;
	short int parent,lchild,rchild;
}__attribute__((packed,aligned(1))) SPNODE;

typedef struct _HFHEADER{
	char magic[4];
	short int treenum; 
	unsigned long long fsize;
	SPNODE hftree[CHARS*2-1];
}__attribute__((packed,aligned(1))) FileHeader;

long long CompressFile(const char* src,const char* dst);
void WriteFileHeader(FILE *fp,HFTree* root, int num);
long long WriteCompressFile(FILE* dst, FILE* src, char codes[CHARS][CHARS]);
int DecompressFile(const char* src, const char* dst);
HFTree* CreateHFFromFile(FILE* fp,int *num);

#endif
