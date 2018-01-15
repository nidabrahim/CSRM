
#include "gestion_personne.h"

#include "menu.h"




/****************/
/* Les couleurs */
/****************/

void color(int t,int f)
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(H,f*16+t);
}




/*************************/
/* L'interface d'acceuil */
/*************************/

void pageAcceuil()
{
	
	system("COLOR 0F");

    color(11,0);
    printf("\n                  _____________________________________________         \n");
    
    printf("                  |  ___ ____  __  ____    __ __      __      |          \n");
    printf("                  |  |__  ||  |__|  ||    /   || \\  / || |    |          \n");
    printf("                  |  |__  ||  |  |  ||    \\__ ||  \\/  || |__  |         \n");
    
    printf("                  |___________________________________________|      \n\n\n");
    color(15,0);
    
    printf("\t\t\tBienvenue dans l'application \n\n\t\tde Gestion des Actes d'Etat Civil Numerises\n\n\n");
    printf("\t\tRealise par NIDABRAHIM Youssef et NAJI Kawtar \n\n");
    printf("\t\t\tEncadre par Mr. A. El Hassouny ");
    
    color(11,0);
    printf("\n\n\n________________________________________________________________________________\n");
    color(15,0);
    
    color(4,0);
    printf("   *         \n");
    printf("  ***   ");color(4,0);color(15,0);printf(" ENSIAS 2015-2016 \n");color(4,0);
    printf(" *****        \n");
    
    color(11,0);
    printf("________________________________________________________________________________\n");
    color(15,0);
	
    

    getch(); 
	
}



/*******************************/
/* Le menu d'authentification  */
/*******************************/

void menuAuthentification()
{
	
	color(15,4);
    
  
      system("cls");

      printf("\n\n\t\n\n\n\t\tS'identifier en tant que : \n\n");
      printf("\t\t\t [1] . Administrateur\n\n");
      printf("\t\t\t [2] . Citoyen\n\n");
      printf("\t\t\t [3] . Quitter\n\n\n");
	
}



/********************************/
/* Le menu de l'administrateur  */
/********************************/

void menuAdmin()
{
	

    color(11,0);
    printf("\t\t\t << Espace Administration >>  \n\n");

    color(11,0);
    printf("\n\n\t\t\t\tM E N U\n");
    printf("\t\t\t\t-------\n\n\n");
    color(15,0);
    printf("\t\t--------------------------------------\n");
    printf("\t\t|                                     |\n");
    printf("\t\t| [1] . Gestion des personnes         |\n\n");
    printf("\t\t| [2] . Gestion des enfants           |\n\n");
    printf("\t\t| [3] . Gestion des mariages           |\n\n");
    printf("\t\t| [4] . Gestion des deces             |\n\n");
    color(11,0);
    printf("\t\t| [5] . Quitter                       |\n");
    color(15,0);
    printf("\t\t|                                     |\n");
    printf("\t\t--------------------------------------\n\n");
	
}



/************************************/
/* Le menu de gestion des personnes */
/************************************/

void menuGestionPersonnes()
{
	
	system("cls");

                     color(11,0);
                     printf("\n\n\n  - - - - - - - - -  G E S T I O N   D E S   P E R S O N N E S - - - - - - - - \n\n\n");
                     color(15,0);

                     printf("\t\t [1] . Ajouter une personne.\n\n");
                     printf("\t\t [2] . Modifier les enregistrements d'une personne.\n\n");
                     printf("\t\t [3] . Consulter la liste des personnes.\n\n");
                     printf("\t\t [4] . Chercher une personne par son nom ou prenom, CIN.\n\n");
                     printf("\t\t [5] . Retourner le nom de mere ou pere d'une personne.\n\n");
                     printf("\t\t [6] . Retourner l'age d'une personne.\n\n");
                     printf("\t\t [7] . Trier la liste des personnes.\n\n");
                     printf("\t\t [8] . Imprimer acte de naissance.\n\n");
                     color(11,0);
                     printf("\t\t [9] . Revenir au menu principal.\n\n");
                     printf("\t\t[10] . Quitter.\n\n\n");
                     color(15,0);
	
}


/*******************************/
/* Le menu de l'espace citoyen */
/*******************************/

void menuCitoyen()
{
	
	printf("\n\n\t\t\t\tM E N U\n");
    printf("\t\t\t\t-------\n\n\n");
    printf("\t\t--------------------------------------\n");
    printf("\t\t|                                     |\n");
    printf("\t\t| [1] . Acte de naissance             |\n\n");
    printf("\t\t| [2] . Acte de mariage               |\n\n");
    printf("\t\t| [3] . Acte de deces                 |\n\n");
    printf("\t\t| [4] . Se deconnecter                |\n\n");
    color(11,0);
    printf("\t\t| [5] . Quitter                       |\n");
    color(15,0);
    printf("\t\t|                                     |\n");
    printf("\t\t--------------------------------------\n\n");
	
}
