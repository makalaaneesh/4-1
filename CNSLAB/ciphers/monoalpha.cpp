#include<stdio.h>
#include<malloc.h>
#include<algorithm>
#include<map>

using namespace std;

map<char,char> encryption;
map<char,char> decryption;



void mono_alpha(char *str){
	int i  = 0;
	while(str[i] != '\0'){
		//printf("encryp of %c is %c\n", str[i], encryption[str[i]]);
		str[i] = encryption[str[i]];
		i++;
	}
	printf("Mono alphabetic text is %s\n", str);
}

void un_mono_alpha(char *str){
	int i = 0;
	while(str[i] != '\0'){
		str[i] = decryption[str[i]];
		i++;
	}
	printf("Original text is %s\n", str);
}



int main(){
	int n;
	printf("Enter the number of characters you want to create a map for\n");
	scanf("%d", &n);
	char a, b;
	while(n--){
		printf("hell\n");
		scanf(" %c", &a);
		scanf(" %c", &b);
		encryption[a] = b;
		decryption[b] = a;
	}
	printf("Enter string\n");
	char * str = (char*)malloc(sizeof(char)*100);
	scanf("%s", str);
	printf("-%s-\n", str);
	mono_alpha(str);
	un_mono_alpha(str);

}

