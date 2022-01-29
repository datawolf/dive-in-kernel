#include <stdio.h>

int main(){
	int i = 0;
	int j = 0;
	int n = 0;

	for(i = 0; i< 10000; i++) {
		for(j = 0; j < 100000; j++)
			n = i*j;
	}
	return 0;
}
