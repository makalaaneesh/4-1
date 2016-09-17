#include<stdio.h>
#include<malloc.h>
#include<algorithm>
#include<map>
#include<vector>


using namespace std;

vector<int> key;
vector<int> value;
vector<int> ans;


void gen_key(){
	printf("key is ");
	for(int i = 0; i< 5; i++){
		int num = rand()%2;
		printf("%d",num);
		key.push_back(num);
	}
	printf("\n");
	
}


void otpe(){
	for(int i = 0; i<value.size(); i++){
		int num = value[i] ^ key[i];
		ans.push_back(num);
	}
	printf("otp encrypted value is ");
	for(int i = 0; i<ans.size(); i++){
		printf("%d",ans[i]); 
	}
	printf("\n");

}

void otpd(){
	vector<int> original;
	for(int i = 0; i< ans.size(); i++){
		int num = key[i] ^ ans[i];
		original.push_back(num);
		
	}
	printf("original value is ");
	for(int i = 0; i<original.size(); i++){
		printf("%d",original[i]); 
	}
	printf("\n");




}


int main(){
	gen_key();
	value.push_back(1);
	value.push_back(0);
	value.push_back(1);
	value.push_back(1);
	value.push_back(0);

	

	otpe();
	otpd();
	
	
}


