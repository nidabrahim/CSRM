
#include "gestion_personne.h"

#include "gestion_mariage.h"




/***************************************************/
/* Vérifier la différance du sexe de deux personnes*/
/***************************************************/

int isDiffGender(int id, int idConj)
{
	//On peut déterminer le sexe d'une personne à partir de 1er nombre de son identifiant:
	
	return (id%10 != idConj%10) ;
}


/***************************************/
/* Afficher le conjoint d'une personne */
/***************************************/


void afficherConjoint(listePersonne debut, listePersonne p)
{
	 //Récuperer le conjoint:
	listePersonne person = chercherPersonneById(debut,p->data->idConjoint);
	
	if(!person)
	{
		printf("\n\n- Cette personne est celebataire, n'est pas encore marier.\n\n ");
	} 
	else  
	{
		//Afficher les informations du conjoint:
	   afficherPersonne(person);
	}
	 
}


/*************************/
/* Marier deux personnes */
/*************************/

void marier(listePersonne debut, int id, int idConj)
{
	listePersonne person = NULL;
	listePersonne conj = NULL;
	
	//Récuperer l'adresse de la personne:
	person = chercherPersonneById(debut,id);
	
	 //Récuperer l'adresse de son conjoint:
    conj = chercherPersonneById(debut,idConj);
    
     //Les deux personnes seront mariés s'elles ne sont pas encore mariés:
    if( person->data->idConjoint == -1 && conj->data->idConjoint == -1 && isDiffGender(id, idConj) )
    {
    	person->data->idConjoint = idConj;
    	conj->data->idConjoint = id;
    	
    	color(7,0);
    	printf("\n\n- Le mariage est bien effectue ! \n\n");
    	color(15,0);
    	
	}
	else
	{
		color(7,0);
		printf("\n\n- Impossible de marier ses deux personnes ! \n\n");
		color(15,0);
	}
    
}


/***************************/
/* Divorcer deux personnes */
/***************************/

void divorcer(listePersonne debut, int id, int idConj)
{
	listePersonne person = NULL;
	listePersonne conj = NULL;
	
	//Récuperer l'adresse de la personne:
	person = chercherPersonneById(debut,id);
	
	 //Récuperer l'adresse de son conjoint:
    conj = chercherPersonneById(debut,idConj);
    
     //Les deux personnes seront divorcés, s'elles sont déjà mariés:
    if( person->data->idConjoint == idConj && conj->data->idConjoint == id )
    {
    	person->data->idConjoint = -1;
    	conj->data->idConjoint = -1;
    	
    	color(7,0);
    	printf("\n\n- Le divorce est bien effectue ! \n\n");
    	color(15,0);
    	
	}
	else
	{   
	    color(7,0);
		printf("\n\n- Impossible de divorcer ses deux personnes ! elles ne sont pas marier ensemble \n\n");
		color(15,0);
	}
    
}



/******************************/
/* Imprimer acte de mariage   */
/******************************/


void acteMariage(listePersonne debut,listePersonne pers)
{
	
     listePersonne conj = NULL;
     listePersonne pere = NULL;
     listePersonne mere = NULL;
     date dateActuelle = DateActuelles();
     

	  //Son conjoint:
	 conj = chercherPersonneById(debut, pers->data->idConjoint);
	 
	 if( !conj ) printf("\n\n- Cette personne n'est encore mariés ! \n\n");
	 else
	 {
	 
	 
	  //Son pere:
	 pere = chercherPersonneById(debut, pers->data->idPere);
	 
	  //Sa mere:
	 mere = chercherPersonneById(debut, pers->data->idMere);
	 
	 
	 FILE *fiche;

     fiche = fopen("acteMariage.doc","wt");

     if(fiche == NULL) printf("erreur\n");
     else
     {

       fprintf(fiche,"\t\t\t\tEXTRAIT DE L'ACTE DE MARIAGE\n\n\n");

       
        //Le nom et le prenom de demandeur:
       if(pers->data->sexe == 'M')
       {
       	   fprintf(fiche,"\t -L'EPOUX :      %s  %s \n\n",pers->data->nom,pers->data->prenom);
	   }
	   else
	   {
	   	   fprintf(fiche,"\t -L'EPOUSE :      %s  %s \n\n",pers->data->nom,pers->data->prenom);
	   }

	   
	    //Sa date de naissance:
	   fprintf(fiche,"\t\t -DATE DE NAISSANCE :       %d / %d / %d \n\n",pers->data->dateNaissance.jour,pers->data->dateNaissance.mois,pers->data->dateNaissance.annee);


        //Si son pére est déjà inscrit ou pas:
	   if(pers->data->idPere != -1)
	      fprintf(fiche,"\t\t -PERE :       %s  %s \n\n",pere->data->nom,pere->data->prenom);
	      
	   else
          fprintf(fiche,"\t\t -PERE :       ( n'est pas inscrit ) \n\n");

          
         //Si sa mére est déjà inscrite ou pas: 
	   if(pers->data->idMere != -1)
          fprintf(fiche,"\t\t -MERE :       %s  %s \n\n",mere->data->nom,mere->data->prenom);
          
       else
          fprintf(fiche,"\t\t -MERE :       ( n'est pas inscrite ) \n\n");
          
       
	   //Le pere de conjoint:
	 pere = chercherPersonneById(debut, conj->data->idPere);
	 
	  //La mere de conjoint:
	 mere = chercherPersonneById(debut, conj->data->idMere);   
	 
	 
	  //Le nom et le prenom de conjoint:
       if(conj->data->sexe == 'M')
       {
       	   fprintf(fiche,"\n\t -L'EPOUX :      %s  %s \n\n",conj->data->nom,conj->data->prenom);
	   }
	   else
	   {
	   	   fprintf(fiche,"\n\t -L'EPOUSE :      %s  %s \n\n",conj->data->nom,conj->data->prenom);
	   }

	   
	    //Sa date de naissance:
	   fprintf(fiche,"\t\t -DATE DE NAISSANCE :       %d / %d / %d \n\n",conj->data->dateNaissance.jour,conj->data->dateNaissance.mois,conj->data->dateNaissance.annee);


        //Si son pére est déjà inscrit ou pas:
	   if(conj->data->idPere != -1)
	      fprintf(fiche,"\t\t -PERE :       %s  %s \n\n",pere->data->nom,pere->data->prenom);
	      
	   else
          fprintf(fiche,"\t\t -PERE :       ( n'est pas inscrit ) \n\n");

          
         //Si sa mére est déjà inscrite ou pas: 
	   if(conj->data->idMere != -1)
          fprintf(fiche,"\t\t -MERE :       %s  %s \n\n",mere->data->nom,mere->data->prenom);
          
       else
          fprintf(fiche,"\t\t -MERE :       ( n'est pas inscrite ) \n\n");
          
          
                   
       fprintf(fiche,"\n\n\n\n\t\t\t\t -DATE DE DELIVRANCE : %d / %d / %d \n\n",dateActuelle.jour,dateActuelle.mois,dateActuelle.annee);


       fclose(fiche);
       
       
       //Convertir l'acte en PDF:
       system("OfficeToPDF.exe acteMariage.doc actes/acteMariage.pdf ");
       system("del acteMariage.doc ");
       
       printf("\n\n - L'actes de mariage est bien imprime, vous pouvez le recuperer.\n\n");
       
   }


      }

}




























