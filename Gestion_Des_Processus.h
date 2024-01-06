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
TListeProcessus ListeBloquer;
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
TarbreProcessus recherchepere(TarbreProcessus l);
TListeProcessus rechercheliste(TListeProcessus l);
TarbreProcessus recherche(TarbreProcessus l, int p); 
void Lancer();
void Tuer();
void Terminer();
void Bloquer(); 
void Debloquer(); 
