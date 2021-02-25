#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "huffman.h"


void SelectNode(HFTree* arr, int num)
{
	int i;
	int min1, min2,n1,n2;
	int get;
	for(i=0,get=0;get<2;i++){
			if(i>=num){
				printf("Impossible,there must be some errors!\n");
				exit(1);
			}
			if(arr[i].parent==-1){
					if(get==0){
						min1=arr[i].weight;
						n1=i;
					}else{
						min2=arr[i].weight;
						n2=i;
					}
					get++;
			}
	}
	if(min1>min2){
		int temp;
		SWAP(min1,min2);
		SWAP(n1,n2);
	}
	for(/*i has the proper value*/;i<num;i++){
		if(arr[i].parent==-1){
			if(arr[i].weight<min2){
				min2=arr[i].weight;
				n2=i;
			}
			if(min1>min2){
				SWAP(min1,min2);
				SWAP(n1,n2);
			}
		}
	}
	arr[i].weight=min1+min2;
	arr[i].lchild=n1;
	arr[i].rchild=n2;
	arr[n1].parent=i;
	arr[n2].parent=i;
}

void CreateTree(HFTree* arr, int num)
{
	int i;
	for(i=0;i<num-1;i++)
			SelectNode(arr,num+i);
}

HFTree* InitTree(int num)
{
	HFTree* root=(HFTree*)malloc(sizeof(HFNode)*(num));
	int i;
	for(i=0;i<num;i++)
	{
		memset(root+i,0,sizeof(HFNode));
		root[i].parent=root[i].lchild=root[i].rchild=-1;
	}
	return root;
}

void GetData(HFTree* tree){
	int i;
/*	for(i=0;i<CHARS;i++){
			printf("ascii:");
			scanf("%c",&tree[i].data);
			printf("times:");
			scanf("%d",&tree[i].weight);
	}*/
	for(i=0;i<CHARS;i++)
	{
	//	tree[i].data=i;
		tree[i].weight=rand()%100;
	}
	for(i=CHARS-1;i>CHARS-10;i--)
	{
		tree[i].weight=rand()%10000;
	}
}

void CreateCodes(HFTree* tree, int num, char codes[CHARS][CHARS])
{
	int i=0;
	for(i=0;i<num;i++)
	{
		char temp[CHARS]={'\0'};
		int start=num-1;
		int cur;
		for(cur=i;tree[cur].parent!=-1;cur=tree[cur].parent)
		{
			if(tree[tree[cur].parent].lchild==cur)
				temp[start-1]='0';
			else
				temp[start-1]='1';
			start--;
		}
		strcpy(codes[i],temp+start);
	}
}

void PrtCodes(HFTree* tree,char codes[CHARS][CHARS],int num)
{
	int i;
	for(i=0;i<num;i++)
			printf("%c:%d->%s\n",i,tree[i].weight,codes[i]);
}

int FindCode(HFTree* tree,int num,const char* s){
	int i=num*2-1-1;
	int bit=0;
	int n;
	do{
		if(s[bit]=='\0') break;
		n=s[bit]-'0';
		if(n!=0 && n!=1){
			printf("error codes\n");
			return 0;
		}	
		/* now we have got a new bit from s */
		if(tree[i].lchild==-1) return 0;
		if(n==0)
			i=tree[i].lchild;
		else i=tree[i].rchild;
		bit++;
	}while(s[bit]!='\0');
	if(tree[i].lchild==-1) return i;
	else return 0;
}

void TestDecode(HFTree* tree, int num)
{
	char s[1024];
	int ascii;
	printf("Input decoded string:");
	scanf("%s",s);
	ascii=FindCode(tree,num,s);
	if(ascii){
		printf("Find origin char: %c\n",ascii);
	}else{
		printf("Invalid decoded string!\n");
	}
}

int main()
{
	int num=CHARS;
	int i;
	char codes[CHARS][CHARS];
	HFTree* arr=InitTree(num*2-1);
	GetData(arr);
	CreateTree(arr,num);
	CreateCodes(arr,num,codes);
	PrtCodes(arr,codes,num);
	TestDecode(arr,num);
	return 0;
}
