# include <stdio.h>
# include <math.h>
# include "random.h"
# include <stdlib.h>
# include <time.h>
#include <string.h>
int arrondi(float nombre) {
    return nombre + 0.5;
}
int main(){
    
    
    /* Coordonnées des n villes */
     int n=100;
     
    // printf ("Combien il y a t'-il de villes à visiter ?\n");
   // scanf ("%d", &n); // on demande d'entrer le nombre de villes
    
    double *L,*M,*N,(*S)[n];
    L=malloc((n)*sizeof(double));
    M=malloc((n)*sizeof(double));
    N=malloc((n)*sizeof(double));
    S=malloc((n)*sizeof(*S));
    
    srand(time(NULL));
    
    for(int i=0;i<n;i++){
        L[i]=rand()/(double)RAND_MAX;
        M[i]=rand()/(double)RAND_MAX;
        //L[i]=rand_double();
        //M[i]=rand_double();
        
    }
    /* Construction du tableau des trajets */
    for (int i=0;i<n;i++){
        N[i]=sqrt((L[0]-L[i])*(L[0]-L[i])+(M[0]-M[i])*(M[0]-M[i]));
        for (int j=0;j<n;j++){
            if (i==j){
                S[i][j]=10000;
            }
            else {
                S[i][j]=sqrt((L[j]-L[i])*(L[j]-L[i])+(M[j]-M[i])*(M[j]-M[i]));
            }
           
        }
    }
    N[0]=10000;
    
   
    int d,d1;
    int *C,*C1;
    
    C=malloc(n*sizeof(int));
    C1=malloc(n*sizeof(int));
    
    int i,i1=0,i2=0;
    int j;
    int k=0;
    int compteur=0,compteur1=0,compteur2=0;
    double distance_totale=0;
    double distance_rand=0;
    double t=100,t1=101;
    double a,a1;
    
    /* Selection du trajet le plus court */
    while (k<n){
    
        a=1000;
        a1=1000;
        int j;
        
    
    /* Boucle (1) */        
        for(j=0;j<n;j++){
            if(a > S[j][i1] && j!=i2){   /* Condition pour ne pas visiter la ville que la boucle (2) vient juste de traiter */ 
                d=j;
                a=S[j][i1];
                /*printf("%lf",a);*/
               /* printf("%d\n",d);*/
                if (a<50){
                    t=a;
                }
            }
        }
        
        a=1000;
        a1=1000;
        if  ( k>1 && compteur==0){  /* Boucle s'activant une seule fois, part du point d'arivé */ 
            
            for(j=0;j<n;j++){
                if(a1 > N[j] && j!=i1){
                    d1=j;
                    a1=N[j];
                /*printf("%lf",a);*/
               /* printf("%d\n",d);*/
                    if (a1<50){
                        t1=a1;
                    }
                }
            }
        
        //printf("d",compteur);
        }
        
        /* Boucle (2) */  
        if ( k>1 && compteur!=0){
        for(j=0;j<n;j++){
                if(a1 > S[j][i2] && j!=i1){  /* Condition pour ne pas visiter la ville que la boucle (1) vient juste de triater */ 
                    d1=j;
                    a1=S[j][i2];
                /*printf("%lf",a);*/
               /* printf("%d\n",d);*/
                    if (a1<50){
                        t1=a1;
                    }
                }
            }
        
        }
        
        if ( t<=t1){
                
         
    
            distance_totale+=t;
            
            
            
            
            
            /* Remplace les distances entre les villes par des valeurs hautes ( pour pas que ça nous embète après )*/
            for (int l=0;l<n;l++){
                S[i1][l]=10000;
                S[l][i1]=10000;
                }
            
            N[d]=10000;
            i1=d;
            C[compteur1]=d;
            compteur1+=1;
            
            
        }
        
        if (t>t1) {
            
            distance_totale+=t1;
            
            
            
            
            
            /* Remplace les distances entre les villes par des valeurs hautes ( pour pas que ça nous embète après )*/
            for (int l=0;l<n;l++){
                S[i2][l]=10000;
                S[l][i2]=10000;
                }
            compteur =1;
            compteur2+=1;
            i2=d1;
            C[n-compteur2]=d1;
        }
   // printf("%lf %lf\n ",t,t1);
    k+=1;
   // printf(" r=\n",distance_totale);
   // printf("%d  %d\n",i1,i2);
    //printf("%lf  %lf\n",t,t1);
    
    }
      
    
    
   
       /* Initialisation du tableau tab de 1 à n*/
    int *tab;
    
    tab=malloc(n*sizeof(int));
    
    for (int l=0;l<n;l++){
        tab[l]=l+1;
    }
    double b;
    /* L'aléatoire est créé en échangeant aléatoirement deux éléments du tableau "tab" qui prend les valeurs 1 à n */
    for (int i=1;i<n;i++){
        j=arrondi(n*rand_double()+1);
        b=tab[i];
        tab[i]=tab[j];
        tab[j]=b;
    }
    
   tab[0]=0;
    
    for (j=0;j<n-1;j++){
        distance_rand+=sqrt((L[tab[j]]-L[tab[j+1]])*(L[tab[j]]-L[tab[j+1]])+(M[tab[j]]-M[tab[j+1]])*(M[tab[j]]-M[tab[j+1]]));
    }
    distance_rand+=sqrt((L[tab[n-1]]-L[0])*(L[tab[n-1]]-L[0])+(M[tab[n-1]]-M[0])*(M[tab[n-1]]-M[0]));
        
        
    printf("Distance totale: %lf et %lf\n",distance_totale, distance_rand);

   
    
    /* Trajet le plus court et ordre des villes */
    
    printf("%d  %d  %d\n",compteur,compteur1, compteur2);
    FILE *fp;FILE *fp1;
    fp=fopen("trajectoire","w");
    fp1=fopen("distance","w");
    fprintf(fp1,"%lf %lf\n",distance_totale, distance_rand);
    
    
    int test=-1;
    fprintf(fp,"%lf %lf\n",L[0],M[0]);
    for (i=0;i<n;i++){
        if ( test != C[i] ){         /*Test pour vérifier à quelle position est la ville comptée deux fois */
        // printf("%d\n",C[i]);
            fprintf(fp,"%lf %lf\n",L[C[i]],M[C[i]]);
        }
        test=C[i];
    }
    fprintf(fp,"%lf %lf\n",L[0],M[0]);
    fclose(fp);
    fclose(fp1);
      
    /* Trajet le plus court et ordre des villes */
    /*for (int m=0;m<n;m++){
        printf("Parcours de ville: %d\n",C[m]); 
        printf("ordre aléatoire : %d\n",tab[m]);
    }*/
    
    free(L);
    free(M);
    free(S);
    free(N);
    free(C);
    free(C1);
    free(tab);
    
        
                
}
        
