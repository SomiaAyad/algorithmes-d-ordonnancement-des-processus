#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct processus{
int id;
int arrivee;
double priority;
double duree;
double ta;
double tr;
int termine;

}processus;

typedef struct resultats{
    char nom[50];
    double tm_attente;
    double tm_rotation;
    double debit;
} resultats;


void saisie(int N,processus *p){ int i;
for(i=0;i<N;i++){
        p[i].id=i;
    printf("\nentrer la duree dexecution du PR%d:",p[i].id);
    scanf("%lf",&p[i].duree);
    printf("entrer la priorite du PR%d:",p[i].id);
    scanf("%lf",&p[i].priority);
}
}

void t_arrivee(int N , processus *p){
    clock_t debut =clock(); // debut est le temps quand la fct a commencé
    int i=0;
    p[0].arrivee=0;
    p[0].id=0;
while(getchar()!='\n'); // sert bien à vider le buffer d'entrée
for(i=1;i<N;i++){
    p[i].id=i;
    printf("appuyez sur entrer pour generer l'arrivee du processus PR%d\n",p[i].id);
    getchar();//attend que l'utilisateur appuie sur entrée
    // clock() mesure le temps écoulé depuis le debut du programme (en ticks)
    p[i].arrivee=(int)(clock()-debut)/CLOCKS_PER_SEC;//on divise par CLOCKS_PER_SEC pour obtenir le temps en secondes

}
 for(i=0;i<N;i++){
        printf("le temps d arrivee de PR%d est : %d\n",p[i].id,p[i].arrivee);
    }
}

int main()
{ int N,choix,i,j,termines,finis=0;
double t_observation;
processus temp;
printf("========== Simulation d ordonnancement des processus (OS)========== \n\n");
    printf("entrer le nombre des processus :");
    scanf("%d",&N);
    processus *p=malloc(N*sizeof(processus));
    if(p==NULL){
        printf("erreur d allocation");
        exit(1);
    }
    resultats t_resultats[6]; //tb pour stocker les resultats de chaque algo
    int nbr_algo=0;
t_arrivee(N,p);
saisie(N,p);
printf("\nentrer le temps d observation :");
scanf("%lf",&t_observation);
   do{
            printf("\nChoisissez l algorithme d ordonnancement que vous souhaitez executer :");
            printf("\n\n1:First Come First Served (FCFS)\n2:Shortest Job First (SJF)\n3:Shortest Remaining Time First (SRTF)\n4:ordonnancement par priorit prremptif\n5:ordonnancement par priorit non prremptif\n6:Round-Robin(RR)\n7:classer les algorithmes\n0:quitter le programme\n");
           scanf ("%d",&choix);
    switch(choix){

         case 1:  {
                   printf("------l algorithme FCFS(First Come First Served )------\n");
                   int time=0,termines=0;
                   double s_trotation=0,s_tattente=0;
                   //tri selon le temps d'arrivée (ordre croissant)
         for(i=0;i<N-1;i++){
            for (j=i+1;j<N;j++){
                if( p[j].arrivee<p[i].arrivee){
                    temp=p[j];
                    p[j]=p[i];
                    p[i]=temp;}
                   }}
                // Affichage de l’ordre d’exécution des processus
                   printf("\nl ordre d execution des processus :\n");
                   for(i=0;i<N;i++){
                    printf("P%d\t",p[i].id);
                   }
                // Affichage du diagramme de Gantt
                   printf("\n\n-----Diagramme de Gantt-----\n\n");
                   for(i=0;i<N;i++){
                    printf("| PR%d ",p[i].id);
                   }
                   //temps initial(0)
                   printf("\n0");
                   for(i=0;i<N;i++){
                        time+=p[i].duree;
                   printf("    %d",time);

                   //calculs des temps
                   p[i].tr=time-p[i].arrivee;//tepms de rotation
                   p[i].ta=p[i].tr-p[i].duree;//temps d'attente
                   s_trotation+=p[i].tr;
                   s_tattente+=p[i].ta;
                    // Calcul du débit (nombre de processus terminés dans le temps d’observation)
                   if(time<=t_observation){
                    termines++;
                   }
                  }
                   printf("\n");
                   for(i=0;i<N;i++){
                     printf("\nle temps de rotation de PR%d: %.2lf\n",i,p[i].tr);
                   printf("le temps d attente de PR%d: %.2lf\n",i,p[i].ta);
                   }
                   printf("\nle temps moyen de rotation: %.2lf",s_trotation/N);
                   printf("\nle temps moyen d attente: %.2lf\n\n",s_tattente/N);
                   printf("le debit : %.2lf",termines/t_observation);

                   strcpy(t_resultats[nbr_algo].nom,"FCFS");
                  t_resultats[nbr_algo].tm_attente = s_tattente / N;
                   t_resultats[nbr_algo].tm_rotation = s_trotation / N;
                   t_resultats[nbr_algo].debit = (double)termines / t_observation;
                   nbr_algo++;
                   break;
                  }

    case 2:   {
              printf("------l algorithme SJF (Shortest Job First)------\n");
               double s_trotation=0,s_tattente=0;
               int termines=0;
            for(i=0;i<N;i++){
           p[i].termine=0;// 0= pas encore exécuté
           }
           int finis=0; // nombre de processus terminés
           int time =0;
           // Affichage du diagramme de Gantt
           printf(" \n-----le diagramme de gantt-----\n\n");
           printf("0");

            while (finis<N){
            int idx=-1;
            int min_duree=1000000;
         // Recherche du processus prêt ayant la plus petite durée
            for(i=0;i<N;i++){
                if(p[i].termine==0&&p[i].arrivee<=time){
                    if(p[i].duree <min_duree){
                        min_duree=p[i].duree;
                        idx=i;
                    }
                }
            }

           if(idx!=-1){
            printf("| PR%d |",p[idx].id);
            time+=p[idx].duree;  // Avancer le temps selon la duree d'execution
             printf(" %d",time);

            p[idx].termine =1;   // termine = 1 signifie que ce processus a déjà été exécuté
             finis++;
                    //calculs des temps
                   p[idx].tr=time-p[idx].arrivee;
                   p[idx].ta=p[idx].tr-p[idx].duree;
                   s_trotation+=p[idx].tr;
                   s_tattente+=p[idx].ta;
                   if(time<=t_observation){
                    termines++;
                   }
                  }
            else{    //aucun processus n'est pret on incrémente le temps pour continuer la simulation
                    printf("| inactif");
                    time++;
                   printf(" %.2lf",time);
               }
              }
                 printf("\n");
                 for(i=0;i<N;i++){
                    printf("\n\nle temps de rotation de PR%d: %.2lf\n",p[i].id,p[i].tr);
                     printf("le temps d attente de PR%d: %.2lf\n",p[i].id,p[i].ta);
                 }
                   printf("\nle temps moyen de rotation: %.2lf",s_trotation/N);
                   printf("\nle temps moyen d attente: %.2lf\n",s_tattente/N);
                   printf("\nle debit : %.2lf\n",(double)termines/t_observation);

                   strcpy(t_resultats[nbr_algo].nom,"SJF");
                  t_resultats[nbr_algo].tm_attente = s_tattente / N;
                   t_resultats[nbr_algo].tm_rotation = s_trotation / N;
                   t_resultats[nbr_algo].debit = (double)termines / t_observation;
                   nbr_algo++;
                   break;
               }

    case 3:  {
                 printf("------Algorithme SRTF------\n");
                           int temps_restant[N];// un tab pour stocker le temps restant de chaque processus
                           int finis=0, time=0,termines=0;
                            double s_trotation=0,s_tattente=0;
                       for(i=0;i<N;i++){
                           temps_restant[i]=p[i].duree;
                        p[i].termine=0; //marque les processus comme non terminés
                     }
                     printf("\n------Diagramme de Gantt-----\n\n");
                     printf("0");
                     while(finis<N){

                        int idx=-1;  // index du processus sélectionné pour exécution
                        int min_temps_restant = 1000000 ;

                        //chercher le processus pret avec le plus petit temps restant >0
                        for(i=0;i<N;i ++){
                            if(p[i].arrivee<=time&&p[i].termine==0&&temps_restant[i]<min_temps_restant&&temps_restant[i]>0){
                               min_temps_restant=temps_restant[i];
                               idx=i;
                            }
                             }
                      if(idx!=-1){
                     //executer ce processus pendant 1 unite de temps
                        printf(" | PR%d",p[idx].id);
                        temps_restant[idx]--;
                        time++;
                        printf(" %d",time);

                        // si le processus est executee
                        if(temps_restant[idx]==0){
                            p[idx].termine=1;
                            finis++;
                            // calculs temps de rotation et attente
                           p[idx].tr = time-p[idx].arrivee;
                           p[idx].ta = p[idx].tr-p[idx].duree;
                           s_trotation += p[idx].tr;
                           s_tattente += p[idx].ta;
                            if(time<=t_observation){
                             termines++;
                              }

                        }
                      } else {
                          //si aucun processus pret
                          printf("| inactif");
                          time++;

                        printf(" %d\n",time);}}
                         for(i=0;i<N;i++){
                    printf("\n\nle temps de rotation de PR%d: %.2lf\n",p[i].id,p[i].tr);
                     printf("le temps d attente de PR%d: %.2lf\n",p[i].id,p[i].ta);
                 }
                   printf("\nle temps moyen de rotation: %.2lf",s_trotation/N);
                   printf("\nle temps moyen d attente: %.2lf\n",s_tattente/N);
                   printf("\nle debit : %.2lf\n",(double)termines/t_observation);

                   strcpy(t_resultats[nbr_algo].nom,"SRTF");
                   t_resultats[nbr_algo].tm_attente = s_tattente / N;
                   t_resultats[nbr_algo].tm_rotation = s_trotation / N;
                   t_resultats[nbr_algo].debit = (double)termines / t_observation;
                   nbr_algo++;

                   break;
                }

           case 4: {
                    printf("------l algorithme priority preemptif------\n");
                       int temps_restant[N];
                       int finis=0,time=0,termines=0;
                        double s_trotation=0,s_tattente=0;

                      for(i=0;i<N;i++){
                        temps_restant[i]=p[i].duree;
                        p[i].termine=0;//marque les processus comme non terminés
                      }
                        printf("\n-----Diagramme de Gantt-----\n\n");
                        printf("0");

                      while(finis<N){
                            int idx=-1;
                            int max_priority = 100000;
                            //chercher le processus pret avec la priorite la plus eleve (valeur la plus basse)
                            for(i=0;i<N;i++){
                        if(p[i].arrivee<=time&&temps_restant[i]>0&&p[i].priority<max_priority&&p[i].termine==0){
                            max_priority=p[i].priority;
                            idx=i ;
                        }}
                        if(idx!=-1){
                        // Exécution du processus sélectionné pendant 1 unité de temps
                            printf(" | PR%d",p[idx].id);
                            temps_restant[idx]--;
                            time++;
                            printf(" %d",time);
                            if(temps_restant[idx]==0){
                                    p[idx].termine=1;
                              finis++;
                              // calculs temps de rotation et attente
                              p[idx].tr=time-p[idx].arrivee;
                              p[idx].ta=p[idx].tr-p[idx].duree;
                              s_trotation+=p[idx].tr;
                               s_tattente+=p[idx].ta;
                                if(time<=t_observation){
                                 termines++;
                                }
                            }
                            }else{
                                //si aucun processus pret
                                printf(" | inactif");
                                time++;
                            printf(" %d",time);}
                      } for(i=0;i<N;i++){
                    printf("\n\nle temps de rotation de PR%d: %.2lf\n",p[i].id,p[i].tr);
                     printf("le temps d attente de PR%d: %.2lf\n",p[i].id,p[i].ta);
                 }
                   printf("\nle temps moyen de rotation: %.2lf",(s_trotation/N));
                   printf("\nle temps moyen d attente: %.2lf\n",(s_tattente/N));
                   printf("\nle debit : %.2lf\n",(double)termines/t_observation);

                   strcpy(t_resultats[nbr_algo].nom,"priority preemptif");
                   t_resultats[nbr_algo].tm_attente = s_tattente / N;
                   t_resultats[nbr_algo].tm_rotation = s_trotation / N;
                   t_resultats[nbr_algo].debit = (double)termines / t_observation;
                   nbr_algo++;
                   break;
           }

      case 5: { printf("------l algorithme priorite non preemptif------\n");
                int finis=0,time=0,termines=0;
                double s_trotation=0,s_tattente=0;
                for(i=0;i<N;i++){
                  p[i].termine=0;
                }
                //affichage du diagramme
                printf("\n-----Diagramme de Gantt-----\n\n");
                printf("0");
                while(finis<N){
                        int idx=-1;
                        int max_priority=1000000;
                        // chercher le processus prêt avec la plus haute priorité(val la plus basse)
                        for(i=0;i<N;i++){
                    if(p[i].arrivee<=time&&p[i].termine==0){
                       if(p[i].priority<max_priority){
                        max_priority=p[i].priority;
                        idx=i;
                       }
                    }
                }
                  if(idx!=-1){
                     // exécuter le processus jusqu'à la fin
                     printf(" | PR%d",p[idx].id);
                     time+=p[idx].duree;
                     printf(" %d",time);
                     p[idx].termine=1;
                     finis++;
                     // calculs temps de rotation et attente
                     p[idx].tr=time-p[idx].arrivee; //temps de rotation
                     p[idx].ta=p[idx].tr-p[idx].duree;//temps d'attente
                     s_trotation+=p[idx].tr;
                     s_tattente+=p[idx].ta;
                     if(time<=t_observation){
                        termines++;
                     }
                  }else{
                      //si aucun processus pret
                  printf(" | inactif");
                  time++;
                  printf(" %d",time);
                  }
                }
                for(i = 0; i < N; i++){
                    printf("\n\nle temps de rotation de PR%d: %.2lf", p[i].id, p[i].tr);
                    printf("\nle temps d attente de PR%d:%.2lf\n", p[i].id, p[i].ta);}

                   printf("\nle temps moyen de rotation: %.2lf",s_trotation/N);
                   printf("\nle temps moyen d attente: %.2lf\n",s_tattente/N);
                  printf("\nle debit : %.2lf\n", (double)termines / t_observation);

                  strcpy(t_resultats[nbr_algo].nom,"priority non preemptif");
                   t_resultats[nbr_algo].tm_attente = s_tattente / N;
                   t_resultats[nbr_algo].tm_rotation = s_trotation / N;
                   t_resultats[nbr_algo].debit = (double)termines / t_observation;
                   nbr_algo++;
                   break;}
        case 6:{
                         printf("\n------Algorithme RR (Round Robin)------\n");
                            int time = 0,finis = 0,quantum,termines=0;
                             double s_trotation=0,s_tattente=0;

                         printf("Entrez le quantum : ");
                        scanf("%d", &quantum);
                         int temps_restant[N];
                    // Initialisation
                     for(i = 0; i < N; i++){
                     temps_restant[i] = p[i].duree;
                      p[i].termine = 0;}
                      printf("\n-----Diagramme de Gantt-----\n\n");
                      printf("0");

                     while(finis < N){
                      int execute= 0;  // pour savoir si quelqu’un a été exécuté
                     for(i = 0; i < N; i++){
                         if(p[i].arrivee <= time && temps_restant[i] > 0){
                            execute = 1;
                 printf(" | PR%d", p[i].id);
                   if(temps_restant[i]>quantum){
                       temps_restant[i] -= quantum;
                        time += quantum;
                  }else{
                       time += temps_restant[i];
                        temps_restant[i] = 0;
                        p[i].termine = 1;
                        finis++;

                      // calculs
                       p[i].tr=time-p[i].arrivee;
                       p[i].ta=p[i].tr-p[i].duree;
                       s_trotation+=p[i].tr;
                       s_tattente+=p[i].ta;

                       if(time<=t_observation){
                       termines++;
                                }
                            }
                        printf(" %d",time);}}

                        // Si aucun processus n’est pret
                        if(execute == 0){
                        printf(" | inactif");
                       time++;
                       printf(" %d", time);}}

                       for(i = 0; i < N; i++){
                      printf("\n\n temps de rotation de PR%d:%.2lf", p[i].id, p[i].tr);
                      printf("\nle temps d attente de PR%d: %.2lf\n", p[i].id, p[i].ta);}

                      printf("\nle temps moyen de rotation: %.2lf", s_trotation / N);
                      printf("\nle temps moyen d attente: %.2lf\n", s_tattente / N);
                      printf("\nle debit : %.2lf\n", (double)termines / t_observation);

                      strcpy(t_resultats[nbr_algo].nom,"RR");
                    t_resultats[nbr_algo].tm_attente = s_tattente / N;
                   t_resultats[nbr_algo].tm_rotation = s_trotation / N;
                   t_resultats[nbr_algo].debit = (double)termines / t_observation;
                   nbr_algo++;
                   break;}
        case 7:
               //Classement selon le temps moyen d’attente (croissant)

               for(int i=0;i<nbr_algo-1;i++){
                for(int j=i+1;j<nbr_algo;j++){
                    if(t_resultats[j].tm_attente<t_resultats[i].tm_attente){
                      resultats tmp=t_resultats[i];
                      t_resultats[i]=t_resultats[j];
                      t_resultats[j]=tmp;
                    }
                }
               }

            printf("\n------Classement des algorithmes (selon le temps moyen d attente)------\n");
               for(int i = 0; i < nbr_algo; i++){
            printf("%d) %s : %.2lf\n",i+1,t_resultats[i].nom,t_resultats[i].tm_attente);
                 }

                 //Classement selon le temps moyen de rotation(croissant)

               for(int i=0;i<nbr_algo-1;i++){
                for(int j=i+1;j<nbr_algo;j++){
                    if(t_resultats[j].tm_rotation<t_resultats[i].tm_rotation){
                      resultats tmp=t_resultats[i];
                      t_resultats[i]=t_resultats[j];
                      t_resultats[j]=tmp;
                    }
                }
               }

            printf("\n------Classement des algorithmes (selon le temps moyen de rotation)------\n");
               for(int i = 0; i < nbr_algo; i++){
             printf("%d) %s : %.2lf\n",i+1,t_resultats[i].nom,t_resultats[i].tm_rotation);
                 }

                 //Classement selon le debit(decroissant)

               for(int i=0;i<nbr_algo-1;i++){
                for(int j=i+1;j<nbr_algo;j++){
                    if(t_resultats[i].debit<t_resultats[j].debit){
                      resultats tmp=t_resultats[i];
                      t_resultats[i]=t_resultats[j];
                      t_resultats[j]=tmp;
                    }
                }
               }

            printf("\n------Classement des algorithmes (selon le debit)------\n");
               for(int i=0;i<nbr_algo;i++){
             printf("%d) %s : %.2lf\n",i+1,t_resultats[i].nom,t_resultats[i].debit);
                 }
                 break;

            case 0: printf("fin du programme");
                    break;
            default:
                    printf("Choix invalide\n");
    }
   }while(choix!=0);
   free(p);

    return 0;
}
