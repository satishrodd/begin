#include "stdio.h"

void has_all_unique(char str[], int n) {
	int i=0, j=0;
	for (i=0; i<n;i++) {
		for(j=i+1;j<n;j++) {
			if (str[i]==str[j]) {
		        printf("Not all are unique");	
                return;
			}
		}
	}
	printf("all are unique");	

}


void remove_all_dup(char str[], int n) {
	int i=0, j=0;
	for (i=0; i<n;i++) {
		for(j=i;j<n;j++) {
			if (str[i]==str[j]) {
				str[j]=str[j+1];
				j--;n--;
			}
		}
	}
}

int is_anagram(char str[], int n) {
	int i=0, j=0, found=0;
	for (i=0; i<n;i++) {
		for(j=i;j<n;j++) {
			if(str[i]==str[j])found=1;
		}
		if(!found) return(0);
	}
	return(1);
}

void replace(char str[], int n) {
	int i=0;
	for (i=0; i<n;i++) {
		if(str[i]==' ')str[i]='%20';
	}
}

void rotate(char matrix[10][10], int n) {
}

void main() {
	char str[10] = "abcdaerfgh";
    has_all_unique(str,9);
        
    
}
