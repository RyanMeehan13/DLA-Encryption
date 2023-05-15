#include <gmp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define A "10849"
#define B "20223"
#define P "42131"

int main() 
{
   //declarations
   mpz_t c1;
   mpz_t c2;
   mpz_t c3;
   mpz_t a;
   mpz_t b;

   mpz_t p;

   mpz_t c1_exp_a;
   mpz_t c2_exp_b;
   mpz_t denom; //c1^a*c2^b
   
   mpz_t res;
   //inits
   mpz_inits(c1,c2,c3,a,b,p, c1_exp_a, c2_exp_b, res, denom, NULL);
   mpz_set_str(a, A, 10);
   mpz_set_str(b, B, 10);
   mpz_set_str(p, P, 10);


   printf("Enter c1, c2, c3: \n");
   gmp_scanf("%Zd, %Zd, %Zd", c1, c2, c3);


   //c1^a
   mpz_powm(c1_exp_a, c1, a, p);

   mpz_powm(c2_exp_b, c2, b, p); //c2^b

   mpz_mul(denom, c1_exp_a, c2_exp_b);
   mpz_mod(denom, denom, p);
   
  // gmp_printf("denom is %Zd\n",denom);
   mpz_divexact(res, c3, denom);
   mpz_mod(res,res,p);
   gmp_printf("m: %Zd\n", res);


   mpz_clears(c1,c2,c3,a,b,p,c1_exp_a, c2_exp_b, res, denom,NULL);

   return 0;
}
