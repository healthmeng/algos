#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"
#include "bits.h"
#include "file.h"

void WriteFileHeader(FILE *fp,HFTree* root,int num){
	int i;
	FileHeader h;//=(FileHeader*)calloc(1,sizeof(FileHeader));

	memset(&h,0,sizeof(h));
	strncpy(h.magic,"HFFL",4);
	h.treenum=num;
	for(i=0;i<num;i++)
	{
		h.fsize+=root[i].weight;
		h.hftree[i].data=root[i].data;
		h.hftree[i].parent=root[i].parent;
		h.hftree[i].lchild=root[i].lchild;
		h.hftree[i].rchild=root[i].rchild;
	}
	fwrite(&h,sizeof(FileHeader),1,fp);
}

static long long GetFpLen(FILE *src){
	long long len;
	long long pos;
	pos=ftell(src);
	fseek(src,2,0);
	len=ftell(src);
	fseek(src,0,pos);
	return len;
}

long long WriteCompressFile(FILE* dst, FILE* src, char codes[CHARS][CHARS]){
	long long len,i;
	BITS* cur;
	len=GetFpLen(src);
	cur=GetNewPiece();
	for(i=0;i<len;i++){
		const char* str=codes[i];
		BITS* next=AddString(cur,str);
		if(next!=cur){
			fwrite(cur->chData,CACHE_SIZE,1,dst);
			free(cur);
			cur=next;
		}
	}
	fwrite(cur->chData,(cur->nBits-1)/8+1,1,dst);
	free(cur);
	return ftell(dst);
}

HFTree* CreateHFFromFile(FILE *fp,int *nonzero){
	long long dt[256];
	long long len=GetFpLen(fp);
	long long i;
	HFTree* root;
	*nonzero=0;
	for(i=0;i<len;i++){
		unsigned char ch=fgetc(fp);
		dt[ch]++;
		if(dt[ch]==1)
			(*nonzero)++;
	}
	root=InitTree(*nonzero*2-1);
	SetData(root,dt);
	CreateTree(root,*nonzero);
	return root;
}

long long CompressFile(const char* srcpath, const char* dstpath){
	FILE *src, *dst;
	HFTree* root;
	int treenodes;
	long long flen;
	char codes[CHARS][CHARS];
	src=fopen(srcpath,"rb");
	if(!src)
		return 0;
	dst=fopen(dstpath,"wb");
	if(!dst)
		return 0;
	root=CreateHFFromFile(src,&treenodes);
	WriteFileHeader(dst,root,treenodes);

	CreateCodes(root,treenodes,codes);
	rewind(src);
	flen=WriteCompressFile(dst,src,codes);

	fclose(src);
	fclose(dst);
	return flen;
}
