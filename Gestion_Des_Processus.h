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
TListeProcessus Elu;
TListeProcessus Pret;
TListeProcessus Bloquer;
TListeProcessus premier;
TListeProcessus dernier;
int ram;
int PID = 1;
 
void CreerRoot();
void LancerRoot();
TListeProcessus InsererFin(TListeProcessus l, int PID); 
void creeNoued();
void Preordre(TarbreProcessus root);
