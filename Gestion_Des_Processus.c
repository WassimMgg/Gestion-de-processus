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
    while (ram - root->RAM < 0)
    {
        printf("Espace dans la Ram insufisant refaire la saisie : ");
        scanf("%d", &root->RAM);
    }
    ram = ram - root->RAM;
    root->Fils = NULL;
    root->Frere = NULL;
    noued = root;
    Pret = InsererFin(&Pret, root->PID);
    compteur = 1;
}

void LancerRoot()
{
    root->Etat = 1;
    Elu = InsererFin(&Elu, root->PID);
    Pret = SuppDebut(&Pret);
}

void Creer()
{
    int nevram;
    if (ram == 0)
    {
        printf("Espace dans la Ram insufisant ajoute imposible !!\n");
        return;
    }
    printf("Saisir la taille de ram de cette processus : \n");
    scanf("%d", &nevram);
    while (ram - nevram < 0)
    {
        printf("Espace dans la Ram insufisant refaire la saisie : ");
        scanf("%d", &nevram);
    }
    TListeProcessus temp;
    do
    {
        temp = rechercheliste(Elu);
        if (temp == NULL)
        {
            printf("Le pere de cette processus n'est pas dans l'etat elu \n");
            printf("Les PID dans la liste elu est : "); 
            afficherListe(Elu);
        }
    } while (temp == NULL);
    ram = ram - nevram;
    TarbreProcessus nouveauNoeud = malloc(sizeof(elementArbre));
    nouveauNoeud->RAM = nevram;
    InsererNoeud(nouveauNoeud, temp->PID);
    nouveauNoeud->PID = compteur;
    compteur++;
    nouveauNoeud->Etat = 0;
    printf("Entrez le nom de cette processus : ");
    getchar();
    gets(nouveauNoeud->Nom);
    nouveauNoeud->Fils = NULL;
    nouveauNoeud->Frere = NULL;
    Pret = InsererFin(&Pret, nouveauNoeud->PID);
}
void InsererNoeud(TarbreProcessus l, int p)
{
    TarbreProcessus temp;
    if (root->Fils == NULL)
    {
        root->Fils = l;
        noued = root->Fils;
    }
    else
    {
        if (p == 0)
        {
            temp = noued;
            while (noued->Frere != NULL)
            {
                noued = noued->Frere;
            }
            noued->Frere = l;
            noued = temp;
        }
        else
        {
            temp = recherche(root->Fils, p);
            if (temp == NULL)
                printf("Cette PID n'existe pas \n");
            else
            {
                if (temp->Fils == NULL)
                {
                    temp->Fils = l;
                }
                else
                {
                    noued = temp;
                    while (noued->Frere != NULL)
                    {
                        noued = noued->Frere;
                    }
                    noued->Frere = l;
                    noued = temp;
                }
            }
        }
    }
}

TarbreProcessus recherche(TarbreProcessus r, int p)
{
    if (r == NULL)
        return NULL;
    else
    {
        if (p == r->PID)
        {
            return r;
        }
        else
        {
            return recherche(r->Fils, p);
            return recherche(r->Frere, p);
        }
    }
}

TListeProcessus InsererFin(TListeProcessus *l, int P)
{
    TListeProcessus temp;
    if (*l == NULL)
    {
        *l = malloc(sizeof(elementProcessus));
        (*l)->PID = P;
        (*l)->Suivant = NULL;
    }
    else
    {
        while ((*l)->Suivant != NULL)
        {
            *l = (*l)->Suivant;
        }
        temp = malloc(sizeof(elementProcessus));
        (*l)->Suivant = temp;
        temp->PID = P;
        temp->Suivant = NULL;
    }
    return *l;
}

void Htop(TarbreProcessus r)
{
    if (r != NULL)
    {
        TarbreProcessus pere = recherchpere(r);
        printf("Le nom de cette processus est : ");
        puts(r->Nom);
        printf("PID = %d \n", r->PID);
        printf("L'etat de cette processus : %d\n", r->Etat);
        printf("La ram de cette processus : %d\n", r->RAM);
        printf("Le PID de pere est :%d\n", pere->PID);
        Htop(r->Fils);
        Htop(r->Frere);
    }
}

void afficherListe(TListeProcessus l)
{
    if (l == NULL)
    {
        printf("La liste est vide\n");
    }
    else
    {
        while (l != NULL)
        {
            printf("%d ", l->PID);
            l = l->Suivant;
        }
    }
}

TListeProcessus SuppDebut(TListeProcessus *l)
{
    TListeProcessus temp;
    if (*l == NULL)
    {
        printf("La liste est empty\n");
    }
    else
    {
        temp = *l;
        *l = (*l)->Suivant;
        free(temp);
    }
    return *l;
}

TarbreProcessus recherchpere(TarbreProcessus l)
{
    TarbreProcessus pere = root, temp;
    while (pere != NULL)
    {
        if (pere->Fils->PID == l->PID)
            return pere;
        else
        {
            temp = pere->Fils;
            while (temp->Frere != NULL)
            {
                if (temp->Frere->PID == l->PID)
                    return pere;
                temp = temp->Frere;
            }
            pere = pere->Fils;
        }
    }
    printf("le pere n'est pas trouvee");
    return pere;
}

TListeProcessus rechercheliste(TListeProcessus l)
{
    TListeProcessus par = l;
    int pid;
    printf("Entrer le PID\n");
    scanf("%d", &pid);
    while (par != NULL)
    {
        if (par->PID == pid)
        {
            printf("PID trouvee\n\n");
            return par;
        }

        par = par->Suivant;
    }
    printf("PID n'existe pas\n");
    return NULL;
}
