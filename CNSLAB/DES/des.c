#include <iostream>
#include <stdio.h>
#include <bitset>
#include <string.h>
#include <vector>
#include <math.h>

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
	
	int pc1[56]; // 7*8
	int pc2[48]; // 8*6
	int leftshifts[16];

public:
	char roundKey[7];
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



class Algorithm{
	keyset *key_obj;
	char * input_text;
	char * cipher_text;
	int IP[64];
	int IP_INV[64];
	int EXPANSION[48];
	int PERMUTATION[32];
	int S1[64];
	int S2[64];
	int S3[64];
	int S4[64];
	int S5[64];
	int S6[64];
	int S7[64];
	int S8[64];
	int S[8][64];
	char left[5];
	char right[5];
public:
	Algorithm(char * input, keyset *k, int ip[64], int ip_inv[64], int expansion[48], int permutation[32], int s[8][64]){
		//int s1[64], int s2[64], int s3[64], int s4[64], int s5[64], int s6[64], int s7[64], int s8[64]
		input_text = input;
		key_obj = k;
		memcpy(IP,ip, 64 * sizeof(int));
		memcpy(IP_INV, ip_inv, 64 * sizeof(int));
		memcpy(EXPANSION, expansion, 48 * sizeof(int));
		memcpy(PERMUTATION, permutation, 32 * sizeof(int));
		int i;
		for(i = 0; i<8; i++)
		{
		    memcpy(S[i], s[i], 64 * sizeof(int));
		}
		cout<<S[0][1]<<endl;
		// memcpy(S1, s1, 64 * sizeof(int));
		// memcpy(S2, s2, 64 * sizeof(int));
		// memcpy(S3, s3, 64 * sizeof(int));
		// memcpy(S4, s4, 64 * sizeof(int));
		// memcpy(S5, s5, 64 * sizeof(int));
		// memcpy(S6, s6, 64 * sizeof(int));
		// memcpy(S7, s7, 64 * sizeof(int));
		// memcpy(S8, s8, 64 * sizeof(int));


	}

	void init(){
		key_obj->permute1();
		// vector<int> test;
		// test.push_back(1);
		// test.push_back(0);
		// test.push_back(1);
		// cout<<binary_to_int(test)<<endl;

	}

	int binary_to_int(vector<int> &a){
		int power = a.size() -1;
		int value = 0;
		for(int i = 0; i<a.size(); i++){
			value = value + (a[i]* (int)(pow(2,power)));
			power--;
		}
		return value;
	}

	vector<int> int_to_binary(int a){
		vector<int> result;

		while(a){
			int r = a % 2;
			result.insert(result.begin(),r);
			a = a/2;
		}
		int filler = 4 - result.size();
		for(int i = 0; i< filler; i++){
			result.insert(result.begin(), 0);
		}
		return result;
	}

	void round(int number){
		int i;

		
		cout<<"ROUND "<<number<<"____________________________________"<<endl;
		cout<<"\033[1;32m";

		//expansion
		charset rightset(right, 5);
		charset leftset(left, 5);
		cout<<"LEFT -";
		leftset.print_binary();
		cout<<"RIGHT-";
		rightset.print_binary();


		char expanded[7];
		charset expanded_set(expanded, 7);

		for(i = 0; i< 48; i++){
			int bit_to_get = EXPANSION[i];

			if(rightset.get_bit(bit_to_get)){
				expanded_set.set_bit(i+1);
			}
			else{
				expanded_set.reset_bit(i+1);
			}
		}


		cout<<"EXPANDED"<<endl;
		expanded_set.print_binary();

		// get the key ready
		key_obj->circularshift();
		key_obj->permute2();


		



		// xor the key and the expanded key
		char xored[7];

		for(i = 0; i< 6; i++){
			xored[i] = expanded[i] ^ key_obj->roundKey[i];
		}
		charset xoredset(xored, 7);

		cout<<"XORED"<<endl;
		xoredset.print_binary();





		// substitution
		vector<int> num;
		vector<int> substituted_vec;
		char subbed[5];
		charset subbedset(subbed, 5);
		for(i = 0; i< 48; i++){
			// cout<<i<<endl;
			num.push_back(xoredset.get_bit(i+1));
			if((i+1) % 6 == 0){
				vector<int> row(num.begin(), num.begin()+2);
				vector<int> col(num.begin()+2, num.end());
				// cout<<row.size()<<"xx"<<col.size()<<endl;
				int rownum = binary_to_int(row);
				int colnum = binary_to_int(col);
				// cout<<rownum<<"xx"<<colnum<<"--";
				int value = S[number][rownum*16 + colnum];
				// cout<<value<<endl;
				vector<int> valuebin = int_to_binary(value);
				for(int j = 0; j< valuebin.size(); j++){
					// cout<<valuebin[j]<<",";
					substituted_vec.push_back(valuebin[j]);
				}
				// cout<<endl;
				num.clear();
			}
		}
		// cout<<substituted_vec.size()<<endl;
		for(i = 0; i< 32; i++){
			if(substituted_vec[i]){
				subbedset.set_bit(i+1);
			}
			else{
				subbedset.reset_bit(i+1);
			}
		}
		cout<<"SUBSTITUTED"<<endl;
		subbedset.print_binary();




		//permutation
		char permuted[5];
		charset permutedset(permuted, 5);

		for(i = 0; i< 32; i++){
			int bit_to_get = PERMUTATION[i];

			if(subbedset.get_bit(bit_to_get)){
				permutedset.set_bit(i+1);
			}
			else{
				permutedset.reset_bit(i+1);
			}
		}

		cout<<"PERMUTATION"<<endl;
		permutedset.print_binary();


		char newright[5];
		for(i = 0; i< 5; i++){
			newright[i] = left[i] ^ permuted[i];
		}

		memcpy(left, right, sizeof(char)*5);
		memcpy(right, newright, sizeof(char)*5);


		cout<<"NEWLEFT -";
		leftset.print_binary();
		cout<<"NEWRIGHT-";
		rightset.print_binary();

		cout<<"\033[0m\n";
		cout<<"____________________________________________"<<endl;

	}

	void encrypt(){
		//input has to be 64 bits. hence 8 characters. (1 extra for \0)
		
		int index = 0;
		int i;
		for(i = 0; i<4; i++){
			left[index++] = input_text[i];
		}
		left[index] = '\0';
		index = 0;
		for(i = 4; i<8;i++){
			right[index++] = input_text[i];
		}
		right[index] = '\0';

		for(i = 0; i< 16; i++){
			round(i);		
		}



		cout<<left<<right;



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


	/////////////////////////////////////////////

	int initial_message_permutation[] =	   {58, 50, 42, 34, 26, 18, 10, 2,
										60, 52, 44, 36, 28, 20, 12, 4,
										62, 54, 46, 38, 30, 22, 14, 6,
										64, 56, 48, 40, 32, 24, 16, 8,
										57, 49, 41, 33, 25, 17,  9, 1,
										59, 51, 43, 35, 27, 19, 11, 3,
										61, 53, 45, 37, 29, 21, 13, 5,
										63, 55, 47, 39, 31, 23, 15, 7};


	int final_message_permutation[] =  {40,  8, 48, 16, 56, 24, 64, 32,
									39,  7, 47, 15, 55, 23, 63, 31,
									38,  6, 46, 14, 54, 22, 62, 30,
									37,  5, 45, 13, 53, 21, 61, 29,
									36,  4, 44, 12, 52, 20, 60, 28,
									35,  3, 43, 11, 51, 19, 59, 27,
									34,  2, 42, 10, 50, 18, 58, 26,
									33,  1, 41,  9, 49, 17, 57, 25};

	int right_sub_message_permutation[] =    {16,  7, 20, 21,
									29, 12, 28, 17,
									 1, 15, 23, 26,
									 5, 18, 31, 10,
									 2,  8, 24, 14,
									32, 27,  3,  9,
									19, 13, 30,  6,
									22, 11,  4, 25};

	int message_expansion[] =  {32,  1,  2,  3,  4,  5,
							 4,  5,  6,  7,  8,  9,
							 8,  9, 10, 11, 12, 13,
							12, 13, 14, 15, 16, 17,
							16, 17, 18, 19, 20, 21,
							20, 21, 22, 23, 24, 25,
							24, 25, 26, 27, 28, 29,
							28, 29, 30, 31, 32,  1};

int S[8][64] ={ {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
			 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
			 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
			15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},

{15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
			 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
			 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
			13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},

{10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
			13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
			13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
			 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},

{ 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
			13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
			10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
			 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},

{ 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
			14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
			 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
			11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},

{12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
			10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
			 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
			 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},


 { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
			13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
			 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
			 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},

{13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
			 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
			 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
			 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11} };

	char key[9] = "abcdefgh";

	keyset k(key, initial_key_permutaion, sub_key_permutation, key_shift_sizes);

	char input[9] = "sreerag!";
	Algorithm algo(input, &k, initial_message_permutation, final_message_permutation, message_expansion, right_sub_message_permutation, S);

	algo.init();
	algo.encrypt();

	// k.permute1();
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
