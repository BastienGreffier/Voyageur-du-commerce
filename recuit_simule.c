# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <time.h>
#include <unistd.h>
#define f 0.999; // f est le facteur de refroidissement de la température
      
      
int main(){
    
    int n, i, j, h, k, l, tmp;
    
    double theta,old_d,new_d,d,a,u,x,y;
    
    printf ("Combien il y a t'-il de villes à visiter ?\n");
    scanf ("%d", &n); // on demande d'entrer le nombre de villes
    
    
  
//  Allocation dynamique des tableaux      
    
    double (*v)[2];
    int *t,*newt;
    
    v=malloc((n+1)*sizeof(*v));
    t=malloc((n+1)*sizeof(int));
    newt=malloc((n+1)*sizeof(int));
  
  


    FILE *fp;
    FILE *fp1;
    
    fp=fopen("recuit_simule.dat","w");
    fp1=fopen("trajet.dat","w");
    
    srand(time(NULL)); // initialisation de rand, grâce à ça à chaque fois que le programme est relancé la fonction rand renvoie d'autres nombres aléatoires
    
    
    
    for (i=0;i<n;i++){
        v[i][0]=rand()/(double)RAND_MAX; // initialisation des coordonnées x des villes
        v[i][1]=rand()/(double)RAND_MAX; // initialisation des coordonnées y des villes
        t[i]=i;
        newt[i]=i;
        //printf("t: %lf\n",t[i]);
    }
    
    v[n][0]=v[0][0];
    v[n][1]=v[0][1];
    t[n]=t[0];
    newt[n]=newt[0];
    
    
    // Début du recuit_simule
    
    theta = 3/log(10./9); // température initiale du système
    
    while (theta>0.0001){
        for(j=0;j<100*n;j++){
            
            k=rand()%(n-1)+1;  // on génère des nombres aléatoire compris entre 1 et n-1
            l=rand()%(n-1)+1;
            
          //  x=rand()%(100-10)+10; // on génère des nombres aléatoire compris entre 100 et 10
          //  y=rand()%(100-10)+10;
            
          //  printf("k%d\tl%d\n",k,l);
          //  sleep(1);
            
            old_d=0;
            new_d=0;
            
            if(k!=l){
            
                if(k<l){                                // On fait une permutation cyclique des villes dans l'intervalle [k;l]
                    for(u=0;u<(l-k)/(double)2;u++){
                        tmp=newt[(int)(l-u)];
                        newt[(int)(l-u)]=newt[(int)(k+u)];
                        newt[(int)(k+u)]=tmp;
                    }
                }
                else{                                  // On fait une permutation cyclique des villes dans l'intervalle [k;l]
                    for(u=0;u<(k-l)/(double)2;u++){
                        tmp=newt[(int)(k-u)];
                        newt[(int)(k-u)]=newt[(int)(l+u)];
                        newt[(int)(l+u)]=tmp;
                    }
                }
                    
             /*   for(i=0;i<=n;i++){
                    printf("t:%d\tnewt:%d\n",t[i],newt[i]);
                    sleep(1);
                }*/
             
                
                // Calcul des distances //
                
                for(i=0;i<n;i++){
                    old_d += sqrt((v[t[i]][0]-v[t[i+1]][0])*(v[t[i]][0]-v[t[i+1]][0])+(v[t[i]][1]-v[t[i+1]][1])*(v[t[i]][1]-v[t[i+1]][1]));
                
                    new_d += sqrt((v[newt[i]][0]-v[newt[i+1]][0])*(v[newt[i]][0]-v[newt[i+1]][0])+(v[newt[i]][1]-v[newt[i+1]][1])*(v[newt[i]][1]-v[newt[i+1]][1]));
                //  printf("old_d: %lf\tnew_d: %lf\n",old_d,new_d);
               // sleep(1);
                    // printf("j: %d\th: %d\n",j,h);
                    }
                    
                   // old_d=old_d+theta*log(x); // On ajoute aux distances calculés un variable aléatoire suivant une distribution logarithmique
                    
                  //  new_d=new_d-theta*log(y);
            
                    a=rand()/(double)RAND_MAX;
                    if(new_d<old_d){
                        for(i=0;i<=n;i++){
                            t[i]=newt[i];
                //  printf("t: %d\tnewt: %d\n",t[i],newt[i]);
                //  sleep(1);
                    }
                }
                else{
                    if (a<exp(-(new_d-old_d)/theta)){
                        for(i=0;i<=n;i++){
                        t[i]=newt[i];
                    //  printf("t2: %d\n",t[i]);
                            }
                        }
                    }
            
              // printf("old_d: %lf\tnew_d: %lf\ttheta: %lf\n",old_d,new_d,theta);
              // sleep(1);
            }
        }
        
        theta = theta *f;
        fprintf(fp,"%lf %lf %lf\n",old_d,new_d,theta);
    }
    
    // Fin du recuit_simule
    
    
    printf("old_d: %lf\tnew_d: %lf\ttheta: %lf\n",old_d,new_d,theta);
    
   /* for(i=0;i<n;i++){
        printf("t: %d\tvx: %lf\tvy: %lf\tvmx: %lf\tvmy: %lf\n",t[i],v[i][0],v[i][1],v[t[i]][0],v[t[i]][1]);
    } */
    
    for(i=0;i<n+1;i++){
      //  printf("vx: %lf\tvy: %lf\n",v[t[i]][0],v[t[i]][1]);
        fprintf(fp1,"%lf\t%lf\n",v[t[i]][0],v[t[i]][1]);
    }
    
    fclose(fp);
    fclose(fp1);
    
    free(v);
    free(t);
    free(newt);
}