#include "bits.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int c ,char **v){
	BITS* root=GetNewPiece();
	if(c>2){
		int len=atoi(v[2]);
		int num=atoi(v[1]);
		AddTail(root,num,len);
		PrtBits(root);
		AddTail(root,num,len);
		PrtBits(root);
	}
	else if(c>1){
		BITS* cur=AddString(root,v[1]);
		PrtBits(root);
		AddString(cur,v[1]);
		PrtBits(root);
	}

	return 0;
}
