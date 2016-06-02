#include "stdio.h"

void has_all_unique(char str[], int n) {
	int i=0, j=0;
	for (i=0; i<n;i++) {
		for(j=i+1;j<n;j++) {
			if (str[i]==str[j]) {
		        printf("\nNot all are unique");	
                return;
			}
		}
	}
	printf("\nall are unique");	

}


void remove_all_dup(char str[], int n) {
	int i=0, j=0;
	for (i=0; i<n;i++) {
		for(j=i+1;j<n;j++) {
			if (str[i]==str[j]) {
				str[j]=str[j+1];
				j--;n--;
			}
		}
	}
        printf("\n Removed duplicates %s", str);
}

void is_anagram(char str[],char str1[], int n,int m) {
	int i=0, j=0, found=0;
        if (n!=m) {
            printf("\n Its not an anagram:%s %s", str, str1);
            return;
        }
	for (i=0; i<n;i++) {
		for(j=0;j<n;j++) {
			if(str[i]==str1[j])found=1;
		}
		if(!found) {
                    printf("\nIts Not an anagram: %s %s", str, str1);
                    return;
                }
	}
	printf("\nIts an anagram: %s %s", str, str1);
        return;
}

void replace(char str[], int n) {
	int i=0;
	for (i=0; i<n;i++) {
		if(str[i]==' ')str[i]='%20';
	}
        printf("\nreplaced: %s",str);
}

void rotate(char matrix[10][10], int n) {
}


void main() {
    char str[10] = "abcadef";
    char str1[10] = "afecdb";
    int n = 7, m = 6;
    has_all_unique(str,n);
    replace(str,n);    
    remove_all_dup(str, n);
    n=6;
    is_anagram(str,str1,n,m);
    
}
