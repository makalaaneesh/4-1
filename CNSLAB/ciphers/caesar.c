#include<stdio.h>
#include<malloc.h>


void caesar(char *str, int k){
	int i = 0;
	while(str[i] != '\0'){
		str[i] =  ((str[i] - 'a' + k) % 26) + 'a' ;
		i++;
	}
	printf("Caeser version is %s\n", str);
		
}

void uncaesar(char *str, int k){
	int i = 0;
	while(str[i] != '\0'){
		str[i] =  ((str[i] - 'a' - k + 26) % 26) + 'a' ;
		i++;
	}
	printf("Original version is %s\n", str);
}

int main(){
	char * str = (char*)malloc(sizeof(char)*100);
	scanf("%s", str);
	caesar(str,3);
	uncaesar(str,3);

}
