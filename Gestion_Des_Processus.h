#include <stdbool.h>
typedef struct elementArbre *TarbreProcessus;
typedef struct elementArbre{
    int PID; 
    char Nom[12] ;
    int RAM; 
    int Etat; 
    TarbreProcessus Fils; 
    TarbreProcessus Frere;
}elementArbre; 

typedef struct elementProcessus *TListeProcessus; 
typedef struct elementProcessus
{
    int PID ; 
    TListeProcessus Suivant; 
}elementProcessus;

TarbreProcessus root;
TarbreProcessus noued; 
TListeProcessus Elu;
TListeProcessus Pret;
TListeProcessus Bloquer;
TListeProcessus premier;
TListeProcessus dernier;
int ram;
int compteur;

void creeroot();
void LancerRoot();
TListeProcessus InsererFin(TListeProcessus *l, int P); 
void Creer();
void Htop(TarbreProcessus root);
void afficherListe(TListeProcessus l); 
void InsererNoeud(TarbreProcessus l, int p); 
TListeProcessus SuppDebut(TListeProcessus *l); 
TarbreProcessus recherche(TarbreProcessus r, int p); 
TarbreProcessus recherchpere(TarbreProcessus l);
