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

void CreerRoot();
void LancerRoot();
TListeProcessus InsererFin(TListeProcessus l, int PID); 
void AjouterFils(TarbreProcessus root, int PID , char Nom[12] , int Ram , int Etat);
TarbreProcessus createNode(TarbreProcessus root, int PID , char Nom[12] , int Ram , int Etat );
