

#include "gestion_personne.h"
#include "gestion_enfants.h"
#include "gestion_mariage.h"
#include "gestion_deces.h"
#include "gestion_fichiers.h"
#include "menu.h"



int main()
{
	
	

	listePersonne listeP = NULL , p = NULL;
	int id, idP, idPere, idMere, idConj, NbrPers, i, j, testDate, testAge, nbrePersonne=0, choixSearch, choixIdent, a, idM, continu, choixMenuP, choixMenu=1;
	char nom[CMAX], prenom[CMAX], sexe, login[MAX],password[MAX], choixContinu, loginNom[20], choixSupp;
	date dateNaissance;
	
	
	

/*@@@@@@  CHARGER LES DONNEES  @@@@@*/


listeP = charger(&nbrePersonne);

	
/*@@@@@@  MENU  @@@@@*/


pageAcceuil();


/*@@@@@ AUTHENTIFICATION @@@@@*/


do{
      
    menuAuthentification();
    
    color(14,4);
    printf("\n\n\n\t -- Faites votre choix : ");
    fflush(stdin);
    scanf("%d",&choixIdent);
    color(15,4);
      
}while(choixIdent != 1 && choixIdent != 2 && choixIdent != 3);  


    
switch(choixIdent)
{
	
case 1:  //L'authentification en tant qu'administrateur:
		
			
	color(15,4);
		     
    do 
    {
        system("cls");

        printf("\n\n\t\t\t    AUTHENTIFICATION\n\n");
        printf("\t\t--------------------------------------\n");
        printf("\n\t\t| Login : "); fflush(stdin); scanf("%s",&login);
        printf("\n\n\t\t| Mot de Passe : ");
              
        //Cacher le mot de passe:
         
        i=0;
        
		 //La saisie du mot de passe:      
        do{ 
             //On récupére chaque élément saisie:  	   
            password[i] = getch();
              	   
            if(password[i] == 0x08) // Code hexa. de <supprimer>
            {
                system("cls");
                printf("\n\n\t\t\t    AUTHENTIFICATION\n\n");
                printf("\t\t--------------------------------------\n");
                printf("\n\t\t| Login : %s\n",login);
                printf("\n\n\t\t| Mot de Passe : ");
                        
                //On affiche les elements déjà saisies
				//sans l'element i-1 qui doit être supprimé 
				
                for( j=0 ; j<=i-2 ; j++ )
                   printf("*");
                                          
                if(i == 0 || i == 1) i = 0;
                else i = i-1;
                        
                j = i;
              	   	  
			}
			else
            {
				 //On affiche étoile tant qu'on a pas encore taper <entrer>
				if( password[i] != 0x0D )   printf("*"); 
				
				 //On récupére l'élément courant afin de tester s'il s'agit de <l'entrer> ou pas: 
                j = i;
                
                 //On passe à l'élément suivant:
		     	i++;
			}
              	
		}while(password[j] != 0x0D); //Code Hexa. de <entrer>, s'il s'agit de l'entrer on quitte.
			  
		password[j] = '\0';
              
               
        //Vérifier login et le mot de passe:
        if( ! authentifier( login,password,loginNom) )
        {
        	color(7,4);
        	printf("\n\n\n\n\t\t  -Mot de passe ou login incorrect-  ");
        	color(15,4);
        	getch();
        	continu = 0;
        }
        else continu = 1;

    }while( !continu );


    system("COLOR 0F");

           
    do{ 

        //L'espace administration:
    
        system("cls");
        printf("\n  Bienvenue MR. %s ",loginNom);
                 
        menuAdmin();
                 
        color(14,0);
        printf("\t -- Faites votre choix : ");
        fflush(stdin);
        scanf("%d",&choixMenuP);
        color(15,0);



        switch(choixMenuP)
        {
        case 1: 
                //Gestion des personnes

                do
				{
                    menuGestionPersonnes();

                    color(14,0);
					printf("\t -- Faites votre choix : ");
					fflush(stdin);
                    scanf("%d",&choixMenu);
                    fflush(stdin);
                    color(15,0);



              

			         switch(choixMenu)
			         {
					    case 1 :
                                    system("cls");

                                    color(11,0);
                                    printf("\n\n - - - - - - - -  - - - - - AJOUTER DES PERSONNES - - - - - - - - - -  - - - - \n\n");
                                    color(15,0);
                                    
                                  	printf("\n - Combien de personne voulez vous saisir : ");
	                                scanf("%d",&NbrPers);
	                                
									if( NbrPers > 0 )
									{
                                        color(4,0);
									    printf("\n\n- - - - - - - - - - - - - LA SAISIE DES DONNEES - - - - - - - - - - - - - - - \n\n");
									    color(15,0);
                                    }

	                                for(i = 0 ; i < NbrPers ; i++)
	                                {

                                       printf("  - PRENOM : ");fflush(stdin);gets(prenom);fflush(stdin);

                                       printf("\n  - SEXE : ");fflush(stdin);scanf("%c",&sexe);fflush(stdin);


                                         //Vérification de l'identifiant du Père :
		                                 // - Si le père n'existe pas.
		                                 // - Si le père n'est pas un homme.
		                                 
		                                printf("\n  - ID DU PERE : ");
                                        do{

		                                	scanf("%d",&idPere);
		                                	
		                                	p = chercherPersonneById(listeP,idPere);
		                                	
		                                	if( !p ) 
		                                	{
		                                		color(7,0);
		                                		printf("\n  - Id n'existe pas -");
		                                		color(15,0);
												printf(" ID DU PERE : ");

											}
											else
											{
												if( idPere%10 != 1 )
												{
													color(7,0);
		                                		    printf("\n  - Id invalid -");
		                                		    color(15,0);
												    printf(" ID DU PERE : ");	
												}
											}
					                  	 
                                        }while( !p || ( idPere%10 != 1 )  );



                                         //Vérification de l'identifiant de la mere :
	                             	     // - Si la mere n'existe pas.
	                              	     // - Si la mere n'est pas une femme.
	                              	     
	                              	    printf("\n  - ID DE LA MERE : ");
                                        do{

											scanf("%d",&idMere);
											
											p = chercherPersonneById(listeP,idMere);
		                                	
		                                	if( !p ) 
		                                	{
		                                		color(7,0);
		                                		printf("\n  - Id n'existe pas -");
		                                		color(15,0);
												printf(" ID DE LA MERE : ");

											}
											else
											{
												if( idMere%10 != 2 )
												{
													color(7,0);
		                                		    printf("\n  - Id invalid -");
		                                		    color(15,0);
												    printf(" ID DE LA MERE : ");	
												}
											}

                                        }while( !p || ( idMere == idPere ) || ( idMere%10 != 2 ) );



                                         //On vérifier la date de naissance
                                        do{

	                                        printf("\n  - DATE DE NAISSANCE : ");
	                                        scanf("%d/%d/%d",&dateNaissance.jour,&dateNaissance.mois,&dateNaissance.annee);

                                             // Si la date est invalid 
                                            testDate = verifierDate(dateNaissance);     
											 
											 // Si l'age du fils est plus grand que celui du pere         
			                                testAge = verifierAge(listeP,dateNaissance,idPere);     

                                        }while( testDate == 0 || testAge==0 );
                                        
                                        
                                       color(4,0);
	                                   printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n");
	                                   color(15,0);


                                      /* insertion */
                                     listeP = addNewPersonne(listeP,&nbrePersonne,prenom,dateNaissance,sexe,idPere,idMere);

                                   }

                                    getch();
                                    break;
                                    

                        case 2 :
                                    system("cls");

                                    color(11,0);
                                    printf("\n\n - - - - - - - - - - - - - - - -  MODIFICATION  - - - - - - - - - - - - - - - - \n\n");
                                    color(15,0);
                                    
                                    printf("\n\n - Saisissez l'identifiant du personne a modifier : ");

                                    scanf("%d",&idM);

                                    modifierPrenomPersonne(listeP,idM);
                                    
                                    
                                    getch();
                                    break;

					    case 3 :
                                    system("cls");
                                    
                                    color(11,0);
                                    printf("\n\n - - - - - - - - - - - - - - - - -  AFFICHAGE  - - - - - - - - - - - - - - - - - \n\n");
                                    color(15,0);
                                    
                                    afficherListePersonne(listeP);
                                    
                                    
                                    getch();
                                    break;
                                    
                                    
                        case 4 :  
                                     do{
                        	
                        	            do{
                                             system("cls");
                                    
                                             color(11,0);
                                             printf("\n\n - - - - - - - - - - -  RECHERCHE PAR NOM / PRENOM / ID  - - - - - - - - - - - - \n\n");
                                             color(15,0);
                                    
                                    

                                             printf("\n\t\t [1].Recherche par l'Identifiant  \n");
                                             printf("\n\t\t [2].Recherche par Nom  \n");
                                             printf("\n\t\t [3].Recherche par Prenom  \n");
                                             color(11,0);
                                             printf("\n\t\t [4].Revenir au menu precedent \n\n");
                                             color(15,0);

                                             color(14,0);
                                             printf("\n\t - Faites votre choix : ");
                                             scanf("%d",&choixSearch);
                                             color(15,0);

                                          }while( choixSearch != 1 && choixSearch != 2 && choixSearch != 3 && choixSearch != 4 );

                                          chercherPersonne(listeP,choixSearch);
                                      
                                       }while( choixSearch != 4 );
                                      
                                      
                                       
                                       break;
                                    
                                    
					    case 5 :
                                    system("cls");
                                    
                                    color(11,0);
                                    printf("\n\n - - - - - - -   RETOURNER LE NOM DE MERE OU PERE D'UNE PERSONNE   - - - - - - - \n\n");
                                    color(15,0);
                                    
                                    printf("\n\n - Saisissez l'identifiant d'une personne : ");
                                    scanf("%d",&id);
                                    
                                    nomPereMere( listeP, id );
                                    
                                    getch();
                                    break;
                                    
                        case 6 :
                                    system("cls");
                                    
                                    color(11,0);
                                    printf("\n\n - - - - - - - - - - - -   RETOURNER L'AGE D'UNE PERSONNE  - - - - - - - - - - - \n\n");
                                    color(15,0);
                                    
                                    printf("\n\n - Saisissez l'identifiant d'une personne : ");
                                    scanf("%d",&id);
                                    
                                    p = chercherPersonneById( listeP, id );
                                    
                                    if( !p ) printf("\n\n - La personne de l'id %d n'existe pas ! \n\n ",id);
                                    else
                                      printf("\n\n - %s %s , qui a comme identifiant %d, a %d ans \n\n",p->data->nom,p->data->prenom,p->data->id,agePersonne(p));

                                    getch();
                                    break;
                                    
					    case 7 :
                                    
                                    do
									{
									  
									    do
										{
											system("cls");
                                    
                                            color(11,0);
                                            printf("\n\n- - - - - - - - - - - - --  TRIER LA LISTE DES PERSONNES - - - - - - - - - - - - \n\n");
                                            color(15,0);
											

                                            printf("\n\t\t [1].Trier par l'identifiant  \n");
                                            printf("\n\t\t [2].Trier par Nom  \n");
                                            color(11,0);
                                            printf("\n\t\t [3].Revenir au menu precedent \n\n");
                                            color(15,0);

                                            color(14,0);
                                            printf("\n - Faites votre choix : ");
                                            scanf("%d",&choixSearch);
                                            color(15,0);

                                        }while( choixSearch != 1 && choixSearch != 2 && choixSearch != 3 );

                                        listeP = trierListe(listeP,choixSearch);
									
								   }while( choixSearch != 3 );
									
									
                                    
                                    
                                    break;
                                    
                        case 8 :
                                    system("cls");
                                    
                                    color(11,0);
                                    printf("\n\n - - - -  - - - - - - - - -   IMPRIMER ACTE DE NAISSANCE   - - - - - - - - - - - - \n\n");
                                    color(15,0);
                                    
                                    
				                    
				                    printf("\n - Saisissez l'identifiant d'une personne : ");
                                    do{
									
	                                      scanf("%d",&id);
	                                      
	                                      p = chercherPersonneById(listeP,id);
	                                      
	                                      if(!p) printf("\n - Saisissez un autre : ");
	                                      
	                                  }while( !p );
				                    
				                    printPersonne(listeP,id);
				                    
				                    

				                    getch();                                    
                                    break;
                                    
                        case 9 :
                        	       //Revenir au menu principal
                        	
                        	        break;
                        	        
						case 10 :    
						
						            //Quitter
     	     
                                    sauvegarder( listeP,nbrePersonne);
   		                            exit(0);
						        
                                    break;
                                    
                                    
                                    
						default:
							    color(7,0);
                                printf("\n\n\t/!\\ Votre choix est invalid /!\\\n\n");
                                color(15,0);
                                getch();


		            }
		            

                    

              }while( choixMenu != 9  );

		            
		            
              break;




	    case 2:
	 	
	 	       //Gestion des enfants
		       do{
                     system("cls");

                     color(11,0);
                     printf("\n - - - - - - - - - - G E S T I O N   D E S   E N F A N T S - - - - - - - - - - - \n\n\n");
                     color(15,0);
                     
                     printf("\t\t [1] . Afficher les enfants d'une personne \n\n");
                     printf("\t\t [2] . Ajouter les enfants d'une personne\n\n");
                     color(11,0);
                     printf("\t\t [3] . Revenir au menu principal.\n\n");
                     printf("\t\t [4] . Quitter.\n\n\n");
                     color(15,0);

                     color(14,0);
					 printf("\t -- Faites votre choix : ");
                     scanf("%d",&choixMenu);
                     color(15,0);



			         switch(choixMenu)
			         {
					    case 1 :
                                    system("cls");
                                    
                                    color(11,0);
                                    printf("\n\n - - - - - - - - - - - - - - AFFICHER LES ENFANTS - - - - - - - - - - - - - - - \n\n");
                                    color(15,0);
                                    
                                  	printf("\n - Saisissez l'identifiant d'une personne : ");
	                                scanf("%d",&id);
	                                
	                                afficherEnfants(listeP,id);
	                                
                                    getch();
                                    break;
                                    


					    case 2 :
                                    system("cls");
                                    
                                    color(11,0);
                                    printf("\n\n - - - - - - - - - - - - - - AJOUTER LES ENFANTS - - - - - - - - - - - - - - - \n\n");
                                    color(15,0);
                                    
                                  	printf("\n - Combien d'enfants voulez vous saisir : ");
	                                scanf("%d",&NbrPers);

	                                printf("\n\n - - - - - - - - - - - - -  LA SAISIE DES DONNEES - - - - - - - - - - - - \n\n");

	                                for(i = 0 ; i < NbrPers ; i++)
	                                {
                                       printf("  - PRENOM : ");fflush(stdin);gets(prenom);fflush(stdin);

                                       printf("  - SEXE : ");fflush(stdin);scanf("%c",&sexe);fflush(stdin);


                                         //Vérification de l'identifiant du Pere :
		                                 // - Si le pere n'existe pas.
		                                 // - Si le pere n'est pas un homme.
                                         
                                        printf("\n  - ID DU PERE : ");
                                        do{

		                                	scanf("%d",&idPere);
		                                	
		                                	p = chercherPersonneById(listeP,idPere);
		                                	
		                                	if( !p ) 
		                                	{
		                                		color(7,0);
		                                		printf("\n  - Id n'existe pas -");
		                                		color(15,0);
												printf(" ID DU PERE : ");

											}
											else
											{
												if( idPere%10 != 1 )
												{
													color(7,0);
		                                		    printf("\n  - Id invalid -");
		                                		    color(15,0);
												    printf(" ID DU PERE : ");	
												}
											}
					                  	 
                                        }while( !p || ( idPere%10 != 1 )  );



                                         //Vérification de l'identifiant de la mere :
	                             	     // - Si la mere n'existe pas.
	                              	     // - Si la mere n'est pas une femme.
	                              	     
	                              	    printf("\n  - ID DE LA MERE : ");
                                        do{

											scanf("%d",&idMere);
											
											p = chercherPersonneById(listeP,idMere);
		                                	
		                                	if( !p ) 
		                                	{
		                                		color(7,0);
		                                		printf("\n  - Id n'existe pas -");
		                                		color(15,0);
												printf(" ID DE LA MERE : ");

											}
											else
											{
												if( idMere%10 != 2 )
												{
													color(7,0);
		                                		    printf("\n  - Id invalid -");
		                                		    color(15,0);
												    printf(" ID DE LA MERE : ");	
												}
											}

                                        }while( !p || ( idMere == idPere ) || ( idMere%10 != 2 ) );
 
                                        


                                      //On vérifier la date de naissance
                                      do{

	                                         printf("  - DATE DE NAISSANCE : ");
	                                         scanf("%d/%d/%d",&dateNaissance.jour,&dateNaissance.mois,&dateNaissance.annee);

                                             testDate = verifierDate(dateNaissance);               /* Si la date est invalid */
			                                 testAge = verifierAge(listeP,dateNaissance,idPere);     /* Si l'age de fils est plus grand que celui du pere */

                                        }while( testDate == 0 || testAge==0 );



                                     listeP = addNewPersonne(listeP,&nbrePersonne,prenom,dateNaissance,sexe,idPere,idMere);    /* insertion */

                                   }

                                    getch();
                                    break;

                                    
                        case 3 : 
                                    //Revenir au menu principal
                                    break;
                        	
						case 4 :            
                                    //Quitter
     	     
                                    sauvegarder( listeP,nbrePersonne);
   		                            exit(0);
						        
                                    break;

						default:
							    color(7,0);
                                printf("\n\n\t\t/!\\ Votre choix etait invalid /!\\\n\n");
                                color(15,0);
                                getch();


		            }

              

              }while( choixMenu != 3 );



              break;
              
        case 3:
     	       //Gestion du mariages
     	
     	
            	do{
                     system("cls");

                     color(11,0);
                     printf("\n - - - - - - - - - - G E S T I O N   D U   M A R I A G E S - - - - - - - - - - - \n\n\n");
                     color(15,0);
                     
                     printf("\t\t [1] . Afficher le conjoint d'une personne \n\n");
                     printf("\t\t [2] . Declaration de mariage \n\n");
                     printf("\t\t [3] . Declaration de divorce \n\n");
                     printf("\t\t [4] . Imprimer l'acte du mariage \n\n");
                     color(11,0);
                     printf("\t\t [5] . Revenir au menu principal.\n\n");
                     printf("\t\t [6] . Quitter.\n\n\n");
                     color(15,0);

                     color(14,0);
					 printf("\t -- Faites votre choix : ");
                     scanf("%d",&choixMenu);
                     color(15,0);


			         switch(choixMenu)
			         {
					    case 1 :
                                    system("cls");
                                    
                                    color(11,0);
                                    printf("\n\n - - - - - - - - - - - CONJOINT D'UNE PERSONNE - - - - - - - - - - - - \n\n");
                                    color(15,0);
                                    
                                    
                                    printf("\n - Saisissez l'identifiant d'une personne : ");
                                    do{
									
	                                      scanf("%d",&id);
	                                      
	                                      p = chercherPersonneById(listeP,id);
	                                      
	                                      if(!p) printf("\n - Saisissez un autre : ");
	                                      
	                                  }while( !p );
	                                
	                                afficherConjoint(listeP,p);
	                
                                    getch();
                                    break;
                                    


					    case 2 :
                                    system("cls");
                                    
                                    color(11,0);
                                    printf("\n\n - - - - - - -  - - - - DECLARATION DE MARIAGE - - - - - - - -  - - - - \n\n");
                                    color(15,0);
                                    
                                    
                                    printf("\n - Saisissez l'identifiant d'une personne : ");
                                    do{
									
	                                    scanf("%d",&id);
	                                      
	                                    p = chercherPersonneById(listeP,id);
	                                     
	                                    if( !p ) 
		                                {
		                                	color(7,0);
		                                	printf("\n  - Id n'existe pas -");
		                                	color(15,0);
											printf(" Saisissez un autre : ");

										}
										else
										{
											if( p->data->deces == 1 )
											{
											    color(7,0);
		                                		printf("\n  - La personne est morte -");
		                                		color(15,0);
												printf(" Saisissez un autre : ");	
											}
										} 
	                                      
	                                  }while( !p || ( p!=NULL && p->data->deces == 1 ) );
	                                
	                                
	                                printf("\n - Saisissez l'identifiant de son conjoint : ");
                                    do{
									
	                                    scanf("%d",&idConj);
	                                      
	                                    p = chercherPersonneById(listeP,idConj);
	                                      
	                                    if( !p ) 
		                                {
		                                	color(7,0);
		                                	printf("\n  - Id n'existe pas -");
		                                	color(15,0);
											printf(" Saisissez un autre : ");

										}
										else
										{
											if( p->data->deces == 1 )
											{
											    color(7,0);
		                                		printf("\n  - La personne est morte -");
		                                		color(15,0);
												printf(" Saisissez un autre : ");	
											}
										} 
	                                      
	                                  }while( !p || ( p!=NULL && p->data->deces == 1 ) );
	                                
	                               

	                               
	                                marier(listeP,id,idConj);

	                                
                                    getch();
                                    break;
                                    
                        case 3 :
						            
									system("cls");
                                    
                                    color(11,0);
                                    printf("\n\n - - - - - - -  - - - - DECLARATION DE DIVORCE - - - - - - - -  - - - - \n\n");
                                    color(15,0);
                                    
                                  	printf("\n - Saisissez l'identifiant d'une personne : ");
                                    do{
									
	                                    scanf("%d",&id);
	                                      
	                                    p = chercherPersonneById(listeP,id);
	                                      
	                                    if( !p ) 
		                                {
		                                	color(7,0);
		                                	printf("\n  - Id n'existe pas -");
		                                	color(15,0);
											printf(" Saisissez un autre : ");

										}
	                                      
	                                  }while( !p );
	                                
	                                
	                                printf("\n - Saisissez l'identifiant de son conjoint : ");
                                    do{
									
	                                    scanf("%d",&idConj);
	                                      
	                                    p = chercherPersonneById(listeP,idConj);
	                                      
	                                    if( !p ) 
		                                {
		                                	color(7,0);
		                                	printf("\n  - Id n'existe pas -");
		                                	color(15,0);
											printf(" Saisissez un autre : ");

										}
	                                      
	                                  }while( !p );

	                               
	                                divorcer(listeP,id,idConj);

	                                
                                    getch();
                                    break;

                        case 4 :
                                    system("cls");
                                    
                                    color(11,0);
                                    printf("\n\n - - - -  - - - - - - - - -   IMPRIMER ACTE DE MARIAGE   - - - - - - - - - - - - \n\n");
                                    color(15,0);
                                    
                                    printf("\n - Saisissez l'identifiant d'une personne : ");
                                    do{
									
	                                    scanf("%d",&id);
	                                      
	                                    p = chercherPersonneById(listeP,id);
	                                      
	                                    if( !p ) 
		                                {
		                                	color(7,0);
		                                	printf("\n  - Id n'existe pas -");
		                                	color(15,0);
											printf(" Saisissez un autre : ");

										}
	                                      
	                                  }while( !p );
				                    
				                    acteMariage(listeP,p);
				                    
				                    
				                    getch();
                                    break;
                                    
                        case 5 :
                        	        //Revenir au menu principal
                        	        
                        	        break;
                        	        
						case 6 :    
						            //Quitter
     	     
                                    sauvegarder( listeP,nbrePersonne);
   		                            exit(0);
						        
                                    break;
									        
                                    

						default:
							    color(7,0);
                                printf("\n\n\t\t/!\\ Votre choix est invalid /!\\\n\n");
                                color(15,0);
                                getch();


		            }




              }while( choixMenu != 5 );



              break;
			 
	    case 4:
	   	        //Gestion du deces
	 	
	 	
	 	
	 	        do{
                     system("cls");

                     color(11,0);
                     printf("\n - - - - - - - - - - G E S T I O N   D U   D E C E S - - - - - - - - - - - \n\n\n");
                     color(15,0);
                     
                     printf("\t\t [1] . Declaration de deces \n\n");
                     printf("\t\t [2] . Imprimer l'acte de deces \n\n");
                     color(11,0);
                     printf("\t\t [3] . Revenir au menu principal.\n\n");
                     printf("\t\t [4] . Quitter.\n\n\n");
                     color(15,0);
                     

                     color(14,0);
					 printf("\t -- Faites votre choix : ");
                     scanf("%d",&choixMenu);
                     color(15,0);


			         switch(choixMenu)
			         {
			
					    case 1 :
                                    system("cls");
                                    
                                    color(11,0);
                                    printf("\n\n - - - - - - -  - - - - DECLARATION DE DECES - - - - - - - -  - - - - \n\n");
                                    color(15,0);
                                    
                                    
                                    printf("\n - Saisissez l'identifiant de personne : ");
                                    do{
									
	                                    scanf("%d",&id);
	                                      
	                                    p = chercherPersonneById(listeP,id);
	                                      
	                                    if( !p ) 
		                                {
		                                	color(7,0);
		                                	printf("\n  - Id n'existe pas -");
		                                	color(15,0);
											printf(" Saisissez un autre : ");

										}
	                                      
	                                  }while( !p );
	                                
	                               
	                                p->data->deces = 1;
	                                
	                                color(7,0);
	                                printf("\n\n- Votre declaration a etait bien effectuer.\n\n");
	                                color(15,0);
	                                
                                    getch();
                                    break;
                                    
                        case 2 :
                                    system("cls");
                                    
                                    color(11,0);
                                    printf("\n\n - - - -  - - - - - - - - -   IMPRIMER ACTES DE DECES   - - - - - - - - - - - - \n\n");
                                    color(15,0);
                                    
                                    
                                    printf("\n - Saisissez l'identifiant de personne : ");
                                    do{
									
	                                    scanf("%d",&id);
	                                      
	                                    p = chercherPersonneById(listeP,id);
	                                      
	                                    if( !p ) 
		                                {
		                                	color(7,0);
		                                	printf("\n  - Id n'existe pas -");
		                                	color(15,0);
											printf(" Saisissez un autre : ");

										}
	                                      
	                                  }while( !p );
	                                  
	                                  
	                               
	                                if( !p->data->deces ) printf("\n\n- Impossible de delivrer cet acte, cette personne est encore vivante !\n\n");
									  else
									  {
									  	acteDeces(listeP,p);
									  }
				                    
				                    
				                    
				                    getch();
                                    break;
                                    
                        case 3 :
                        	        //Revenir au menu principal
                        	        
                        	        break;
                        	        
						case 4 :    
						            //Quitter
     	     
                                    sauvegarder( listeP,nbrePersonne);
   		                            exit(0);
						        
                                    break;          
                                    

						default:
							    color(7,0);
                                printf("\n\n\t/!\\ Votre choix est invalid /!\\\n\n");
                                color(15,0);
                                getch();


		            }




              }while( choixMenu != 3 );



              break;
	     
		            

		       
        case 5:
     	       //Quitter
     	     
               sauvegarder( listeP,nbrePersonne);
   		       exit(0);
     
		       
        default :
     	
                color(7,0);
                printf("\n\n\t\t/!\\ Votre choix est invalid /!\\\n\n");
                color(15,0);
                getch();

       }



    }while( choixMenuP != 5 );

    break;



case 2 : //L'authentification en tant que citoyen:
		
	do{
		   	
	    color(15,4);
		   
	    do 
        {
            system("cls");
            printf("\n\n\t\t\t    AUTHENTIFICATION\n\n");
            printf("\t\t--------------------------------------\n");

            printf("\n\t\t| Identifiant : "); scanf("%d",&id);
            printf("\n\t\t| Nom : "); fflush(stdin); scanf("%s",&loginNom);
            printf("\n\t\t| Prenom : "); fflush(stdin); scanf("%s",&login);
                
             //Nom et Prenom en Maj:    
            uppercase(loginNom);
            uppercase(login);
                
             //Vérifier si la personne existe ou pas:   
            p = chercherPersonneById(listeP,id);
                
             //Vérifier le nom et prénom:
            if( !p )
            {
                continu = 0;
			}
			else
			{ 
				strcpy(prenom,p->data->prenom);
                uppercase(prenom);
				
				//Vérifier le nom et le prénom:
				if( strcmp(p->data->nom,loginNom ) != 0 || strcmp( prenom,login ) != 0 )
                {
            		continu = 0;
            	}
            	else
            	{
				   continu = 1;
				}
			}
                 
        }while( !continu );


        system("COLOR 0F");
             
        do{ 

            //L'espace citoyen:
            do{
				
                system("cls");
                 
                 if(id%10 == 1)
                 {
                 	printf("\n  Bienvenue MR.");
                 	
				 }else{
				 	      printf("\n  Bienvenue Mme.");
				      }
                 
                 printf(" %s %s ",loginNom,login);
                 color(11,0);
                 printf("\t\t\t\t << Espace Citoyen >>  \n\n");
                 color(15,0);
                
				 
                 menuCitoyen();

                
                 color(14,0);
                 printf("\t -- Faites votre choix : ");
                 scanf("%d",&choixMenu);
                 color(15,0);

            }while(choixMenu != 1 && choixMenu != 2 && choixMenu != 3 && choixMenu != 4 && choixMenu != 5); 


            switch(choixMenu)
            {
                case 1: 
                     	         //Acte de naissance:

                                    system("cls");
                                    
                                    color(11,0);
                                    printf("\n\n - - - -  - - - - - - - - - IMPRIMER ACTE DE NAISSANCE - - - - - - - - - - - - \n\n");
                                    color(15,0);
                                    
                                    printf("\n - Saisissez votre identifiant : ");
                                    do{
									
	                                      scanf("%d",&idP);
	                                      
	                                      if( id != idP) 
										  {
										  	color(7,0);
										  	printf("\n - Ce n'est pas votre id :");
											color(15,0);
											printf(" Saisissez un autre :: ");
											
										  }
	                                      
	                                }while( id != idP );
				                    
				                    printPersonne(listeP,id);
				                    
				                    getch();
				                    break;
				                    
				case 2 :
					             //Acte du mariage:
					             
					             system("cls");
                                    
                                    color(11,0);
                                    printf("\n\n - - - -  - - - - - - - - -   IMPRIMER ACTE DE MARIAGE   - - - - - - - - - - - - \n\n");
                                    color(15,0);
                                    
                                    printf("\n - Saisissez votre identifiant : ");
                                    do{
									 
	                                    scanf("%d",&idP);
	                                      
	                                    if( id != idP) 
										{
										  	color(7,0);
										  	printf("\n - Ce n'est pas votre id :");
											color(15,0);
											printf(" Saisissez un autre :: ");
											
										}
	                                      
	                                }while( id != idP );
	                                
	                                p = chercherPersonneById(listeP,idP);
				                    
				                    acteMariage(listeP,p);
				                    
				                    
				                    getch();
                                    break;
                                    
                case 3 :
					            //Acte de deces:
								
								
                                do
								{
									
																	
								    system("cls");
                                    
                                    color(11,0);
                                    printf("\n\n - - - -  - - - - - - - - -   IMPRIMER ACTE DE DECES   - - - - - - - - - - - - \n\n");
                                    color(15,0);
                                    
                        
                                
                                    printf("\n\t\t [1].Acte de deces du Pere  \n");
                                    printf("\n\t\t [2].Acte de deces de la mere  \n");
                                    printf("\n\t\t [3].Acte de deces du Conjoint  \n\n");

                                    color(14,0);
                                    printf("\n - Faites votre choix : ");
                                    scanf("%d",&choixSearch);
                                    color(15,0);

                                }while( choixSearch != 1 && choixSearch != 2 && choixSearch != 3 );

                                    
                                    
                                printf("\n\n - Saisissez son identifiant : ");
                                    
	                            scanf("%d",&idP);
	                                      
	                            deces(listeP,id,idP,choixSearch); 
				                    
				                
                                break;                
                                    
                case 4 :              
					            //Quitter le menu 
					            break;
					            
					            
				case 5:
     	                       //Quitter
     	     
                               sauvegarder( listeP,nbrePersonne);
   		                       exit(0);           
     	     
   		                        
   		                        
   		                        
   		        default :
                                color(7,0);
                                printf("\n\n\t\t/!\\ Votre choix est invalid /!\\\n\n");
                                color(15,0);
                                getch();

            }  



              }while( choixMenu != 4 );
              
            }while( choixMenu = 4 );
              

              break;
					             
					             
					            
	
case 3 :		
		//Quitter
        sauvegarder( listeP,nbrePersonne);
   		exit(0);
   		     
   		     
default:
		color(7,0);
        printf("\n\n\t/!\\ Votre choix est invalid /!\\\n\n");
        color(15,0);
        getch();		     
	
	
		
}



/* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */

   sauvegarder( listeP,nbrePersonne);

/* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */



    getch();
}
