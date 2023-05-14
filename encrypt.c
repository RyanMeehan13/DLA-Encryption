/*
 *DLA Encryption Function
 *Ryan Meehan 
 *
 */

#include <gmp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
   
   int n = 2048; //prime will be 2048 bits
   
   mpz_t p;   
   mpz_t m;
   mpz_t generator;
   mpz_t f;
   mpz_t g;
   mpz_t h;
   mpz_t a;
   mpz_t b;
   mpz_t r;
   mpz_t s;

   mpz_t p_sub_1; //p-1
   mpz_t one;
   long uno = 1;
   mpz_init(one);
   mpz_set_si(one, uno);


   mpz_t f_exp_r;
   mpz_t g_exp_s;
   mpz_t h_exp_r_plus_s;
   mpz_t h_exp_r_plus_s_m;
   //need a few gmp rand states. 
   //Need to figure out what they correspond to 
   gmp_randstate_t gen_state;

   mpz_init(m);
   printf("Enter the value for m: \n");
   gmp_scanf("%Zd", m);
   
   //perform inits 
   mpz_inits(generator, f, g, h, NULL);
   mpz_inits(a,b,r,s,NULL);
   mpz_inits(f_exp_r, g_exp_s, h_exp_r_plus_s, h_exp_r_plus_s_m, NULL);
  

   //pick prime p:


   //determine generator 
   srand(time(0));
   int seed = rand();
   gmp_randseed_ui(gen_state, seed);
   mpz_urandomm(generator, gen_state, p_sub_one);



   return 0;
}
