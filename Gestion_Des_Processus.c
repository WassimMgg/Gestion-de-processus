#include "Gestion_Des_Processus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

TListeProcessus Elu = NULL; 
TListeProcessus Pret = NULL; 
TListeProcessus Bloquer = NULL; 
TarbreProcessus root = NULL; 

void AjouterFils(TarbreProcessus root, int PID , char Nom[12] , int Ram , int Etat) {
    TarbreProcessus Fils = createNode(PID,Nom,Ram,Etat);
    if (root->Fils == NULL) 
    {
        root->Fils = Fils;
    } else {
        TarbreProcessus temp = root->Fils;
        while (temp->Frere != NULL) {
            temp = temp->Frere;
        }
        temp->Frere = Fils;
    }
}

TarbreProcessus createNode(int PID , char Nom[12] , int Ram , int Etat )
{
    TarbreProcessus newNode = malloc(sizeof(elementArbre));
    if (newNode == NULL) {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    newNode->PID = PID;
    newNode->Etat = Etat;
    newNode->Nom = Nom ; 
    newNode->RAM = Ram;
    newNode->Fils = NULL;
    newNode->Frere = NULL;
    return newNode;
}

void CreerRoot()
{
    root = malloc(sizeof(elementArbre)); 
    root->PID = 0; 
    root->Etat = 0; 
    printf("Initialiser la taille de ram de root: ");
    scanf("%d",&root->RAM); 
    root->Fils = NULL; 
    root->Frere = NULL;
}

void LancerRoot()
{
    root->Etat = 1;
    Elu = InsererFin(root,root->PID);  
    
}

TListeProcessus InsererFin(TListeProcessus l , int PID)
{
    TListeProcessus temp;
    if (l == NULL)
    {
        l = malloc(sizeof(elementProcessus)); 
        l->Suivant = NULL; 
        l->PID = PID; 
    }else{
        while(l->Suivant != NULL)
        {
            l = l->Suivant 
        }
            temp = malloc(sizeof(elementProcessus));
            l->Suivant = temp; 
            temp->PID = PID; 
            temp->Suivant = NULL;
    }
}
