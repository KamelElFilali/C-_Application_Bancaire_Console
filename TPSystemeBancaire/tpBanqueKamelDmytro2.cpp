#include <iostream>
#include <iomanip>
#include<stdlib.h>
#include<string>
#include<math.h>
#include <conio.h>
#include "Windows.h"
//#include <"RockUtiles.h">
#define NULL 0
using namespace std;

const unsigned short TAILLE_NOM = 31;
const unsigned short TAILLE_PRENOM = 31;

struct compte
{
	unsigned int noCompte;
	char nom[TAILLE_NOM];
	char prenom[TAILLE_PRENOM];
	double solde;
	bool actif;
};

enum TypeTransaction
{
	DEPOT,
	RETRAIT
};

enum TypeDeTri
{
	NO_COMPTE,
	NOM,
	PRENOM,
	SOLDE
};

enum OrdreDeTri
{
	ASCENDANT,
	DESCENDANT
};

//Prototypes des Fonctions
void afficherMenu(compte comptes[], unsigned int nbComptes);

void ajouterCompte(compte comptes[], unsigned int& nbComptesActuels);
void desactiverCompte(compte comptes[], unsigned int indice);

double calculerSommeSoldes(compte comptes[], unsigned int nbComptes);

unsigned int recupererNombreCompteActif(compte comptes[], unsigned int nbComptes);

void afficherSoldeMoyen(compte comptes[], unsigned int nbComptes);
void afficherSommeSoldes(compte comptes[], unsigned int nbComptes);
int rechercherClient(compte comptes[], unsigned int nbComptes);
void afficherComptes(compte comptes[], unsigned int nbComptes);
void afficherCompte(compte compte);

void effectuerTransaction(TypeTransaction typeTransaction, compte &compte, double montant);
void effectuerDepot(compte &compte, double montant);
void effectuerRetrait(compte &compte, double montant);

int saisieTypeTrie();
int saisieOrdreTrie();
void trierComptes(TypeDeTri typeDeTri, OrdreDeTri ordreDeTri, compte comptes[], unsigned int nbComptes);
void echanger(compte &compte1, compte &compte2);
double validationNum();


int main()
{
	setlocale(LC_ALL, "");
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO *ConsoleInfo = new CONSOLE_SCREEN_BUFFER_INFO();
	GetConsoleScreenBufferInfo(hConsoleHandle, ConsoleInfo);
	WORD OriginalColors = ConsoleInfo->wAttributes;
	/*SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN);*/
	/*SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_INTENSITY);*/
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 262 /*31*/);
	BOOL WINAPI SetConsoleScreenBufferSize
	(
		_In_ HANDLE hConsoleOutput,
		_In_ COORD  dwSize
	);

	compte comptes[1000];
	unsigned int nombreDeCompteActuel = 0;

	afficherMenu(comptes, nombreDeCompteActuel);
	
	system("pause");
	return 0;
}

void afficherMenu(compte comptes[], unsigned int nbComptes)
{
	/*
	Tâche : afficher le menu principal
	paramètres : comptes : représente la liste complète des comptes dans l'application
	nbComptes : représente le nombre de comptes dans l'application en ce moment
	*/

	int choix;
	unsigned int nombreDeCompteActuel = 0;
	double montant = 0;
	unsigned int indiceNumCompte=0;
	TypeDeTri choixTypeTri[] = {NO_COMPTE,NOM,PRENOM,SOLDE };
	OrdreDeTri choixOrdreDeTri[] = { ASCENDANT,DESCENDANT };
	
	do // fait ce programme
	{
		cout << "                         *************************************************** " << endl << endl;
		cout << "                                                RBC                          " << endl << endl;
		cout << "                                APLLICATION BANQUAIRE MENU PRINCIPAL         " << endl << endl;
		cout << "                         *************************************************** " << endl << endl;

		cout << "			1 - Ajouter un compte de la Banque" << endl;
		cout << "			2 - Retirer un compte de la banque" << endl;
		cout << "			3 - Afficher l'information d'un compte client en particulier (par numero de compte)" << endl;
		cout << "			4 - Effectuer un depot dans un compte en particulier (par numero de compte)" << endl;
		cout << "			5 - Effectuer un retrait dans un compte en particulier (par numero de compte)" << endl;
		cout << "			6 - Trier et afficher la liste des clients" << endl;
		cout << "			7 - Afficher la somme total de tout les comptes" << endl;
		cout << "			8 - Afficher le solde moyen des comptes" << endl;
		cout << "			9 - Quitter l'application" << endl << endl;

		cout << "			Entrez votre choix (1-9) : " <<endl <<endl;
							choix = validationNum();
							system("cls");
							
		switch (choix)
		{
		case 1:
			ajouterCompte(comptes, nombreDeCompteActuel);
			break;
		case 2:
			desactiverCompte(comptes, indiceNumCompte);
			break;
		case 3:
			afficherComptes(comptes, nombreDeCompteActuel);
			break;
		case 4:
			effectuerTransaction(TypeTransaction::DEPOT, comptes[indiceNumCompte], montant);
			break;
		case 5:
			effectuerTransaction(TypeTransaction::RETRAIT, comptes[indiceNumCompte], montant);
			break;
		case 6:
			trierComptes(choixTypeTri[saisieTypeTrie()], choixOrdreDeTri[saisieOrdreTrie()], comptes, nombreDeCompteActuel);
			break;
		case 7:
			afficherSommeSoldes(comptes, nombreDeCompteActuel);
			break;
		case 8:
			afficherSoldeMoyen(comptes, nombreDeCompteActuel);
			break;
		case 9:
			break;
		}
	} while (choix != 9); // tant le choix n'est pas 9

}

void ajouterCompte(compte comptes[], unsigned int& nbComptesActuels)
{
	/*
	Tâche : ajouter un compte
	Paramètres : comptes : représente la liste complète des comptes dans l'application
	nbComptes : représente le nombre de comptes dans l'application en ce moment

	*/

	cout << "			************************************************************************** " << endl << endl;
	cout << "			Veuillez entrer les informations suivantes pour ajouter un nouveau compte    " << endl << endl;
	cout << "			************************************************************************** " << endl << endl;
	
	cout << "			Numero de compte : ";
	comptes[nbComptesActuels].noCompte = validationNum();
	cout << "			Nom du Client : ";
	cin.ignore();
	cin.getline(comptes[nbComptesActuels].nom, 31);
	cout << "			Prenom du Client : ";
	cin.ignore();
	cin.getline(comptes[nbComptesActuels].prenom, 31);
	cout << "			Solde du compte : ";
	comptes[nbComptesActuels].solde = validationNum();
	cout << endl;
	if (comptes[nbComptesActuels].solde > 0)
	{
		comptes[nbComptesActuels].actif = true;
		cout << "			Le Compte numero : " << comptes[nbComptesActuels].noCompte << " est Activer " << endl << endl;
	}
	else
	{
		comptes[nbComptesActuels].actif = false;
		cout << "			Pour le moment le compte numero : " << comptes[nbComptesActuels].noCompte << " est Desactiver " << endl << endl;
	}
	nbComptesActuels++;
}

void afficherCompte(compte compte)
{
	/*
	Tâche : affiche les informations d'un seul compte.
	Paramètres : compte : représente le compte d'un seul client
	*/

	cout << "			*********************************\n";
	cout << "			Voici les informations Du Compte " << endl;
	cout <<	"			*********************************" << endl << endl;

	cout << "			- - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << "			| Numero de compte : " << compte.noCompte		 << endl;
	cout << "			| Nom du client : " << compte.nom				 << endl;
	cout << "			| Prenom du client : " << compte.prenom			 << endl;
	cout << "			| Solde : " << compte.solde << " $"			     << endl;
	if (compte.solde > 0)
	{
		compte.actif = true;
	cout << "			Statut du Compte : Activer " << endl;
	}
	else
	{
		compte.actif = false;
	cout << "			Statut du Compte : Desactiver " << endl;
	}
	cout << "			- - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << endl;

}

void afficherComptes(compte comptes[], unsigned int nbComptes)
{
	/*
	Tâche : affiche les informations de toutes les comptes actifs.
	Paramètres : comptes : représente la liste complète des comptes dans l'application
	nbComptes : représente le nombre de comptes saisies dans l'application en ce moment
	*/

	for (int i = 0; i < comptes->noCompte ; i++)
	{

		if (comptes->solde > 0)
		{
			afficherCompte(comptes[i]);
		}
	}
}


void desactiverCompte(compte comptes[], unsigned int indice)
{/*
 Tâche : désactiver un compte si son solde est 0, sinon afficher un message
 Paramètres : comptes : représente la liste complète des comptes dans l'application
nbComptes : représente le nombre de comptes dans l'application en ce moment
*/
	unsigned int nbCompte = 0;

	for (int i = 0; i < comptes->noCompte; i++)
	{
		if (rechercherClient(comptes, nbCompte) == comptes->noCompte)
		{
			comptes->solde = 0;
			cout << "	Le compte numero " << comptes->noCompte << " a bien ete desactiver son solde est a 0 "  << endl <<endl;

			cout << "			*********************************\n";
			cout << "			 Voici les informations Du Compte " << endl;
			cout << "			*********************************" << endl << endl;

			cout << "			- - - - - - - - - - - - - - - - - - - - - - - -" << endl;
			cout << "			| Numero de compte : " << comptes->noCompte << endl;
			cout << "			| Nom du client : " << comptes->nom << endl;
			cout << "			| Prenom du client : " << comptes->prenom << endl;
			cout << "			| Solde : " << comptes->solde << " $" << endl;
			cout << "			- - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;

			return;
		}
		
	}

}

int rechercherClient(compte comptes[], unsigned int nbComptes)
{
	/*
	Tâche : demander un numéro de compte et rechercher un compte actif en fonction du numéro de client saisie. Affiche "Compte inexistant" et retourne -1 si le compte
	est inexistant, sinon retourne l'indice dans le tableau ou se trouve le compte.
	Paramètres : comptes : représente la liste complète des comptes dans l'application
	nbComptes : représente le nombre de comptes saisies dans l'application en ce moment
	*/
	//unsigned int numeroCompte;
	unsigned int compteExistant = 0;
	
	for (int i = 0; i < comptes->noCompte; i++)
	{
		cout << "ENTREZ VOTRE NUMERO DE COMPTE EXISTANT : ";
		cin >> comptes->noCompte;
		cout << endl << endl;

		if (comptes->noCompte != comptes[i].noCompte)
		{
			compteExistant = -1;
			cout << "Le Compte N'Existe pas " << endl << endl;
		}
		else
		{
			/*compteExistant++;*/
			return comptes[i].noCompte;
		}
		
	}

}


double calculerSommeSoldes(compte comptes[], unsigned int nbComptes)
{
	/*
	Tâche : calculer la somme de toutes les comptes actifs
	Paramètres : comptes : représente la liste complète des comptes dans l'application
	nbComptes : représente le nombre de comptes saisies dans l'application en ce moment
	*/

	double sommeSoldes = 0;
	for (int i = 0; i < comptes->noCompte; i++)
	{
		sommeSoldes += comptes[i].solde;
	}
	return sommeSoldes;
}

void afficherSommeSoldes(compte comptes[], unsigned int nbComptes)
{
	/*
	Tâche : afficher la somme de toutes les comptes actifs
	Paramètres : comptes : représente la liste complète des comptes dans l'application
	nbComptes : représente le nombre de comptes saisies dans l'application en ce moment
	*/
	cout << "			Voici la somme TOTAL des comptes : " << calculerSommeSoldes(comptes, nbComptes) << endl << endl;

}

unsigned int recupererNombreCompteActif(compte comptes[], unsigned int nbComptes)
{
	/*
	Tâche : récupérer le nombre total de comptes actifs
	Paramètres : comptes : représente la liste complète des comptes dans l'application
	nbComptes : représente le nombre de comptes saisies dans l'application en ce moment
	*/

	for (int i = 0; i < comptes->solde > 0; i++)
	{

		if (comptes[i].solde > 0)
		{

			nbComptes++;
		}
	}
	cout << nbComptes << endl;

	return nbComptes;

}

void afficherSoldeMoyen(compte comptes[], unsigned int nbComptes)
{
	/*
	Tâche : affcher la moyenne des soldes de toutes les comptes actifs
	Paramètres : comptes : représente la liste complète des comptes dans l'application
	nbComptes : représente le nombre de comptes saisies dans l'application en ce moment*/

	cout << "			Voici la somme MOYENNE des comptes : " << calculerSommeSoldes(comptes, nbComptes) / nbComptes << endl << endl;

}

void effectuerTransaction(TypeTransaction typeTransaction, compte &compte, double montant)
{
	/*
	Tâche : effectuer une transaction bancaire sur un compte en fonction d'un type de transaction et d'un montant
	Paramètres : typeTransaction : le type de transaction effectué
	compte : représente le compte d'un client
	montant : le montant de la transaction

	*/
	unsigned int nbCompte = 0;

	if (rechercherClient(&compte, nbCompte) == compte.noCompte)
	{
		cout << "			**************************************" << endl;
		cout << "			             TRANSACTION"               << endl;
		cout << "			**************************************" << endl << endl;

		cout << "			             BIENVENUE " << compte.prenom << endl << endl;

		if (typeTransaction == RETRAIT)
		{
			effectuerRetrait(compte, montant);

		}
		else if (typeTransaction == DEPOT)
		{
			effectuerDepot(compte, montant);
		}

	}

}

void effectuerDepot(compte &compte, double montant)
{
	/*
	Tâche : affectuer un dépot dans le compte d'un client.
	Paramètres : compte : représente le compte d'un client
	montant : le montant de la transaction
	*/
	char choix = 'o';
	
	cout << "			*********************************" << endl;
	cout << "			         DEPOT D'ARGENT"           << endl;
	cout << "			*********************************" << endl << endl;

	do
	{

		cout << "		ENTREZ LE MONTANT A DEPOSER: \n ";
		montant = validationNum();
		cout << endl << endl;

		cout << "		Voici le Montant que vous souhaitez Deposer : " << montant << "\n Est ce le Bon? (o-n) : " << endl;
		cin >> choix;
		cout << endl;

		if (choix == 'o')
		{
			compte.solde = compte.solde + montant;

			cout << fixed << setprecision(2) << "			Votre Nouveau Solde est " << compte.solde << endl << endl;

			cout << "			*********************************\n";
			cout << "			 Voici les informations Du Compte " << endl;
			cout << "			*********************************" << endl << endl;

			cout << "			- - - - - - - - - - - - - - - - - - - - - - - -" << endl;
			cout << "			| Numero de compte : " << compte.noCompte		 << endl;
			cout << "			| Nom du client : " << compte.nom				 <<  endl;
			cout << "			| Prenom du client : " << compte.prenom			 <<  endl;
			cout << "			| Solde : " << compte.solde << " $"				 << endl;
			cout << "			- - - - - - - - - - - - - - - - - - - - - - - -" << endl;

		}

	} while (choix != 'o');

}

void effectuerRetrait(compte &compte, double montant)
{
	/*
	Tâche : affectuer un retrait dans le compte d'un client.
	Paramètres : compte : représente le compte d'un client
	montant : le montant de la transaction
	*/

	char choix = 'o';

	cout << "			*********************************" << endl;
	cout << "			          RETRAIT D'ARGENT"        << endl;
	cout << "			*********************************" << endl << endl;

	do
	{
		cout << "			ENTREZ LE MONTANT A RETIRER : \n ";
		montant = validationNum();
		cout << endl << endl;

		cout << "			Voici le Montant que vous souhaitez Retirer : " << montant << "\n Est ce le Bon? (o-n) : " << endl;
		cin >> choix;
		cout << endl;

		if (choix == 'o')
		{
			if (compte.solde <= 0 || compte.solde < montant)
			{

				cout << "			*********************************************\n";
				cout << "			 SOLDE INSUFFISANT POUR EFFECTUER UN RETRAIT " << endl;
				cout << "			*********************************************" << endl << endl;
				return;

			}
			else
			{
				compte.solde = compte.solde - montant;

				cout << fixed << setprecision(2) << "			Votre Nouveau Solde est " << compte.solde << endl << endl;

				cout << "			*********************************\n";
				cout << "			 Voici les informations Du Compte " << endl;
				cout << "			*********************************" << endl << endl;

				cout << "			- - - - - - - - - - - - - - - - - - - - - - - -" << endl;
				cout << "			| Numero de compte : " << compte.noCompte		 << endl;
				cout << "			| Nom du client : " << compte.nom				 << endl;
				cout << "			| Prenom du client : " << compte.prenom			 << endl;
				cout << "			| Solde : " << compte.solde << " $"			     << endl;
				cout << "			- - - - - - - - - - - - - - - - - - - - - - - -" << endl;
			}
		}

	} while (choix != 'o');

}

int saisieTypeTrie()
{
	int typeDetriSaisie;
	
	cout << "			Veuillez choisir le type de tri desiré : " << endl << endl;
	cout << "			0 - par Numéro de compte" << endl;
	cout << "			1 - par Prénom de clients" << endl;
	cout << "			2 - par Nom de clients" << endl;
	cout << "			3 - par Solde de compte" << endl;

	typeDetriSaisie = validationNum();
	
	return typeDetriSaisie;
}

int saisieOrdreTrie()
{

	int ordreDeTrieSaisie;

	cout << endl << endl;
	cout << "			Veuillez choisir le ordre de tri desiré : " << endl << endl;
	cout << "			0 - Ascendant" << endl;
	cout << "			1 - Descendant" << endl;
	ordreDeTrieSaisie = validationNum();

	return ordreDeTrieSaisie;

}

void trierComptes(TypeDeTri typeDeTri, OrdreDeTri ordreDeTri, compte comptes[], unsigned int nbComptes)
{
	/*Tâche : trier les comptes en fonction du mode de tri et de l'ordre de tri passés en paramètre.
	Paramètres : typeDeTri : le type de tri désiré
	ordreDeTri : l'ordre de tri désiré
	comptes : le tableau de toutes les comptes dans l'application
	nbComptes : représente le nombre de comptes saisies dans l'application en ce moment*/

	if (typeDeTri == 0 && ordreDeTri == 0) {
		unsigned int compteDeClients = 0;

		for (int i = 0; i < nbComptes; i++) {

			compteDeClients = i;

			for (unsigned int j = i + 1; j < nbComptes; j++) {
				if (comptes[j].noCompte < comptes[compteDeClients].noCompte)
				{
					compteDeClients = j;
				}
			}
			echanger(comptes[compteDeClients], comptes[i]);
		}
	}

	else if (typeDeTri == 0 && ordreDeTri == 1) {
		unsigned int compteDeClients = 0;

		for (int i = 0; i < nbComptes; i++) {

			compteDeClients = i;

			for (unsigned int j = i + 1; j < nbComptes; j++) {
				if (comptes[j].noCompte > comptes[compteDeClients].noCompte)
				{
					compteDeClients = j;
				}
			}
			echanger(comptes[compteDeClients], comptes[i]);
		}
	}


	else if (typeDeTri == 1 && ordreDeTri == 0) {
		unsigned int nomDeClients = 0;

		for (int i = 0; i < nbComptes; i++) {

			nomDeClients = i;

			for (unsigned int j = i + 1; j < nbComptes; j++) {

				if (strcmp(comptes[j].nom, comptes[nomDeClients].nom) == -1)
				{

					nomDeClients = j;
				}
			}
			echanger(comptes[nomDeClients], comptes[i]);
		}

	}

	else if (typeDeTri == 1 && ordreDeTri == 1) {
		unsigned int nomDeClients = 0;

		for (int i = 0; i < nbComptes; i++) {

			nomDeClients = i;

			for (unsigned int j = i + 1; j < nbComptes; j++) {
				//if (comptes[j].nom > comptes[nomDeClients].nom)
				if (strcmp(comptes[j].nom, comptes[nomDeClients].nom) == -1)
				{

					nomDeClients = j;
				}
			}
			echanger(comptes[nomDeClients], comptes[i]);
		}

	}
	else if (typeDeTri == 2 && ordreDeTri == 0) {
		unsigned int prenomDeClients = 0;

		for (int i = 0; i < nbComptes; i++) {

			prenomDeClients = i;

			for (unsigned int j = i + 1; j < nbComptes; j++) {
				if (comptes[j].prenom < comptes[prenomDeClients].prenom)
					if (strcmp(comptes[j].prenom, comptes[prenomDeClients].prenom) < NULL)
					{
						prenomDeClients = j;
					}
			}
			echanger(comptes[prenomDeClients], comptes[i]);
		}
	}
	else if (typeDeTri == 2 && ordreDeTri == 1) {
		unsigned int prenomDeClients = 0;

		for (int i = 0; i < nbComptes; i++) {

			prenomDeClients = i;

			for (unsigned int j = i + 1; j < nbComptes; j++) {
				if (comptes[j].prenom > comptes[prenomDeClients].prenom)
					if (strcmp(comptes[j].prenom, comptes[prenomDeClients].prenom) < NULL)
					{
						prenomDeClients = j;
					}
			}
			echanger(comptes[prenomDeClients], comptes[i]);
		}
	}

	else if (typeDeTri == 3 && ordreDeTri == 0)
	{
		unsigned int soldeDeClients = 0;

		for (int i = 0; i < nbComptes; i++) {

			soldeDeClients = i;

			for (unsigned int j = i + 1; j < nbComptes; j++) {
				if (comptes[j].solde < comptes[soldeDeClients].solde)
				{
					soldeDeClients = j;
				}
			}
			echanger(comptes[soldeDeClients], comptes[i]);
		}
	}
	else if (typeDeTri == 3 && ordreDeTri == 1)
	{
		unsigned int soldeDeClients = 0;

		for (int i = 0; i < nbComptes; i++) {

			soldeDeClients = i;

			for (unsigned int j = i + 1; j < nbComptes; j++) {
				if (comptes[j].solde > comptes[soldeDeClients].solde)
				{
					soldeDeClients = j;
				}
			}
			echanger(comptes[soldeDeClients], comptes[i]);
		}
	}

	afficherComptes(comptes, nbComptes);

}

void echanger(compte &compte1, compte &compte2)
{
	/*
	Tâche : échanger en mémoire le contenu de deux comptes
	Paramètres : compte1 et compte2 : représente les comptes à échanger
	*/
	
	compte temp = compte1;
	compte1 = compte2;
	compte2 = temp;
}

double validationNum() 
{

	double nombre;
	cin >> nombre;
	while (cin.fail() || cin.peek() != '\n') 
	{
		cin.clear();
		cin.ignore(512, '\n');
		cout << "Valeur numerique seulement : ";
		cin >> nombre;
	}
	cin.ignore(512, '\n');

	return nombre;
}
