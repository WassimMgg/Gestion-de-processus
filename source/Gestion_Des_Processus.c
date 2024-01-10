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
    root->PID = 0;  // initialiser le PID
    root->Etat = 0; // intialiser l'etat
    printf("Initialiser la taille de ram de la processus root (PID = 0) : ");
    scanf("%d", &root->RAM);    // insialiser la ram
    while (ram - root->RAM < 0) // verifier la ram
    {
        printf("Espace dans la Ram insufisant refaire la saisie : ");
        scanf("%d", &root->RAM);
    }
    ram = ram - root->RAM; // modifier la ram
    root->Fils = NULL;
    root->Frere = NULL;
    Pret = Inserer(&Pret, root->PID, root->Prio); // Inserer dans la liste pret
    compteur = 1;
}

void LancerRoot()
{
    root->Etat = 1;                                // modifier l'etat
    Elu = InsererFin(&Elu, root->PID, root->Prio); // Inserer dans la liste elu
    compteurelu = 1;                               // Intialiser le nombre de microprocesseur
    Pret = SuppDebut(&Pret);                       // Supperimer cette processus de l'état pret
}

void Creer()
{
    int nevram;
    TarbreProcessus y;
    TarbreProcessus nouveauNoeud = malloc(sizeof(elementArbre)); // reserver un espace memoire pour le noeud
    printf("Entrez le nom de cette processus : ");
    do
    {
        fflush(stdin);
        fgets(nouveauNoeud->Nom, sizeof(nouveauNoeud->Nom), stdin);
        nouveauNoeud->Nom[strcspn(nouveauNoeud->Nom, "\n")] = '\0';
        y = rechercheName(nouveauNoeud->Nom); // Verifier si le nom existe ou non
        if (y != NULL)
            printf("Le nom deja existe refaire la saisie : ");
    } while (y != NULL);
    if (ram == 0) // verifier la ram
    {
        printf("Espace dans la Ram insufisant ajoute impossible !!\n");
        return;
    }
    printf("Saisir la taille de ram de cette processus : \n");
    scanf("%d", &nevram);
    while (ram - nevram < 0) // Verifier l'espace memoire
    {
        printf("Espace dans la Ram insufisant refaire la saisie : ");
        scanf("%d", &nevram);
    }
    TListeProcessus temp;
    int PID;
    do
    {
        printf("\nEntrer le PID de pere SVP : \n");
        scanf("%d", &PID);
        temp = rechercheliste(Elu, PID); // Verifier le PID de pere est ce que dans L'etat elu ou non
        if (temp == NULL)                // le PID De Pere n'est pas dans l'état Elu
        {
            printf("Le pere de cette processus n'est pas dans l'etat elu \n");
            printf("Les PID dans la liste elu est : ");
            afficherListe(Elu); // Afficher la liste ELu
        }
    } while (temp == NULL);
    ram = ram - nevram;
    nouveauNoeud->RAM = nevram;   // insialiser la ram
    nouveauNoeud->PID = compteur; // insialiser le PID (comptuer pour assuerer le PID est unique)
    compteur++;                   // incrementer dans le compteur
    do
    {
        printf("\nEntrez la priorities de cette processus(entre 1 et 7): ");
        scanf("%d", &nouveauNoeud->Prio); // insialiser la priorité
        if ((nouveauNoeud->Prio > 7) || (nouveauNoeud->Prio < 1))
            printf("\nrefaire la saisir de priorities ");
    } while ((nouveauNoeud->Prio > 7) || (nouveauNoeud->Prio < 1)); // Verifier la priorité
    nouveauNoeud->Etat = 0;
    nouveauNoeud->Fils = NULL;
    nouveauNoeud->Frere = NULL;
    InsererNoeud(nouveauNoeud, PID);                              // Inserer le noeud dans l'arbre
    Pret = Inserer(&Pret, nouveauNoeud->PID, nouveauNoeud->Prio); // Inserer le processus dans l'état Pret
    ListeAffichage = InsererFin(&ListeAffichage, nouveauNoeud->PID, nouveauNoeud->Prio);
}

void Lancer()
{
    if (compteurelu >= 4) // Verifier le nombre de microprocesseur
    {
        printf("\nla liste Elu est complet, impossible de Lancer cette processus \n");
        return;
    }
    if (Pret == NULL) // Verifier la liste Pret
    {
        printf("\nLa liste Pret est vide ");
        return;
    }
    noued = recherche(Pret->PID);                  // rechercher dans l'arbre pour modifier l'etat de processus
    noued->Etat = 1;                               // Modifier l'état de processus
    Elu = InsererFin(&Elu, Pret->PID, Pret->Prio); // Inserer le processus dans la liste Elu
    compteurelu++;                                 // Incrementer le nombre de microprocesseur
    SuppDebut(&Pret);  
    printf("Le processus avec le PID %d a ete lancee\n",Elu->PID);                            // Supperimer cette processus de liste pret
}

void Tuer(TarbreProcessus l)
{
    TarbreProcessus temp = l;
    temp = recherchepere(l->PID);
    temp->Fils = l->Frere;
    SuppArbre(l->Fils);
    ram += l->RAM;
    ListeAffichage = Supp(&ListeAffichage, l->PID);
    switch (l->Etat)
    {
    case 0:
        Pret = Supp(&Pret, l->PID);
        break;
    case 1:
        Elu = Supp(&Elu, l->PID);
        break;
    case 2:
        ListeBloquer = Supp(&ListeBloquer, l->PID);
        break;
    }
    free(l);
}

void Terminer(TarbreProcessus l)
{
    if (l->Etat != 1)
    {
        printf("\nLa processus n'est pas en Etat Elu Teminer impossible !!");
        return;
    }
    Tuer(l);
}

void Bloquer()
{
    char Nom[12];
    TarbreProcessus temp;
    TListeProcessus prec;
    printf("Entrez le nom de cette processus : ");
    do
    {
        fflush(stdin);
        fgets(Nom, sizeof(Nom), stdin);
        Nom[strcspn(Nom, "\n")] = '\0';
        temp = rechercheName(Nom); // Rechercher par nom dans l'arbre de processus
        if (temp == NULL)
            printf("\nLe nom n'existe pas refaire la saisie : ");
    } while (temp == NULL);
    prec = rechercheliste(Elu, temp->PID); // rechercher dans la liste ELU
    if (prec == NULL)                      // Cette PID n'existe pas dans la liste ELu
    {
        printf("Le pere de cette processus n'est pas dans l'etat elu \n");
        printf("Les PID dans la liste elu est : ");
        afficherListe(Elu);
        return;
    }
    else
    {
        // cette PID existe dans l'état elu
        temp->Etat = 2;
        // Inserer le PID de Cette Processus dans la liste Bloquer
        ListeBloquer = InsererFin(&ListeBloquer, temp->PID, temp->Prio);
        // Supperimer le PID de cette processus dans la liste elu
        Elu = Supp(&Elu, temp->PID);
        compteurelu--; // desincrementer le nombre de microprocesseur
    }
}

void Debloquer()
{
    char Nom[12];
    TarbreProcessus temp;
    TListeProcessus prec;
    printf("Entrez le nom de cette processus : ");
    do
    {
        fflush(stdin);
        fgets(Nom, sizeof(Nom), stdin);
        Nom[strcspn(Nom, "\n")] = '\0';
        temp = rechercheName(Nom); // Rechercher par nom dans l'arbre de processus
        if (temp == NULL)
            printf("\nLe nom n'existe pas refaire la saisie : ");
    } while (temp == NULL);
    prec = rechercheliste(ListeBloquer, temp->PID); // rechercher dans la liste ELU
    if (prec == NULL)                               // Cette PID n'existe pas dans la liste ELu
    {
        printf("Le pere de cette processus n'est pas dans l'etat Bloquer \n");
        printf("Les PID dans la liste Bloquer est : ");
        afficherListe(ListeBloquer);
        return;
    }
    else
    {
        if (compteurelu >= 4) // Verifier le nombre de microprocesseur
        {
            printf("\nla liste Elu est complet, impossible de Lancer cette processus \n");
            return;
        }
        else
        {
            temp->Etat = 1;
            // Inserer le PID de Cette Processus dans la liste Elu
            Elu = InsererFin(&Elu, temp->PID, temp->Prio);
            // Supperimer le PID de cette processus dans la liste elu
            ListeBloquer = Supp(&ListeBloquer, temp->PID);
            compteurelu++; // desincrementer le nombre de microprocesseur
        }
    }
}

void InsererNoeud(TarbreProcessus l, int PID)
{
    TarbreProcessus parent_node = NULL;
    TarbreProcessus current_node = NULL;
    if (PID == 0)
    {
        parent_node = root; // si le pere est la racine
    }
    else
    {
        parent_node = recherche(PID); // rechercher le PID de pere et retourner l'adress de cette PID si il existe
        if (parent_node == NULL)      // Le Pid n'existe pas
        {
            printf("Cette PID n'existe pas \n");
            return; // Exit if parent not found
        }
    }
    if (parent_node->Fils == NULL) // si le fils est Null
    {
        parent_node->Fils = l; // inserer dans le fils
    }
    else // si le fils n'est pas NULL
    {
        current_node = parent_node->Fils;
        while (current_node->Frere != NULL)
        {
            current_node = current_node->Frere;
        }
        current_node->Frere = l; // inserer dans le frere
        l->Frere = NULL;
    }
}

TListeProcessus Inserer(TListeProcessus *l, int P, int prio)
{
    TListeProcessus new_node = malloc(sizeof(elementProcessus));
    if (new_node == NULL)
    {
        // Handle memory allocation failure
        return NULL;
    }
    new_node->PID = P;
    new_node->Prio = prio;
    new_node->Suivant = NULL;
    if (*l == NULL)
    {
        *l = new_node;
        return *l;
    }

    TListeProcessus prev_node = NULL;
    TListeProcessus current_node = *l;
    while (current_node != NULL && current_node->Prio <= prio)
    {
        prev_node = current_node;
        current_node = current_node->Suivant;
    }
    if (prev_node == NULL)
    {
        new_node->Suivant = *l;
        *l = new_node;
    }
    else
    {
        new_node->Suivant = prev_node->Suivant;
        prev_node->Suivant = new_node;
    }
    return *l;
}

TListeProcessus InsererFin(TListeProcessus *l, int P, int prio)
{
    TListeProcessus temp;
    TListeProcessus par;
    if (*l == NULL)
    {
        *l = malloc(sizeof(elementProcessus));
        (*l)->PID = P;
        (*l)->Prio = prio;
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
        temp->Suivant = NULL;
        par->Suivant = temp;
        temp->PID = P;
        temp->Prio = prio;
    }
    return *l;
}
void Htop()
{
    TListeProcessus temp = ListeAffichage;
    while (temp != NULL)
    {
        TarbreProcessus node = recherche(temp->PID);
        TarbreProcessus Parent = recherchepere(node->PID);
        printf("-----------------------------------\n");
        printf("Le nom de cette processus est : ");
        for (int i = 0; node->Nom[i] != '\0'; i++)
        {
            putchar(node->Nom[i]);
        }
        printf("\n");
        printf("PID = %d \n", node->PID);
        printf("L'etat de cette processus : %d\n", node->Etat);
        if (node->Etat == 1)
        {
            int indice;
            indice = rechercheindiceliste(Elu, temp->PID);
            printf("Le numero de microprocesseur de cette processus est : %d\n", indice);
        }
        printf("La ram de cette processus : %d\n", node->RAM);
        printf("Le PID de pere est :%d\n", Parent->PID);
        printf("-----------------------------------\n");
        temp = temp->Suivant;
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

TListeProcessus Supp(TListeProcessus *l, int PID)
{
    TListeProcessus current = *l;
    TListeProcessus previous = NULL;
    if (current == NULL)
    {
        printf("La liste est empty\n");
        return NULL;
    }
    while (current != NULL)
    {
        if (current->PID == PID)
        {
            if (previous == NULL)
            {
                *l = current->Suivant;
            }
            else
            {
                previous->Suivant = current->Suivant;
            }
            free(current);
            return *l;
        }
        previous = current;
        current = current->Suivant;
    }
    printf("PID %d non trouve dans la liste\n", PID);
    return *l;
}

TarbreProcessus recherchepere(int PID)
{
    TarbreProcessus current_node = root;

    while (current_node != NULL)
    {
        TarbreProcessus current_child = current_node->Fils;
        while (current_child != NULL)
        {
            if (current_child->PID == PID)
            {
                return current_node;
            }
            current_child = current_child->Frere;
        }
        // move to The sibling subtree
        current_node = current_node->Fils;
    }
    return NULL;
}

TListeProcessus rechercheliste(TListeProcessus l, int PID)
{
    TListeProcessus par = l;
    while (par != NULL)
    {
        if (par->PID == PID)
        {
            printf("\nPID trouvee\n\n");
            return par;
        }
        par = par->Suivant;
    }
    printf("\nPID n'existe pas\n");
    return NULL;
}

TarbreProcessus recherche(int PID)
{
    TarbreProcessus r = root->Fils, temp;
    while (r != NULL)
    {
        if (r->PID == PID)
            return r;
        else
        {
            temp = r;
            while (temp->Frere != NULL)
            {
                if (temp->Frere->PID == PID)
                    return temp->Frere;
                temp = temp->Frere;
            }
            r = r->Fils;
        }
    }
    return r;
}

TarbreProcessus rechercheName(char Nom[12])
{
    TarbreProcessus r = root->Fils, temp;
    while (r != NULL)
    {
        if (strcmp(r->Nom, Nom) == 0)
            return r;
        else
        {
            temp = r;
            while (temp->Frere != NULL)
            {
                if (strcmp(temp->Frere->Nom, Nom) == 0)
                    return temp;
                temp = temp->Frere;
            }
            r = r->Fils;
        }
    }
    return NULL;
}

int rechercheindiceliste(TListeProcessus l, int PID)
{
    if (l->PID == PID)
        return 1;
    else
        return 1 + rechercheindiceliste(l->Suivant, PID);
}

void SuppArbre(TarbreProcessus r)
{
    if (r == NULL)
        return;
    else
    {
        SuppArbre(r->Fils);
        SuppArbre(r->Frere);
        ram += r->RAM;
        ListeAffichage = Supp(&ListeAffichage, r->PID);
        switch (r->Etat)
        {
        case 0:
            Pret = Supp(&Pret, r->PID);
            break;
        case 1:
            Elu = Supp(&Elu, r->PID);
            break;
        case 2:
            ListeBloquer = Supp(&ListeBloquer, r->PID);
            break;
        }
        free(r);
    }
}
