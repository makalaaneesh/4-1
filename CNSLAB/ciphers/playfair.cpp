#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<math.h>
using namespace std;




int findRow(char play[5][5],char x){
	int i,j;
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			if((x=='j'&&play[i][j]=='i')||(play[i][j]==x)) return i;
		}
	}
}
int findCol(char play[5][5],char x){
	int i,j;	
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			if((play[i][j]==x)||(x=='j'&&play[i][j]=='i')) return j;
		}
	}
}
int main(){
	
	string input;
	string output = "";
	cin>>input;
	string keyword = "monarchy";
	char table[5][5];
	int all[25];	
	int i,j,k;



	for(i=0;i<26;i++){
		all[i]=0;
	}
	for( i=0,j=0;i<keyword.length() && j<5;j++){
		for( k=0;i<keyword.length() && k<5;k++,i++){
			table[j][k]=keyword[i];
			all[keyword[i]-'a']=1;
		}
	}
	
	j--;	
	for(i=0;i<26;i++){
		
		if(all[i]==0 && i!=9){
			table[j][k]=i+'a';		
			k++;
			if(k==5){
				k=0;j++;
			}
		}
	}
	
	for(i=0;i<5;i++) {
		for(j=0;j<5;j++) {
			cout<<table[i][j]<<" ";
		}
		cout<<endl;
	}

	char pairs[input.length()][2];
	int index=0;

	for(i=0;input[i+1]!='\0';i++){
		if(input[i+1]!=input[i]){		
			pairs[index][0]=input[i];
			pairs[index][1]=input[i+1];
			index++;				
			i++;
		}
		else{
			pairs[index][0]=input[i];
			pairs[index][1]='x';
			index++;
		}
	}
	int op=0;
	for(i=0;i<index;i++){
		int r1=findRow(table,pairs[i][0]);	
		int r2=findRow(table,pairs[i][1]);
		int c1=findCol(table,pairs[i][0]);
		int c2=findCol(table,pairs[i][1]);
		if(r1==r2){
			//same row 
			//input[op++]=table[r1][(c1+1)%5];
			//input[op++]=table[r1][(c2+1)%5];
			output = output + table[r1][(c1+1)%5] + table[r1][(c2+1)%5];
		}
		else if (c1==c2){
			//same col
			//input[op++]=table[(r1+1)%5][c1];
			//input[op++]=table[(r2+1)%5][c1];
			output = output + table[(r1+1)%5][c1] + table[(r2+1)%5][c1];

		}
			
		else{
			//diff row and col
			
			//input[op++]=table[r1][c2];
			//input[op++]=table[r2][c1];
			output = output + table[r1][c2] + table[r2][c1];
		}
		
	}
	
	cout<<output<<endl;
}
