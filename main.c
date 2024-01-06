#include "Gestion_Des_Processus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

int main()
{
    int tr, p;
    char y[20];
    TarbreProcessus temp;
    printf("Initialiser la taille de ram de cette programme : ");
    scanf("%d", &ram);
    creeroot();
    LancerRoot();
    while (1)
    {
        printf("\n-----------------------------------\n");
        printf("               Creer\n");
        printf("               Lancer\n");
        printf("               Tuer\n");
        printf("               Terminer\n");
        printf("               Htop\n");
        printf("               Bloquer \n");
        printf("               Debloquer \n");
        printf("               Quittez \n");
        printf("\n----------------------------------\n");
        printf("Entrez votre choix : ");
        fflush(stdin);
        //? Use fgets to avoid buffer overflow
        fgets(y, sizeof(y), stdin);
        //? Remove newline character from the end
        y[strcspn(y, "\n")] = '\0';
        if (strcmp(y, "Quitter") == 0)
            return 0;
        else if (strcmp(y, "Creer") == 0)
        {
            printf("La processus numero %d\n", compteur);
            Creer();
        }

        else if (strcmp(y, "Lancer") == 0)
        {
            printf("Enterez le nom de processus : ");
            Lancer();
        }

        else if (strcmp(y, "Bloquer") == 0)
        {
            printf("Enterez le nom de processus : ");
            Bloquer();
        }

        else if (strcmp(y, "Debloquer") == 0)
        {
            printf("Enterez le nom de processus : ");
            Debloquer();
        }
        else if (strcmp(y, "Tuer") == 0)
        {
            printf("Enterez le nom de processus : ");
            Tuer();
        }
        else if (strcmp(y, "Terminer") == 0)
        {
            printf("Enterez le nom de processus : ");
            Terminer();
        }
        else if (strcmp(y, "Htop") == 0)
        {
            printf("PID de root = %d \n", root->PID);
            printf("L'etat de processus root : %d\n", root->Etat);
            printf("La ram de processus root : %d\n", root->RAM);
            printf("----------------------------------\n");
            Htop(root->Fils);
        }
        else
            printf("Le nom de l'operation incorrect refaire la saisir SVP!!\n");
    }
}
