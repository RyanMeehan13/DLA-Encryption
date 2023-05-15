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
   mpz_inits(generator, f, g, h, p, NULL);
   mpz_inits(a,b,r,s,NULL);
   mpz_inits(f_exp_r, g_exp_s, h_exp_r_plus_s, h_exp_r_plus_s_m, NULL);
   gmp_randinit_mt(gen_state); 
   mpz_init(p_sub_1);
  // printf("inits performed\n");
//cutoff
//gen generated values below:
   mpz_set_ui(p, 42131);
   mpz_set_ui(generator, 25732);
   mpz_set_ui(f,27745);
   mpz_set_ui(g,11019);
   mpz_set_ui(h,972);
   mpz_set_ui(a, 10849);
   mpz_set_ui(b,20223);
   mpz_sub_ui(p_sub_1, p,1);





   //generate r
   srand(time(0));
   int seed = rand();
   gmp_randseed_ui(gen_state, seed);
   mpz_t r_r;
   mpz_init(r_r);
   mpz_urandomm(r_r, gen_state, p_sub_1);
   mpz_add(r_r, r_r, one);
   mpz_powm(r, generator, r_r, p); //r = gen^{random} mod p
   //gmp_printf("r generated: %Zd\n", r);
   sleep(1);
   //generate s
  srand(time(0));
  seed = rand();
  gmp_randseed_ui(gen_state, seed);
  mpz_t r_s;
  mpz_init(r_s);
  mpz_urandomm(r_s, gen_state, p_sub_1);
  mpz_add(r_s, r_s, one); 
  mpz_powm(s, generator, r_s, p); //s = gen^{random] mod p
  //gmp_printf("s generated: %Zd\n", s);
  
  mpz_powm(f_exp_r, f, r, p); //f^r calculation
  mpz_powm(g_exp_s, g, s, p); //g^s calculation 
  mpz_t r_plus_s;
  mpz_init(r_plus_s);
  mpz_add(r_plus_s, r, s);
  //mpz_mod(r_plus_s, r_plus_s, p);
  //printf("simple calculations done. c1,c2 found.\n");

  mpz_powm(h_exp_r_plus_s,h, r_plus_s, p);
  mpz_mul(h_exp_r_plus_s_m, h_exp_r_plus_s, m); //m*h^{r+s}
  //mpz_mod(h_exp_r_plus_s_m, h_exp_r_plus_s_m, p);
  //printf("c3 found.\n");
  
  gmp_printf("%Zd,%Zd,%Zd\n", f_exp_r, g_exp_s, h_exp_r_plus_s_m);
  //mpz_powm(f,f,a,p);
  //gmp_printf("\n %Zd", f);

  //printf("\n about to clear...\n");
  mpz_clears(m ,generator,f,g,h,NULL);
  mpz_clears(a,b,r,s,f_exp_r,g_exp_s,h_exp_r_plus_s, h_exp_r_plus_s_m,NULL);
  mpz_clears(p_sub_1, one, r_r, r_s,NULL);
  gmp_randclear(gen_state);
 


   return 0;
}
