#include<stdio.h>
#include<gmp.h>

#define SIZE 10

void _gcd(mpz_t a, mpz_t b,mpz_t result){

	mpz_t r0,r1;
	mpz_init(r0);
	mpz_init(r1);
	mpz_set(r0, a);
	mpz_set(r1, b);
	mpz_t zero, q;
	mpz_init(zero);
	mpz_init(q);
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
	mpz_set(result, r0);
}


void sub(mpz_t a, mpz_t b, mpz_t n)
{
	mpz_t r;
	mpz_init(r);
	mpz_sub(r, a, b);
	mpz_mod(r, r, n);
	gmp_printf("Subtratction modulo is = %Zd\n", r);
}

void add(mpz_t a, mpz_t b, mpz_t n)
{
	mpz_t r;
	mpz_init(r);
	mpz_add(r, a, b);
	mpz_mod(r, r, n);
	gmp_printf("Addition modulo is = %Zd\n", r);
}

void mul(mpz_t a, mpz_t b, mpz_t n)
{
	mpz_t r;
	mpz_init(r);
	mpz_mul(r, a, b);
	mpz_mod(r, r, n);
	gmp_printf("Multiplication modulo is = %Zd\n", r);
}




void extended_euclidean(mpz_t a, mpz_t b, mpz_t res){

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
	mpz_t  r,q,x,y;
	//mpz_init(a);
	//mpz_init(b);
	mpz_init(r);
	mpz_init(q);
	mpz_init(x);
	mpz_init(y);
	//gmp_scanf("%Zd",a);
	//gmp_scanf("%Zd",b);
	gmp_printf("a - %Zd, b - %Zd\n",a,b);
	mpz_set(r1,a);
	mpz_set(r2,b);
	if(mpz_cmp(r1,r2)<0){
		//gmp_printf("swapping\n");
		mpz_t t;
		mpz_init(t);
		mpz_set(t,r2);
		mpz_set(r2,r1);
		mpz_set(r1,t);
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

		//gmp_printf("r = %Zd, q = %Zd, x = %Zd, y = %Zd\n", r, q, x, y);
		mpz_set(x1, x2);
		mpz_set(y1, y2);
		mpz_set(q1, q2);
		mpz_set(r1, r2);
		mpz_set(x2, x);
		mpz_set(y2, y);
		mpz_set(q2, q);
		mpz_set(r2, r);
		

	}
	
	mpz_set(res, x1);


	if(mpz_cmp(a,b)<0){
		mpz_set(res, y1);
		//gmp_printf("swapping\n");
		mpz_t t;
		mpz_init(t);
		mpz_set(t,b);
		mpz_set(b,a);
		mpz_set(a,t);
	}
	gmp_printf("a = %Zd, b = %Zd, x = %Zd, y = %Zd\n", a, b,x1, y1);
	


}

void div(mpz_t a, mpz_t b, mpz_t n)
{
	mpz_t r;
	mpz_init(r);
	mpz_t t;
	mpz_init(t);
	
	_gcd(b,n,t);

	if (mpz_cmp_si(t, 1) != 0){
		printf("Modular division exists only for co-prime numbers.\n");
		return;
	}
	
	extended_euclidean(b, n, t);
	
	
	gmp_printf("a = %Zd, t = %Zd\n", a, t);
	mpz_mul(r, a, t);
	mpz_mod(r, r, n);
	gmp_printf("Division modulo is = %Zd\n", r);
}



int main(){
	mpz_t a,b,n;
	mpz_init(a);	
	mpz_init(b);
	mpz_init(n);
	gmp_scanf("%Zd", a);
	gmp_scanf("%Zd", b);
	gmp_scanf("%Zd", n);
	mpz_t res;
	mpz_init(res);
	gmp_printf("a,b,c = %Zd, %Zd, %Zd\n", a,b,n);
	//extended_euclidean( b, n,res);
	//gmp_printf("Gcd of %Zd, %Zd is %Zd\n", b, n, res);
	//gmp_printf("inverse is %Zd\n", res); 
	add(a,b,n);
	sub(a,b,n);
	mul(a,b,n);
	div(a,b,n);
	

}
