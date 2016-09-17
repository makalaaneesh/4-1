#include <iostream>
#include <stdio.h>
#include <bitset>
#include <string.h>


using namespace std;


class charset{
	char *str;
	int size;

public:
	charset(char *s, int sz){

		str = s;
		size = sz;
	}

	int get_bit(int i){
		
		int index = i/8;
		int offset = i%8;
		if(offset == 0){
			index--;
		}
		else{
			offset = 8 - offset;
		}
		
		
		char c = str[index];
		// cout<<bitset<8>(c)<<endl;
		// cout<<index<<" "<<offset;
		// cout<<" "<<(c & (1<<offset))<<endl	;
		if (c & (1<<offset))
			return 1;
		else
			return 0;
	}

	int set_bit(int i){
		
		int index = i/8;
		int offset = i%8;
		if(offset == 0){
			index--;
		}
		else{
			offset = 8 - offset;
		}
		char c = str[index];
		// cout<<index<<endl<<offset<<endl;
		c = c | (1 << offset);
		str[index] = c;
	}

	int reset_bit(int i){
		
		int index = i/8;
		int offset = i%8;
		if(offset == 0){
			index--;
		}
		else{
			offset = 8 - offset;
		}
		char c = str[index];
		c = c & ~(1 << offset);
		str[index] = c;
	}

	void print_binary(){
		for(int i = 0; i<size-1; i++){
			cout<<bitset<8>(str[i]);
		}
		cout<<endl;
	}
};



class keyset{
	char inputKey[9];
	char cd[8];
	char roundKey[7];
	int pc1[56]; // 7*8
	int pc2[48]; // 8*6
	int leftshifts[16];

public:
	keyset(char input_key[9], int pc_1[56], int pc_2[48], int ls[16]){

		// cout<<sizeof(input_key)<<sizeof(pc_1)<<sizeof(pc_2)<<sizeof(ls)<<endl;
		// inputKey = input_key;
		memcpy(inputKey, input_key, 9 * sizeof(char));
		memcpy(pc1, pc_1, 56 * sizeof(int));
		memcpy(pc2, pc_2, 48 * sizeof(int));
		memcpy(leftshifts, ls, 16 * sizeof(int));

	}

	void permute1(){
		charset input(inputKey, 9);
		charset output(cd, 8);
		int index = 0;
		int i;
		for(i = 0; i< 56; i++){
			int bit_to_get = pc1[i];
			cout<<input.get_bit(bit_to_get);
			if(input.get_bit(bit_to_get)){
				output.set_bit(i+1);
			}
			else{
				output.reset_bit(i+1);
			}

		}
		cout<<endl;
		// cout<<"new key is"<<endl;
		output.print_binary();
	}

	void circularshift(){
		//circular left shifts the cd array(done after each round in DES)
		charset key(cd, 8);
		cout<<"circularshift"<<endl;
		key.print_binary();
		int first_bit = key.get_bit(1);
		for(int i = 0; i<55; i++){
			if(key.get_bit(i+2)){
				key.set_bit(i+1);
			}
			else{
				key.reset_bit(i+1);
			}

		}
		if (first_bit){
			key.set_bit(56);
		}
		else{
			key.reset_bit(56);
		}
		key.print_binary();
		cout<<"--------------------"<<endl;
	}

	void permute2(){
		charset input(cd, 8);
		charset output(roundKey, 7);
		int index = 0;
		int i;
		for(i = 0; i< 48; i++){
			int bit_to_get = pc1[i];
			cout<<input.get_bit(bit_to_get);
			if(input.get_bit(bit_to_get)){
				output.set_bit(i+1);
			}
			else{
				output.reset_bit(i+1);
			}

		}
		cout<<endl;
		// cout<<"new key is"<<endl;
		output.print_binary();
	}



};



int main(){
	
	int initial_key_permutaion[56] = {57, 49,  41, 33,  25,  17,  9,
								 1, 58,  50, 42,  34,  26, 18,
								10,  2,  59, 51,  43,  35, 27,
								19, 11,   3, 60,  52,  44, 36,
								63, 55,  47, 39,  31,  23, 15,
								 7, 62,  54, 46,  38,  30, 22,
								14,  6,  61, 53,  45,  37, 29,
								21, 13,   5, 28,  20,  12,  4};

	int sub_key_permutation[48] =    {14, 17, 11, 24,  1,  5,
								 3, 28, 15,  6, 21, 10,
								23, 19, 12,  4, 26,  8,
								16,  7, 27, 20, 13,  2,
								41, 52, 31, 37, 47, 55,
								30, 40, 51, 45, 33, 48,
								44, 49, 39, 56, 34, 53,
								46, 42, 50, 36, 29, 32};		

	int key_shift_sizes[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

	char key[9] = "abcdefgh";

	keyset k(key, initial_key_permutaion, sub_key_permutation, key_shift_sizes);
	k.permute1();
	// k.circularshift();
	// k.circularshift();
	// k.circularshift();
	// k.circularshift();
	// k.circularshift();
	// k.circularshift();
	// k.circularshift();
	// k.circularshift();
	// k.circularshift();
	// k.permute2();

	// charset c(key, 9);
	// c.print_binary();
	// c.set_bit(4);
	// c.set_bit(5);
	// c.set_bit(6);
	// c.set_bit(7);
	// c.reset_bit(8);
	// c.reset_bit(11);
	// c.reset_bit(10);

	// for(int i = 1; i<= 64; i++){
	// 	cout<<c.get_bit(i);
	// 	if(i%8==0)
	// 		cout<<",";
	// }
	// cout<<endl;
}
