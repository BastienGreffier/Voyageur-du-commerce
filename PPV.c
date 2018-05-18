# include <stdio.h>
# include <math.h>
//# include "random.h"
# include <stdlib.h>
# include <time.h>
#include <string.h>
int arrondi(float nombre) {         /* fonction permettant d'arondir un flottant et renvoie un entier */
    return nombre + 0.5;
}
int main(){
    
    
    /* Coordonnées des n villes */
    int n=1000;
    double *L,*M,(*S)[n];
    L=malloc(n*sizeof(double));
    M=malloc(n*sizeof(double));
    S=malloc(n*sizeof(*S));
    
   srand(time(NULL));
    
    for(int i=0;i<n;i++){
        L[i]=rand()/(double)RAND_MAX;
        M[i]=rand()/(double)RAND_MAX;
        //L[i]=rand_double();
        //M[i]=rand_double();
        
    }
    /* Construction du tableau des trajets */
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (i==j){
                S[i][j]=10000;
            }
            else {
                S[i][j]=sqrt((L[j]-L[i])*(L[j]-L[i])+(M[j]-M[i])*(M[j]-M[i]));
            }
           // printf("%lf\n",S[i][j]);
        }
    }
    
    int d;
    int C[n];
    int i=0;
    int k=0;
    double distance_totale=0;
    double distance_rand=0;
    double t;
    
    /* Selection du trajet le plus court */
    while (k<n){
        double a=1000;
        int j;
        for(j=0;j<n;j++){
            if(a > S[j][i]){
                d=j;
                a=S[j][i];
                /*printf("%lf",a);*/
               /* printf("%d\n",d);*/
                
                t=a;
                
            }
        }
        
        /* Condition pour que la distance_totale ne prenne pas la dernière valeur du tableau */
        
        distance_totale+=t;
        
        
        /* Remplace les distances entre les villes par des valeurs hautes ( pour pas que ça nous embète après )*/
        for (int l=0;l<n;l++){
            S[i][l]=10000;
            S[l][i]=10000;
            }
        
        i=d;
        C[k]=d;
        printf(" r=%lf\n",distance_totale);
        k+=1;
    }
      
    
    
    /* Trajet le plus court et ordre des villes */
    /*for (int m=0;m<n;m++){
       printf("Parcours de ville: %d\n",C[m]); 
        printf("ordre aléatoire : %d\n",C2[m]);
    }*/
    
    
   
       /* Initialisation du tableau tab de 1 à n*/
    int tab[n];int j;
    for (int l=0;l<n;l++){
        tab[l]=l+1;
    }
    double a;
    /* L'aléatoire est créé en échangeant aléatoirement deux éléments du tableau "tab" qui prend les valeurs 1 à n */
    for (int i=0;i<n;i++){
        j=arrondi(1+n*(rand()/(double)RAND_MAX));
        a=tab[i];
        tab[i]=tab[j];
        tab[j]=a;
    }
   tab[0]=0;
    
    for (j=0;j<n-1;j++){
        distance_rand+=sqrt((L[tab[j]]-L[tab[j+1]])*(L[tab[j]]-L[tab[j+1]])+(M[tab[j]]-M[tab[j+1]])*(M[tab[j]]-M[tab[j+1]])); 
    }
        
    t=sqrt((L[0]-L[d])*(L[0]-L[d])+(M[j]-M[d])*(M[j]-M[d]));
    distance_totale+=t;
    printf("Distance totale: %lf et %lf\n",distance_totale, distance_rand);

  
    
    FILE *fp;FILE *fp1;FILE *fp2;
    fp=fopen("trajectoire_orig","w");
     fp2=fopen("trajectoire_al","w");
    fp1=fopen("distance_orig","w");
    fprintf(fp1,"%lf %lf\n",distance_totale, distance_rand);
    
    fprintf(fp,"%lf %lf\n",L[0],M[0]);
    for (i=0;i<n;i++){
        fprintf(fp,"%lf %lf\n",L[C[i]],M[C[i]]);
        fprintf(fp2,"%lf %lf\n",L[tab[i]],M[tab[i]]);
    }
    fprintf(fp,"%lf %lf\n",L[0],M[0]);
    fprintf(fp2,"%lf %lf\n",L[0],M[0]);
    fclose(fp);
    fclose(fp1);
        
    
    free(L);
    free(M);
    free(S);
    /*free(N);*/
    
        
                
}
        
