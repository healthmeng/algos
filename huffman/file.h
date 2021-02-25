#ifndef __FILE_H__
#define __FILE_H__
#include "huffman.h"

typedef struct _SPNODE{
	short int parent,lchild,rchild;
}__attribute__((packed)) SPNODE;

typedef struct _HFHEADER{
	short int treenum; 
	SPNODE hftree[CHARS*2-1];
	unsigned long long fsize;
}__attribute__((packed)) FileHeader;

int CompressFile(const char* src,const char* dst);
void WriteFileHeader(FILE *fp,HFTree* root, FileHeader* h);
void WriteCompressFile(FILE* dst, FILE* src, const FileHeader* header);
int DecompressFile(const char* src, const char* dst);

#endif
