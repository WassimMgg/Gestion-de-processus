#include "Gestion_Des_Processus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

int main()
{
    printf("Initialiser la taille de ram : ");
    scanf("%d",&ram);
    CreerRoot(); 
    Preordre(root);
    return 0;
}