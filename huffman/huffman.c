#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "huffman.h"

int compweight(const void* e1, const void* e2){
		HFTree* t1=(HFTree*)e1;
		HFTree* t2=(HFTree*)e2;
		return t1->weight-t2->weight;
}

void SelectNode(HFTree* arr, int num)
{
	int i;
	int min1, min2,n1,n2;
	for(i=0;i<num*2-1;i++){
		
	}
}

void CreateTree(HFTree* arr, int num)
{
	int i;
	qsort(arr,num,sizeof(HFTree),compweight);
	for(i=0;i<num-1;i++)
			SelectNode(arr,num);
}

HFTree* InitTree(int num)
{
	HFTree* root=(HFTree*)malloc(sizeof(HFNode)*(num*2-1));
	int i;
	for(i=0;i<num;i++)
		memset(root+i,0,sizeof(HFNode));
	return root;
}

int main()
{
	int num=5;
	int i;
	HFTree* arr=InitTree(num);

	return 0;
}
