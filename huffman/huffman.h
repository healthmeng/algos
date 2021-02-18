#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

typedef struct _HFTree{
	int data;
	int weight;
	int lchild,rchild,parent;
}HFNode,HFTree;

HFTree* InitTree(int num);
void CreateTree(HFTree* arr, int num);
const char PrtCode(int data,char* code);
int Decode(const char* code);

#endif
