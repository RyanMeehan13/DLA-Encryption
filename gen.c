
#include <gmp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define two_E_2047 "32768 "

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
  
   //perform inits 
   mpz_inits(generator, f, g, h, NULL);
   mpz_inits(a,b,r,s,NULL);
   mpz_inits(f_exp_r, g_exp_s, h_exp_r_plus_s, h_exp_r_plus_s_m, NULL);
   gmp_randinit_mt(gen_state); 
   mpz_init(p_sub_1);

   //pick prime p:
   gmp_randstate_t num_state;
   gmp_randinit_mt(num_state);
   srand(time(0));
   int num_seed = rand();
   gmp_randseed_ui(num_state, num_seed);
   mpz_t intermediate_n;
   mpz_init(intermediate_n);
   mpz_urandomb(intermediate_n, num_state, 14); //generate {0, 2^2047}
   mpz_t const_two_e2047;
   mpz_init(const_two_e2047);
   mpz_set_str(const_two_e2047, two_E_2047, 10); //var = 2^2047
   mpz_t random_n;
   mpz_init(random_n);
   mpz_add(random_n, intermediate_n, const_two_e2047); //{2^2047, 2^2048} = 2^2047+{0, 2^2047}
   mpz_nextprime(p, random_n); //sets p to next prime greater than 2048 bit random number

   printf("prime generated. It is: \n");
   gmp_printf("%Zd \n",p);

   //determine generator
   mpz_sub(p_sub_1, p, one); 
   srand(time(0));
   int seed = rand();
   gmp_randseed_ui(gen_state, seed);
   mpz_urandomm(generator, gen_state, p_sub_1);
   bool good = false;
   mpz_t gen_exp_frac;
   mpz_init(gen_exp_frac);

   mpz_t p_sub_1_div_2;
   mpz_init(p_sub_1_div_2);
   mpz_divexact_ui(p_sub_1_div_2,p_sub_1, 2); // calc (p-1)/2
   printf("About to loop and create generator...\n");
   while(!good) 
   {
      srand(time(0));
      int seed = rand();
      gmp_randseed_ui(gen_state, seed);
      mpz_urandomm(generator, gen_state, p_sub_1);

      mpz_powm(gen_exp_frac, generator, p_sub_1_div_2, p); //(generator)^((p-1)/2) mod p
      if( (mpz_cmp_si(gen_exp_frac, 1)==0) || (mpz_cmp_si(gen_exp_frac, -1)==0)) {
         good = true;
      }
   }
   gmp_printf("Generator created: %Zd. Sampling...\n", generator);
    //sample f , g , h 
   seed = rand();
   gmp_randseed_ui(gen_state, seed);    
   mpz_t r_f;
   mpz_init(r_f);
   mpz_urandomm(r_f, gen_state, p_sub_1);
   mpz_add(r_f, r_f, one);
   mpz_powm(f, generator, r_f, p);

   seed = rand();
   gmp_randseed_ui(gen_state, seed);
   mpz_t r_g;
   mpz_init(r_g);
   mpz_urandomm(r_g, gen_state, p_sub_1);
   mpz_add(r_g, r_g, one);
   mpz_powm(g, generator, r_g, p);

   seed = rand();
   gmp_randseed_ui(gen_state, seed);
   mpz_t r_h;
   mpz_init(r_h);
   mpz_urandomm(r_h, gen_state, p_sub_1);
   mpz_add(r_h, r_h, one);
   mpz_powm(h, generator, r_h, p);

   gmp_printf("Sampling finished,f=%Zd,  g=%Zd, h=%Zd\n",f,g,h);  

//find a 
   mpz_t tryF;
   mpz_init(tryF);
   mpz_set(tryF,f);
   mpz_t count;
   mpz_init(count);
   mpz_set_ui(count, 1);
   printf("going into loop for a\n");
   while((mpz_cmp(tryF,h)!=0))
   {
      mpz_add_ui(count,count,1);
      mpz_mul(tryF, tryF, f);
      mpz_mod(tryF, tryF, p);
   }
   mpz_set(a, count);
   mpz_set_ui(count, 1);
//find b
   mpz_t tryG;
   mpz_init(tryG);
   mpz_set(tryG, g);
   printf("going into loop for b\n");
   while( (mpz_cmp(tryG, h)!=0))
   {
      mpz_add_ui(count,count,1);
      mpz_mul(tryG, tryG, g);
      mpz_mod(tryG, tryG, p);
   }
   mpz_set(b, count);
   gmp_printf("a,b = %Zd, %Zd\n", a,b);
 
  mpz_clears(m ,generator,f,g,h,NULL);
  mpz_clears(a,b,NULL);
  mpz_clears(p_sub_1, one, intermediate_n, const_two_e2047, random_n, gen_exp_frac,tryG, tryF, count, NULL);
  gmp_randclear(gen_state);
  gmp_randclear(num_state);





return 0;
}
