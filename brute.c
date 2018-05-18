# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <time.h>

int i,j,p,tmp,a,n;

FILE *fp;

int Affiche(int *LL)
{
    int i;
    for (i = 0 ; i < n ; i++)
        fprintf(fp,"%d ",LL[i]);
            
    fprintf(fp,"\n");
}

void permut(int *v, int n)      /* Création d'un programme de permutation  -----> Algorithme de Heap */
 {
    int i;
    int t;
    if (n == 0){
        Affiche(v);           /* Affichage resultat dans le fichier */
    }
    else {
        for (i = 0; i < n; i++){
            permut(v, n-1);
            if (n % 2 == 1){
                t=v[0];
                v[0] = v[n-1];
                v[n-1]=t;
            }
            else{
                t=v[i];
                v[i]=v[n-1];
                v[n-1]=t;
            }
        }
    }
}

int main(){
    
    fp=fopen("ultra_brute.dat","w");
    
    printf ("Combien il y a t'-il de villes à visiter ?\n");
    scanf ("%d", &n); // on demande d'entrer le nombre de villes
    
    
    for(i=0;i<n-1;i++){
         if(i==0){
             a=1;
         }
         else{
             a += a*i;
         }
    }
    
    printf("a = %d\n",a); // a représente le nombre de trajet possible
    
    double (*v)[2],*d,dmin;
    int *t,(*all_perm)[n+1];
    
    v=malloc((n+1)*sizeof(*v));
    d=malloc(a*sizeof(double));
    t=malloc(n*sizeof(int));
    all_perm=malloc(a*sizeof(*all_perm));
    
    for(i=0;i<a;i++){
        for(j=0;j<n+1;j++){
            all_perm[i][j]=0;  // ce tableau stockera l'ensemble des trajets possibles
        }
    }
    
  //  srand(time(NULL)); // cette ligne permet de générer des nombres aléatoires différents à chaque fois qu'on lance le programme
    
    for (i=0;i<n;i++){
        v[i][0]=rand()/(double)RAND_MAX;    // initialisation des coordonnées x
        v[i][1]=rand()/(double)RAND_MAX;    // initialisation des coordonnées y
        t[i]=i;                             // trajet de base (sans compter la ville d'arriver)
    }
    
    v[n][0]=v[0][0];    // on fixe les coordonnées de la dernière ville comme étant celle de la première
    v[n][1]=v[0][1];
    
    
    permut(t,n-1);  // on crée l'ensemble des trajets possibles grâce à l'algorithme de Heap  
    fclose(fp);
    
    FILE *fp1=NULL;
    fp1=fopen("ultra_brute.dat","r");
    
    if(fp1!=NULL){
        for(i=0;i<a;i++){
            for(j=1;j<n+1;j++){
                fscanf(fp1,"%d",&all_perm[i][j]); // on stocke tout les trajets des le tableau all_perm
            }
        }
    }
    else{
        printf("Erreur\n");
    }
    
    for(i=0;i<a;i++){
        all_perm[i][0]=0;   // on fixe la ville de départ de tout les trajets comme étant la ville 0
    }
    
    for(i=0;i<a;i++){       // l'algorithme de Heap fait toutes les permutations en fixant la ville d'arriver, or nous on veut que la ville de départ soit celle d'arriver donc on permute la dernière ville avec la ville 0 ainsi la ville 0 est la dernière ville visitée
        for(j=1;j<n+1;j++){
            if(all_perm[i][j]==0){
                tmp=all_perm[i][j];
                all_perm[i][j]=all_perm[i][n];
                all_perm[i][n]=tmp;
            }
        }
    }
    
    for(i=0;i<a;i++){   // ce tableau stockera toutes les distances des différents trajets
        d[i]=0;
    }
    
    for(i=0;i<a;i++){      // on calcule toutes les distances
        for(j=0;j<n;j++){
            d[i]+= sqrt((v[all_perm[i][j]][0]-v[all_perm[i][j+1]][0])*(v[all_perm[i][j]][0]-v[all_perm[i][j+1]][0])+(v[all_perm[i][j]][1]-v[all_perm[i][j+1]][1])*(v[all_perm[i][j]][1]-v[all_perm[i][j+1]][1]));
        }
    }
    
    dmin=1000;
    
    for(i=0;i<a;i++){   // on prend la distance minimale
        if(d[i]<dmin){
            dmin=d[i];
            p=i;    // p indique à quelle ligne du tableau all_perm se situe le trajet le plus court
        }
    }
    
    FILE *fp2;
    fp2=fopen("Dmin.dat","w");
    
    for(i=0;i<n+1;i++){
        fprintf(fp2,"%lf\t%lf\n",v[all_perm[p][i]][0],v[all_perm[p][i]][1]);
    }
    
    printf("dmin: %lf\n",dmin);
    
    free(d);
    free(t);
    free(all_perm);
    free(v);

}