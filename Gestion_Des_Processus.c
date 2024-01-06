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
    printf("Initialiser la taille de ram de la processus root (PID = 0) : ");
    scanf("%d", &root->RAM);
    while (ram - root->RAM < 0)
    {
        printf("Espace dans la Ram insufisant refaire la saisie : ");
        scanf("%d", &root->RAM);
    }
    ram = ram - root->RAM;
    root->Fils = NULL;
    root->Frere = NULL;
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
    TarbreProcessus nouveauNoeud = malloc(sizeof(elementArbre));
    printf("Entrez le nom de cette processus : ");
    fflush(stdin);
    //? Use fgets to avoid buffer overflow
    fgets(nouveauNoeud->Nom, sizeof(nouveauNoeud->Nom), stdin);
    //? Remove newline character from the end
    nouveauNoeud->Nom[strcspn(nouveauNoeud->Nom, "\n")] = '\0';
    if (ram == 0)
    {
        printf("Espace dans la Ram insufisant ajoute impossible !!\n");
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
    nouveauNoeud->RAM = nevram;
    InsererNoeud(nouveauNoeud, temp->PID);
    nouveauNoeud->PID = compteur;
    compteur++;
    nouveauNoeud->Etat = 0;
    nouveauNoeud->Fils = NULL;
    nouveauNoeud->Frere = NULL;
    Pret = InsererFin(&Pret, nouveauNoeud->PID);
}
void Lancer()
{
}

void Tuer()
{
}

void Terminer()
{
}

void Bloquer()
{
}

void Debloquer()
{
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
            temp = recherchepere(root->Fils);
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

TListeProcessus InsererFin(TListeProcessus *l, int P)
{
    TListeProcessus temp;
    TListeProcessus par;
    if (*l == NULL)
    {
        *l = malloc(sizeof(elementProcessus));
        (*l)->PID = P;
        (*l)->Suivant = NULL;
    }
    else
    {
        par = *l;
        while (par->Suivant != NULL)
        {
            par = par->Suivant;
        }
        temp = malloc(sizeof(elementProcessus));
        par->Suivant = temp;
        temp->PID = P;
        temp->Suivant = NULL;
    }
    return *l;
}

void Htop(TarbreProcessus r)
{
    if (r != NULL)
    {
        TarbreProcessus pere = recherchepere(r);
        printf("-----------------------------------\n");
        printf("Le nom de cette processus est : ");
        for (int i = 0; r->Nom[i] != '\0'; i++)
        {
            putchar(r->Nom[i]);
        }
        printf("\n");
        printf("PID = %d \n", r->PID);
        printf("L'etat de cette processus : %d\n", r->Etat);
        printf("La ram de cette processus : %d\n", r->RAM);
        printf("Le PID de pere est :%d\n", pere->PID);
        printf("-----------------------------------\n");
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

TarbreProcessus recherchepere(TarbreProcessus l)
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
    return pere;
}

TListeProcessus rechercheliste(TListeProcessus l)
{
    TListeProcessus par = l;
    int pid;
    printf("\nEntrer le PID de pere SVP : \n");
    scanf("%d", &pid);
    while (par != NULL)
    {
        if (par->PID == pid)
        {
            printf("\nPID trouvee\n\n");
            return par;
        }

        par = par->Suivant;
    }
    printf("\nPID n'existe pas\n");
    return NULL;
}
