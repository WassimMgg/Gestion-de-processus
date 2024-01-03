#include "Gestion_Des_Processus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>


//? cree un arbre avec n noued format binaire
void creeroot()
{
    root = malloc(sizeof(elementArbre));
    root->PID = 0;
    root->Etat = 0;
    printf("Initialiser la taille de ram de cette processus : ");
    scanf("%d", &root->RAM);
    root->Fils = NULL;
    root->Frere = NULL;
}
void creeNoued()
    {
        TarbreProcessus nouveauNoeud = malloc(sizeof(elementArbre));
        if (nouveauNoeud == NULL)
        {
            printf("Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        nouveauNoeud->PID = PID;
        PID++; 
        nouveauNoeud->Etat = 1;
        printf("Entrez le nom de cette processus : "); 
        getchar();
        gets(nouveauNoeud->Nom); 
        printf("Initialiser la taille de ram de cette processus : ");
        scanf("%d", &nouveauNoeud->RAM);
        ram = ram - nouveauNoeud; 
        if(ram < 0)
            printf("n'est pas espace memoire"); 
        nouveauNoeud->Fils = NULL;
        nouveauNoeud->Frere = NULL;
        return nouveauNoeud;
    }


   void LancerRoot()
    {
        root->Etat = 1;
        Elu = InsererFin(root, root->PID);
    }

    TListeProcessus InsererFin(TListeProcessus l, int PID)
    {
        TListeProcessus temp;
        if (l == NULL)
        {
            l = malloc(sizeof(elementProcessus));
            l->Suivant = NULL;
            l->PID = PID;
        }
        else
        {
            while (l->Suivant != NULL)
            {
                l = l->Suivant;
            }
            temp = malloc(sizeof(elementProcessus));
            l->Suivant = temp;
            temp->PID = PID;
            temp->Suivant = NULL;
        }
    }

    void Preordre(TarbreProcessus root)
{
    if(root != NULL)
    {
        printf("%d ",root->PID);
        Preordre(root->Fils);
        Preordre(root->Frere);
    }
}