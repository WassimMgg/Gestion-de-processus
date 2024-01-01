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

int main()
{
    int Ram;
    printf("Svp Initialiser la taille de la ram : ");
    scanf("%d",&Ram);
    root = CreerRoot(root);
    root = LancerRoot(root); 
    AjouterFils(root,root->PID,root->Nom,root->RAM,root->Etat); 

    
    return 0;
}