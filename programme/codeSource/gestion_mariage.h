



/***************************************************/
/* Vérifier la différance du sexe de deux personnes*/
/***************************************************/

int isDiffGender(int id, int idConj);



/***************************************/
/* Afficher le conjoint d'une personne */
/***************************************/


void afficherConjoint(listePersonne debut, listePersonne p);


/*************************/
/* Marier deux personnes */
/*************************/

void marier(listePersonne debut, int id, int idConj);



/***************************/
/* Divorcer deux personnes */
/***************************/

void divorcer(listePersonne debut, int id, int idConj);


/******************************/
/* Imprimer acte de mariage   */
/******************************/


void acteMariage(listePersonne debut,listePersonne p);
