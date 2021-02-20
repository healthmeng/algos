#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#define SWAP(m1,m2) do{m1^=m2;m2^=m1;m1^=m2;}while(0)
#define CHARS 5

typedef struct _HFTree{
	int data;
	int weight;
	int lchild,rchild,parent;
}HFNode,HFTree;

HFTree* InitTree(int num);
void CreateTree(HFTree* arr, int num);
const char PrtCode(int data,char* code);
int Decode(const char* code);
void GetData(HFTree* arr);
void CreateCodes(HFTree* arr,int num, char s[CHARS][CHARS]);
int FindCode(HFTree* tree, int num, const char* str);
void TestDecode(HFTree* tree, int num);
#endif
