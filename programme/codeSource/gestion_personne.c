
#include "gestion_personne.h"




/*******************************/
/* Récupérer la date actuelles */
/*******************************/

date DateActuelles()
{
    date  t;
    time_t temps;

	time(&temps);                         /* t contient maintenant la date et l'heure courante */

	struct tm d;

    d = *localtime(&temps);               /* décomposer la date 'temps' en année, mois, jour */

	t.jour = d.tm_mday;
    t.mois = d.tm_mon+1;
    t.annee = d.tm_year+1900;

    return t;

}




/*********************/
/* Verification date */
/*********************/


int verifierDate(date d)
{
	date dateActuelle = DateActuelles();
	
	if( d.annee > dateActuelle.annee ) return 0;
	else {
			if( d.annee == dateActuelle.annee )
			{
                if(  d.mois > dateActuelle.mois ) return 0;
                else{
					   if( d.jour > dateActuelle.jour ) return 0;
					   else return 1;
		            }
	 	    }
			else{

                    switch(d.mois)
			        {
			        	 case 1 :
				         case 3 :
				         case 5 :
				         case 7 :
				         case 8 :
				         case 10:
				         case 12:
						           if( d.jour <1 || d.jour > 31 ) return 0;
						           else
							         return 1;

				         case 4 :
				         case 6 :
				         case 9 :
				         case 11:
                                   if( d.jour <1 || d.jour > 30 ) return 0;
						           else
							          return 1;

				         case 2 :
								   if(d.annee % 4 == 0 && ( d.annee%100 !=0))        /* Si l'année est bissextille */
								   {
										if( d.jour >= 1 && d.jour <=29 ) return 1;
										else return 0;
			   			           }
			   			           else{
                                           if( d.jour >= 1 && d.jour <=28 ) return 1;
										   else return 0;
			   			               }


						 default:
								 return 0;

	                  }
				   
		        }
		 }
}




/***************/
/* Calcule Age */
/***************/

int calculerAge(date date_naissance)
{
    int age;
    
     //On récupére la date actuelle:
	date date_actuelle = DateActuelles();

     //L'âge est la différence entre l'année actuelle et l'année de naissance:
	age = date_actuelle.annee - date_naissance.annee;
	
     // On décremante l'âge si le mois et le jour de naissance 
	//  sont supérieurs au mois et le jour actuelle:
	if( (date_actuelle.mois < date_naissance.mois) 
	    || ( (date_actuelle.mois == date_naissance.mois) 
		  && (date_actuelle.jour < date_naissance.jour) ) )
		  
		 age--;

    return age;

}




/************************/
/* Identifiant personne */
/************************/


int genererId(char sexe,int* nbrePersonne)
{
	int idPersonne;
	
	(*nbrePersonne)++;                                      /* on incremente le nombre de personnes, pour creer un autre id */
															 /* puis on ajoute le chiffre de sexe */
	if( sexe == 'M' ) idPersonne = (*nbrePersonne)*10 + 1;       /* - 1 : Homme ; 2 : Femme */
	else
	   idPersonne = (*nbrePersonne)*10 + 2;
	   
	return idPersonne;
}



/****************/
/* Age personne */
/****************/

int agePersonne(listePersonne p)
{
    return calculerAge(p->data->dateNaissance);

}

/****************/
/* Age personne */
/****************/
int verifierAge(listePersonne debut,date dateFils, int idPere)
{
 	int agePere,ageFils;

	 listePersonne pere= chercherPersonneById( debut, idPere);
	 
	  //Calculer l'âge du père:
     agePere=agePersonne(pere);
     
      //Calculer l'âge du fils:
     ageFils=calculerAge(dateFils);

      //Si l'âge est invalid, on retourne 0 sinon 1
     return agePere>ageFils?1:0;


}


/*************************************************************************/
/* Créer la structure dataPersonne qui contient les données du personne  */
/*************************************************************************/

ptrDataPersonne creerDataPersonne(int id,char* nom,char* prenom,date date_naissance,char sexe,int deces,int idPere,int idMere)
{
	 //La création de la structure DataPersonne:
	ptrDataPersonne donnee = NULL;
	donnee = Malloc(dataPersonne);
	
	 //Remplissage des champs de données:
	donnee->id = id;
	donnee->idPere = idPere;
	donnee->idMere = idMere;
	strcpy(donnee->nom,nom);
	strcpy(donnee->prenom,prenom);
	donnee->dateNaissance = date_naissance;
	donnee->sexe = sexe;
	donnee->deces = deces;
	
	 //Lors de la création, la personne n'est pas encore marier.
	donnee->idConjoint = -1;
	
	return donnee;
}



/********************************/
/* Créer la structure Personne  */
/********************************/

listePersonne creerPersonne(int id,char* nom,char* prenom,date date_naissance,char sexe,int idPere,int idMere)
{
	listePersonne listeP = NULL;
	
	listeP = Malloc(personne);
	
     /** Création de la structure donnee **/
	listeP->data = creerDataPersonne(id,nom,prenom,date_naissance,sexe,0,idPere,idMere);  
	
	listeP->fils = NULL;
	listeP->frere = NULL;
	listeP->suivant = NULL;
	
	return listeP;
}




/********************************/
/* Chercher une personne by id  */
/********************************/



listePersonne chercherPersonneById(listePersonne debut,int id)
{
   listePersonne p = debut;
   
   while( p != NULL && p->data->id != id)  p = p->suivant;

   return p ;
}



/**************************************/
/* Ajouter une Personne dans la liste */
/**************************************/


listePersonne addNewPersonne(listePersonne debut,int* nbrePersonne,char* prenom,date date_naissance,char sexe,int idPere,int idMere)
{
	  listePersonne p = debut;
	  listePersonne pere = NULL;
	  listePersonne mere = NULL;
	  listePersonne listeP = NULL;
	  int id;
	  
       /* Generer l'identifiant du personne à partir de son sexe et le nbr des personnes */
	  id = genererId( sexe,nbrePersonne);        
	  
       /* pointeur sur la mere */
	  mere = chercherPersonneById(debut,idMere);

       /* pointeur sur le pere */
      pere = chercherPersonneById(debut,idPere);
	  
       /* création de la structure personne */
	  listeP = creerPersonne(id,pere->data->nom,prenom,date_naissance,sexe,idPere,idMere);
	  
	  if(p == NULL)
		 // si la liste des personnes est vide
			 debut = listeP;
	   else
	   {
	  
             /* on cherche le dernier element de la liste */
	        while( p->suivant != NULL)  p = p->suivant;     
	  
	        p->suivant = listeP;


	        p = mere->fils;
	  
            /* si la mère n'avait aucun fils */
	       if(!p) mere->fils = listeP;
	       else{
                  /* On cherche le plus petit frere du fils ainé de la mère */
                  /* afin d'ajouter ce nouveau fils comme son frere.   */
			     while( p->frere != NULL) p = p->frere;
															    
			     p->frere = listeP;
              }

            /* Si le pere n'a pas de fils */
           if(! (pere->fils)) pere->fils = listeP;

	  }
          
	  return debut;
			  
}


/*************************/
/* Afficher une personne */
/*************************/

void afficherPersonne(listePersonne p)
{
    color(4,0);
	printf("\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n");
	color(7,0);
	printf("- - ID : ");color(15,0);printf(" %d \n\n",p->data->id);
	 
	color(7,0);
	printf("- - NOM : ");color(15,0);printf(" %s \n\n",p->data->nom);
	 
	color(7,0);
	printf("- - PRENOM : ");color(15,0);printf(" %s \n\n",p->data->prenom);
	 
	color(7,0);
	printf("- - DATE DE NAISSANCE : ");
	color(15,0);printf(" %d / %d / %d \n\n",p->data->dateNaissance.jour,p->data->dateNaissance.mois,p->data->dateNaissance.annee);
	 
	if( p->data->sexe == 'M' )
	{
        color(7,0);
	    printf("- - SEXE : ");color(15,0);printf(" Masculin \n\n");
    }
	else{
            color(7,0);
            printf("- - SEXE : ");color(15,0);printf(" Feminin \n\n");
		}
          
    if( p->data->idConjoint == -1 )
	{
        color(7,0);
        printf("- - SITUATION : ");color(15,0);printf(" Celebataire \n\n");
    }
    else{
            color(7,0);
            printf("- - SITUATION FAMILIALE : ");color(15,0);printf(" Marie \n\n");
	    }      
          
	if( p->data->deces == 0 )
	{
        color(7,0);
	    printf("- - AGE : ");color(15,0);printf(" %d ans \n\n",agePersonne(p));
	 
        color(7,0);
        printf("- - SITUATION : ");color(15,0);
		
		if( p->data->sexe == 'M' )  printf(" Vivant \n\n");	
		else
		    printf(" Vivante \n\n");	
		
    }
    else{
            color(7,0);
            printf("- - SITUATION : ");color(15,0);
			
			if( p->data->sexe == 'M' )  printf(" Mort \n\n");	
		    else
			    printf(" Morte \n\n");
	    }
          
     color(7,0);
     printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n");
     color(15,0);
     

}




/*********************/
/* Afficher la liste */
/*********************/

void afficherListePersonne(listePersonne debut)
{
	 listePersonne p = debut;
	 while(p != NULL)
	 {
		   afficherPersonne(p);
		   getch();
		   p = p->suivant;
	 }
}



/**************************/
/* Supprimer une personne */
/**************************/


int supprimerPersonne(listePersonne debut,int id)
{
   listePersonne pers = chercherPersonneById(debut,id);
   
   if( pers != NULL ) {                                 /* La personne n'existe pas */
   	                     pers->data->deces = 1;
   	                     return 1;
		              }
   else return 0;

}



/**********************************/
/* modifier prenom d'une personne */
/**********************************/


void modifierPrenomPersonne(listePersonne debut,int id)
{
 	 char prenom[CMAX];
 	 
	 listePersonne p = chercherPersonneById(debut,id);   /* rechercher la personne */
	 
	 if(p==NULL)  printf("\n - le personne n'existe pas \n\n");
	 else {
	          printf("\n -- Entrer le nouveau prenom : ");
	          
	          fflush(stdin);gets(prenom);fflush(stdin);
	 
	          strcpy(p->data->prenom,prenom);
          }
}


/*****************************************************/
/* Chercher personne par le nom ou prenom ou bien id */
/*****************************************************/

void chercherPersonne(listePersonne debut, int choix)
{
	 int id, iTrouve = 0; 
	 char nom[CMAX],prenom[CMAX];
	 listePersonne pers = NULL;
	 
	 switch(choix)
	 {
		 case 1 : //recherche par l'identifiant
		 
		          system("cls");
		          
		          color(11,0);
                  printf("\n\n - - - - - - - - - - - - LA RECHERCHE PAR L'IDENTIFIANT  - - - - - - - - - - - - \n\n");
                  color(15,0);
		 
				  printf("\n\n -- Saisissez un identifiant : ");
				  scanf("%d",&id);
				  
				   //On cherche la personne par son identifiant:
				  pers = chercherPersonneById(debut,id);
				  
				   //La personne n'existe pas:
				  if( !pers ) 
				  {
				  	printf("\n\n - La personne de l'id %d n'existe pas ! \n\n ",id);
				  }
				  else{
				  	     afficherPersonne(pers);
				      }
				  
				  
				  getch();
				  break;
				  

		 case 2 : //recherche par le nom
		 
		          system("cls");
		          
		          color(11,0);
                  printf("\n\n - - - - - - - - - - - - - -  LA RECHERCHE PAR NOM   - - - - - - - - - - - - - - \n\n");
                  color(15,0);
		 
                  printf("\n\n -- Saisissez un Nom : ");
                  fflush(stdin);gets(nom);fflush(stdin);
                  
                   //Rendre le nom en majuscule:
                  uppercase(nom);
                  
                   //La recherche:
                  pers = debut;

                  while( pers != NULL )
				  {
				  	      //On affiche chaque personne trouvée:
						 if( strcmp(pers->data->nom,nom) == 0) 
						  {
						  	iTrouve = 1;
						  	afficherPersonne(pers);
						  	getch();
						  }
						 
						 pers = pers->suivant;
   		          }
   		          
   		          if( iTrouve == 0 ) printf("\n\n - Personne n'a %s comme nom ! \n\n ",nom);

                  getch();
				  break;


		 case 3 : //recherche par le prenom
		 
		          system("cls");
		          
		          color(11,0);
                  printf("\n\n - - - - - - - - - - - - - -  LA RECHERCHE PAR PRENOM - - - - - - - - - - - - -\n\n");
                  color(15,0);
		 
                  printf("\n\n -- Saisissez un Prenom : ");
                  fflush(stdin);gets(prenom);fflush(stdin);
                  
                   //Premiere lettre en majuscule:
                  premLettreMaj(prenom);

                   //La recherche:
                  pers = debut;

                  while( pers != NULL )
				  {
				  	     
				  	      //On affiche chaque personne trouvée:
						 if( strcmp(pers->data->prenom,prenom) == 0) 
						 {
						 	iTrouve = 1;
						 	afficherPersonne(pers);
						 	getch();
						 }

						 pers = pers->suivant;
   		          }
   		          
   		          if( iTrouve == 0 ) printf("\n\n - Personne n'a %s comme prenom ! \n\n ",prenom);
   		          
                  getch();
				  break;
				  
		case 4 :
                 //Revenir au menu precedent
                        	
                  break;
                        	         

     }
}



/**********************************************/
/* Imprimer acte de naissance d'une personne  */
/**********************************************/


void printPersonne(listePersonne debut,int id)
{
     listePersonne pers = NULL;
     listePersonne pere = NULL;
     listePersonne mere = NULL;
     date dateActuelle = DateActuelles();
     


	  //La personne qui veut avoir son acte de naissance:
	 pers = chercherPersonneById(debut,id);

	  //Son pere:
	 pere = chercherPersonneById(debut, pers->data->idPere);
	 
	  //Sa mere:
     mere = chercherPersonneById(debut, pers->data->idMere);
	 
	 FILE *fiche;

     fiche = fopen("acteNaissance.doc","wt");

     if(fiche == NULL) printf("erreur\n");
     else
     {

       fprintf(fiche,"\t\t\t\tEXTRAIT DE L'ACTE DE NAISSANCE\n\n\n");
       fprintf(fiche,"\t -NOM :                 %s \n\n",pers->data->nom);
       fprintf(fiche,"\t -PRENOM :              %s \n\n",pers->data->prenom);
     
       if(pers->data->sexe == 'M')
         fprintf(fiche,"\t -SEXE :              Masculin \n\n");
       else
         fprintf(fiche,"\t -SEXE :              Feminin \n\n");
       
       fprintf(fiche,"\t -DATE DE NAISSANCE :   %d / %d / %d \n\n\n",pers->data->dateNaissance.jour,pers->data->dateNaissance.mois,pers->data->dateNaissance.annee);

	   if(pers->data->idPere != -1)
	      fprintf(fiche,"\t -NOM DE PERE :      %s %s \n\n",pere->data->nom,pere->data->prenom);
	   else
          fprintf(fiche,"\t -NOM DE PERE :      ( n'est pas inscrit ) \n\n");
          
	   if(pers->data->idMere != -1)
          fprintf(fiche,"\t -NOM DE MERE :      %s %s \n\n",mere->data->nom,mere->data->prenom);
       else
          fprintf(fiche,"\t -NOM DE MERE :      ( n'est pas inscrite ) \n\n");
          
          fprintf(fiche,"\n\n\n\n\t\t\t\t -DATE DE DELIVRANCE : %d / %d / %d \n\n",dateActuelle.jour,dateActuelle.mois,dateActuelle.annee);

          

       fclose(fiche);
       
        //Convertir l'acte en PDF:
       system("OfficeToPDF.exe acteNaissance.doc actes/acteNaissance.pdf ");
       system("del acteNaissance.doc ");
       
       printf("\n\n - L'actes de naissance est bien imprime\n\n");


      }

}


/***************************************************/
/* Retourner le nom de mere ou pere d’une personne */
/***************************************************/

void nomPereMere( listePersonne debut,int id )
{
   listePersonne p = NULL;
   listePersonne pere=NULL;
   listePersonne mere = NULL;
   
   p = chercherPersonneById( debut, id );
   
   if( p->data->idPere == -1 && p->data->idMere == -1 )
   {
	   printf("\n - Les parents de  %s %s  ne sont pas enregistres. ",p->data->nom ,p->data->prenom);
   }
   else
   {
       pere = chercherPersonneById( debut, p->data->idPere);
       mere = chercherPersonneById( debut, p->data->idMere);

       printf("\n - Le Pere de %s %s est %s %s \n",p->data->nom ,p->data->prenom,pere->data->nom,pere->data->prenom);

       printf("\n\n - La Mere de %s %s est %s %s \n",p->data->nom,p->data->prenom,mere->data->nom,mere->data->prenom);

   }
   
   

}



/*************************************/
/* modifierFilsFrere d'une personnes */
/*************************************/

listePersonne modifierFilsFrere(listePersonne debut, listePersonne pCurr, listePersonne succ )
{
    listePersonne p = debut;
     
    while( p != NULL )
    {
		if( p->fils == pCurr )   p->fils = succ;        /* On change le fils ou le frere de cette personne  */
		else 
		    if( p->fils == succ )   
	            p->fils = pCurr;
		 
		if( p->frere == pCurr ) p->frere = succ;
		 else 
		    if( p->frere == succ ) 
			    p->frere = pCurr;
		 
		 p = p->suivant;

    }
     
     return debut;
}


/********************************/
/* Trier la liste des personnes */
/********************************/


listePersonne trierListe(listePersonne debut, int choix)
{
    
	listePersonne p = debut, succ = debut, temp = NULL;
    
    int continu = 0;

    temp = Malloc(personne);
     
     // Si la liste est vide 
    if( debut == NULL )
		return debut ;

	switch(choix)
	{

	case 1:

            do 
			{                                       /* i eme iteration */
				continu = 0;
				p = debut;
				succ = p->suivant;
				
				while (succ != NULL  )
	           	{
	        		if( p->data->id < succ->data->id )               /* Si l'identifiant de personne current est inf.
					                                                    à celui de la personne suivante   */
	        		{

                           debut = modifierFilsFrere( debut,p,succ );

						   /* Temp <- p */
						   
						   temp->data = p->data;
						   
						   temp->frere = p->frere;
						   temp->fils = p->fils;
						   
						   /* p <- succ */
						   
						   p->data = succ->data;

						   p->frere = succ->frere;
						   p->fils = succ->fils;
						   
						   
						   /* succ <- Temp */


                           succ->data = temp->data;
                           
						   succ->frere = temp->frere;
						   succ->fils = temp->fils;


			        		continu = 1;
	        		}
                        p = succ;
	                    succ = succ->suivant;
	           }


	     	  }while(continu == 1);
	     	  
	     	  color(7,0);
	     	  printf("\n\n - Le tri est bien effectuee \n\n");
	     	  color(15,0);

            getch();
            break;

    case 2:

            do {
                continu = 0;
				p = debut;
				succ = p->suivant;

				while (succ != NULL)
	           	{
                   if( strcmp(p->data->nom,succ->data->nom) < 0 )
	        		{
                             modifierFilsFrere( debut,p,succ );

						   /* Temp <- p */

						   temp->data = p->data;

						   temp->frere = p->frere;
						   temp->fils = p->fils;

						   /* p <- succ */

						   p->data = succ->data;

						   p->frere = succ->frere;
						   p->fils = succ->fils;


						   /* succ <- Temp */

						   succ->data = temp->data;

						   succ->frere = temp->frere;
						   succ->fils = temp->fils;


			        		continu = 1;
		 	        }
		 	        
		 	            p = succ;
	                    succ = succ->suivant;
	           }

	     	  }while(continu == 1);
	     	  
	     	  
	     	   
	     	  color(7,0);
	     	  printf("\n\n - Le tri est bien effectuee \n\n");
	     	  color(15,0);

            getch();
            break;
            
    case 3 :  
	         //Retourner au menu précédent:
			 break;    
            

    default :
                 printf("\n\n\t/!\\ Votre choix est invalid /!\\\n\n");

    }

    return debut;
}



/**************/
/* Majuscule  */
/**************/


void uppercase ( char *ch )
{
	
  while ( *ch != '\0' )
  {
    *ch = toupper ( *ch );
    ++ch;
  }
  
}



/*****************************/
/* 1ere lettre en Majuscule  */
/*****************************/


void premLettreMaj ( char *ch )
{
	
  *ch = toupper ( *ch );
  
}
















