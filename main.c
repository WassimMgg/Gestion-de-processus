#include "Gestion_Des_Processus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

int main()
{
    int x, i = 1, tr, p;
    TarbreProcessus temp; 
    printf("Initialiser la taille de ram : ");
    scanf("%d",&ram);
    creeroot();
    LancerRoot();
    while(1)
    {
    printf("-----------------------------------\n");
    printf("1- Creez un processus\n"); 
    printf("2-Lancez un processus\n"); 
    printf("3-Tuez un processus\n");
    printf("4-Terminez un processus\n");
    printf("5-Affichez un processus\n");
    printf("6-Affichez la liste Pret \n");
    printf("7-Affichez la liste Elu \n");
    printf("8-Affichez la liste Bloquer \n");
    printf("9-Rechercher un processus\n"); 
    printf("0- Quittez l'exuction\n"); 
    printf("Entrez votre choix : "); 
    scanf("%d",&x);
    printf("----------------------------------\n");
        switch (x)
        {
        case 0:
            return 0; 
            break;
        case 1: 
            printf("La processus numero %d\n",i); 
            i++; 
            Creer(); 
            break;
        case 5: 
            Htop(root); 
            break;
        case 6: 
            printf("Les elements dans l'etat Pret : \n"); 
            afficherListe(Pret); 
            break;
        case 7: 
            printf("Les elements dans l'etat Elu: \n"); 
            afficherListe(Elu);
            break; 
        case 8: 
            printf("Les elements dans l'etat Bloquer : \n"); 
            afficherListe(Bloquer);  
            break;
        case 9: 
            temp = recherchpere(root->Fils); 
            printf("PID = %d\n",temp->PID);
            break;
        default:
        printf("numero incorrect refaire la saisir SVP!!\n");
            break;
        }
    }
}
