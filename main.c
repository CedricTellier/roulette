#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fMiseJoueur(int nbJetons){
    int miseJoueur = 0;
    printf("Veuillez miser!\nLa mise minimale est 1 et la mise maximale est de 25\nMise: ",nbJetons);
    scanf("%d",&miseJoueur);
    return miseJoueur;
}

int fChoixJoueur(){
    int choixJoueur = 0;
    printf("Quel est votre choix ?\n0: Pair\n1: Impair\nChoix: ");
    scanf("%d",&choixJoueur);
    return choixJoueur;
}

int tourJeu(int nbJetons){
    int choixJoueur = 0;
    int miseJoueur = 0;
    int nbHasard = rand()%37;

    //Demander sa mise au joueur
    printf("Vous disposez de %d jetons!\n", nbJetons);
    miseJoueur = fMiseJoueur(nbJetons);

    //Vérification si la mise est entre 1 et 25 et que le joueur ne mise pas plus qu'il n'a
    while ((miseJoueur>25) || (miseJoueur<1)||(miseJoueur>nbJetons)){
        miseJoueur = fMiseJoueur(nbJetons);
    }

    //Demander son choix au joueur
    choixJoueur = fChoixJoueur();
    //Vérification si le choix du joueur est entre 0 et 1 (impair ou pair)
    while ((choixJoueur!=0) && (choixJoueur!=1)){
        choixJoueur = fChoixJoueur();
    }

    //Résolution du tour de jeu
    printf("\nLa roulette sort %d\n", nbHasard);
    //if (((choixJoueur==0) && (nbHasard%2==0)) || ((choixJoueur==1) && (nbHasard%2==1))) {
    if (choixJoueur == nbHasard%2){
        //Le joueur pari pair ou impair et gagne!
        printf("Vous avez gagne!\n");
        return miseJoueur;
    }
    else{
        //Le joueur perd
        printf("Vous avez perdu!\n");
        return miseJoueur*-1;
    }
}
// Résolution d'un tir
int tourTir (int barillet, int tir){
    printf("\nTentative de tir numero %d\n",tir);
    if (tir==barillet){
        // le joueur tire et se tue
        printf("le joueur est mort! Perdu!\n");
        return 0;
    }
    else{
        // le joueur tire et reste en vie
        printf("Le joueur s'en sort et remporte 20 jetons\n");
        return 20;
        tir++;
    }
}

int jeuRouletteRusse(){
    int nbJetonsGagnesTotal = 0;
    int nbJetonsGagnes = 0;
    int barillet = rand()%6+1; // lancement aléatoire du barillet
    int jeContinue = 1;
    int tir =1;

    while (jeContinue){
        nbJetonsGagnes = tourTir(barillet,tir);


        if (nbJetonsGagnes){
            //gagné des jetons = ajouté au total
            nbJetonsGagnesTotal = nbJetonsGagnesTotal + nbJetonsGagnes;

            //DemandernbJetonsGagnes = tourTir(barillet, tir);
            if (nbJetonsGagnes){
                //gagné des jetons = ajouté au total
                nbJetonsGagnesTotal = nbJetonsGagnesTotal + nbJetonsGagnes;
            }
            else{
                //pas gagné de jeton = mort
                nbJetonsGagnesTotal = 0;
            }

            //Si le joueur veut continuer
            printf("Voulez-vous retenter votre chance a la roulette russe?\n0. Non\n1. Oui\n");
            scanf("%d", &jeContinue);
            tir++;
        }
        else{
            //pas gagné de jeton = mort
            nbJetonsGagnesTotal = 0;
            jeContinue = 0;
        }
    }
    return nbJetonsGagnesTotal;
}

int main(){
    int nbJetons = 10;
    int lifeJoueur = 1;


    //Initialiser le random
    srand(time(NULL));

    // Tant que le joueur n'a pas remboursé ses dettes et qu'il dispose de jetons

    while ((nbJetons<100)&&(lifeJoueur!=0)){
        while ((nbJetons<100)&&(nbJetons!=0)){
        nbJetons = nbJetons + tourJeu(nbJetons);
        }
        //Cas du joueur sans Jetons
        if (nbJetons==0){
            printf("Bienvenue dans la roulette russe!\n ATTENTION, vous jouez avec votre vie!\n");

            // Le joueur a une vie mais pas de jeton donc jeu roulette russe
            if (lifeJoueur == 1){
                nbJetons = jeuRouletteRusse();

                //Jetons renvoyé à 0 donc la personne est morte
                if (nbJetons == 0){
                    lifeJoueur = 0;
                }
            }
        }
        //Cas rare du joueur qui gagne!
        if ((nbJetons>=100)&&(lifeJoueur==1)){
            printf("Vous avez remboursé toutes vos dettes et vous êtes toujours en vie. Profitez en!");
        }
    }
    return printf("Fin de Jeu");
}
