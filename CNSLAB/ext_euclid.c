#include <stdio.h>
#include <gmp.h>

int main(){

	mpz_t zero,temp, temp1;
	mpz_init(zero);
	mpz_init(temp);
	mpz_init(temp1);
	mpz_set_ui(zero,0);

	mpz_t r1,r2,q1,q2,x1,x2,y1,y2;
	mpz_init(r1);
	mpz_init(r2);
	mpz_init(q1);
	mpz_init(q2);
	mpz_init(x1);
	mpz_init(x2);
	mpz_init(y1);
	mpz_init(y2);
	mpz_t a,b, r,q,x,y;
	mpz_init(a);
	mpz_init(b);
	mpz_init(r);
	mpz_init(q);
	mpz_init(x);
	mpz_init(y);
	gmp_scanf("%Zd",a);
	gmp_scanf("%Zd",b);
	gmp_printf("a - %Zd, b - %Zd\n",a,b);
	mpz_set(r1,a);
	mpz_set(r2,b);
	if(mpz_cmp(r1,r2)<0){
		gmp_printf("swapping\n");
		mpz_t t;
		mpz_init(t);
		mpz_set(t,r2);
		mpz_set(r2,r1);
		mpz_set(r1,t);
	}
	if(mpz_cmp(a,b)<0){
		gmp_printf("swapping\n");
		mpz_t t;
		mpz_init(t);
		mpz_set(t,b);
		mpz_set(b,a);
		mpz_set(a,t);
	}

	mpz_set_ui(x1,1);
	mpz_set_ui(x2,0);
	mpz_set_ui(y1,0);
	mpz_set_ui(y2,1);

	mpz_set_ui(r,1);

	while(mpz_cmp(r,zero) != 0){
		mpz_fdiv_q(q,r1,r2);
		mpz_fdiv_r(r,r1,r2);
		mpz_mul(temp, q, x2);
		mpz_sub(x, x1, temp);
		mpz_mul(temp, q, y2);
		mpz_sub(y, y1, temp);

		gmp_printf("r = %Zd, q = %Zd, x = %Zd, y = %Zd\n", r, q, x, y);
		mpz_set(x1, x2);
		mpz_set(y1, y2);
		mpz_set(q1, q2);
		mpz_set(r1, r2);
		mpz_set(x2, x);
		mpz_set(y2, y);
		mpz_set(q2, q);
		mpz_set(r2, r);
		

	}

	gmp_printf("a = %Zd, b = %Zd, x = %Zd, y = %Zd\n", a, b,x1, y1);





}
