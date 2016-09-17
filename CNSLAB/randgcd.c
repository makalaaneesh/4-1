#include<stdio.h>
#include<gmp.h>

int main(){
	mpz_t r0,r1,q;
	mpz_init(r0);
	mpz_init(r1);
	mpz_init(q);
	gmp_scanf("%Zd",r0);
	gmp_scanf("%Zd",r1);
	mpz_abs(r0,r0);
	mpz_abs(r1,r1);
	mpz_t zero;
	mpz_init(zero);
	mpz_set_ui(zero,0);
	if(mpz_cmp(r0,r1)<0){
		mpz_t t;
		mpz_init(t);
		mpz_set(t,r1);
		mpz_set(r1,r0);
		mpz_set(r0,t);
	}


	while(mpz_cmp(r1,zero)!=0){
		mpz_fdiv_q(q,r0,r1);
		mpz_t temp;
		mpz_init(temp);
		mpz_set(temp,r0);
		mpz_set(r0,r1);
		mpz_submul(temp,q,r1);
		mpz_set(r1,temp);
	}
	gmp_printf("GCD is : %Zd\n",r0);
}

