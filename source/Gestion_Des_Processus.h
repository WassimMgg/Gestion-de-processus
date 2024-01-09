#include <stdbool.h>
#ifndef __MY_HEADER__ 
#define __MY_HEADER__
#include <stdbool.h>
typedef struct elementArbre *TarbreProcessus;
typedef struct elementArbre{
    int PID;
    int Prio; 
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
    int Prio;  
    TListeProcessus Suivant; 
}elementProcessus;

//Declarer les variables
TarbreProcessus root;
TarbreProcessus noued; 
TListeProcessus Elu;
TListeProcessus Pret;
TListeProcessus ListeBloquer;
int ram;
int compteur;
int compteurelu; 

//Declarer les Fonctions 
void creeroot();
void LancerRoot();
TListeProcessus Inserer(TListeProcessus *l, int P, int prio); 
void Creer();
void Htop(TarbreProcessus root);
void afficherListe(TListeProcessus l); 
void InsererNoeud(TarbreProcessus l, int p); 
TListeProcessus SuppDebut(TListeProcessus *l);
TListeProcessus Supp(TListeProcessus *l ,int PID); 
TarbreProcessus recherchepere(int PID);
TListeProcessus rechercheliste(TListeProcessus l,int PID);
TListeProcessus InsererFin(TListeProcessus *l, int P, int prio);
TarbreProcessus recherche(int p); 
void Lancer();
void Tuer();
void Terminer();
void Bloquer(); 
void Debloquer(); 
TarbreProcessus rechercheName(char  Nom[12]);
#endif // heka bah tt3erref mara wahda
