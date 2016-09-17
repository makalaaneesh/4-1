#include<stdio.h>
#include<malloc.h>
#include<algorithm>
#include<map>
#include<vector>
#include<iostream>


using namespace std;

vector<char> alpha;
vector<vector<char> >table;

string key;
string input;
string output;



void init(){
	char c = 'a';
	for(int i = 0; i< 26; i++){
		alpha.push_back(c);
		c++;
	}
	for(int i = 0; i< 26; i++){
		vector<char> temp(alpha);
		table.push_back(temp);
		char first = alpha[0];
		alpha.erase(alpha.begin() + 0);
		alpha.push_back(first);
	}
	key = "deceptive";
	
}



void decrypt(){	
	string original;
	for(int i = 0 ; i<output.length(); i++){
		int row = key[i%key.length()] - 'a';
		
		int col = -1;
		for(int j = 0; j< table[row].size(); j++){
			if(table[row][j] == output[i]){
				col = j;
				break;
			}
		}

		char newchar = col+'a';
		original += newchar;
	}
	cout<<"original is ->"<<original<<endl;
}


int main(){

	init();
	cin>>input;
	for(int i = 0 ; i<input.length(); i++){
		int row = key[i%key.length()] - 'a';
		int col = input[i] - 'a';

		char newchar = table[row][col];
		output += newchar;
	}
	cout<<output<<endl;
	decrypt();
}
