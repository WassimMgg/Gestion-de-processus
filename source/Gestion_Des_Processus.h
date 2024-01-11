#include <stdbool.h>
#ifndef __MY_HEADER__ 
#define __MY_HEADER__
#include <stdbool.h>
typedef struct elementArbre *TarbreProcessus;
typedef struct elementArbre{
    int PID;
    int PIDp; 
    int Prio; 
    char Nom[12];
    int RAM; 
    int Etat; 
    TarbreProcessus Fils; 
    TarbreProcessus Frere;
}elementArbre; 

typedef struct elementProcessus *TListeProcessus; 
typedef struct elementProcessus
{
    int PID;
    int Prio;  
    TListeProcessus Suivant; 
}elementProcessus;

//Declarer les variables
TarbreProcessus root;
TarbreProcessus noued; 
TListeProcessus Elu;
TListeProcessus Pret;
TListeProcessus ListeBloquer;
TListeProcessus ListeAffichage; 
TListeProcessus ListePIDpere; 
int ram;
int compteur;
int compteurelu; 

//Declarer les Fonctions 
void creeroot();
void LancerRoot();
TListeProcessus Inserer(TListeProcessus *l, int P, int prio); 
void Creer();
void Htop();
void afficherListe(TListeProcessus l); 
void InsererNoeud(TarbreProcessus l, int p); 
TListeProcessus SuppDebut(TListeProcessus *l);
TListeProcessus Supp(TListeProcessus *l ,int PID); 
TarbreProcessus SearchName(TarbreProcessus r,char Nom[12]);
TarbreProcessus Searchprec(TarbreProcessus r,int PID);
TListeProcessus rechercheliste(TListeProcessus l,int PID);
int rechercheindiceliste(TListeProcessus l, int PID);
TListeProcessus InsererFin(TListeProcessus *l, int P,int Prio); 
void Lancer();
void Tuer(TarbreProcessus l);
void Terminer(TarbreProcessus l);
void Bloquer(); 
void Debloquer(); 
void SuppArbre(TarbreProcessus r); 
TarbreProcessus Search(TarbreProcessus r, int PID); 
TarbreProcessus Searchfather(TarbreProcessus r,int PID);
#endif 
