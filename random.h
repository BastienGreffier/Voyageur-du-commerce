// generateur de nombres aleatoires avec deux valeurs de seed, "graines"

#define max_rand 2147483647l

/*
unsigned long const_valeur_1=217828199l;
unsigned long const_valeur_2=314159269l;
unsigned long seed_valeur_1=111111l;
unsigned long seed_valeur_2=1111111l;
*/
long const_valeur_1=217828199l;
long const_valeur_2=314159269l;
long seed_valeur_1=111111l;
long seed_valeur_2=1111111l;

void reset_random(void){
  seed_valeur_1=111111l;
  seed_valeur_2=1111111l;
}

void nouveau_seed(void){
    printf("seed_1,  seed_2 ?  ");
    scanf("%u%u",&seed_valeur_1,&seed_valeur_2);
    printf("seed_1 = %12u ,  seed_2 = %12u\n",seed_valeur_1,seed_valeur_2);
}

long rand_int(void){
  long x;
  x=(const_valeur_1*seed_valeur_2-const_valeur_2*seed_valeur_1)%max_rand;
  seed_valeur_1=seed_valeur_2;
  seed_valeur_2=x;
  if(x<0) x+=max_rand;
  return x;
}


// produit un nombre aleatoire x tel que: 0 <= x < 1

double rand_double(void){
  long a;

  a=rand_int();
  return (double)a/(double)max_rand;
}

