#include "planning.h"


#include <iostream>
Planning::Planning(Foyer* foyer) : m_liste_AppareilsContraints(foyer->getListeAppCont()), m_contrainteGlobale(foyer->getContGlob()), m_tableauConso(95,0)
{
    m_score = 0;

    // Appel de l'optimisation
    optimiser();
}

//Getteur
double Planning::getScore(){return m_score;}
vector <double> Planning::getTabConso(){return m_tableauConso;}


//Etat de base
void Planning::etatBase()
{
    //Etape 1 : debut fonctionnement = debut de plage
    for (int i(0);i<this->m_liste_AppareilsContraints.size(); i++)
    {
        //Initialisation de debut de fonctionnement
        m_liste_AppareilsContraints[i]->setDebutFct(m_liste_AppareilsContraints[i]->getTpsDebut());
        //Initialisation de la fin de fonctionnement
        m_liste_AppareilsContraints[i]->setFinFct();
    }
}


//Optimisation
void Planning::optimiser()
{
    //Etat de base
    etatBase();

    //score de l'etat de base
    m_score = score(m_liste_AppareilsContraints);

    // Appelle l'algorithme
    Algorithme();
}


void Planning::Algorithme()
{
    //Copie de la liste d'appareil dans une liste temporaire
    vector<AppareilContraint*> liste_temporaire;
    for (int q(0); q < m_liste_AppareilsContraints.size(); q++)
    {
        AppareilContraint* app = new AppareilContraint(*m_liste_AppareilsContraints[q]);
        app->setDebutFct(0);
        app->setFinFct();
        liste_temporaire.push_back(app);
    }


    // Déclaration des variables utiles à l'optimisation
    double scoreTemp;
    bool continuer = true;
    double ancienScore(0);


    // Cette boucle va être parcourue tant que le meilleur scores enregistré à la fin n'est pas égal deux fois de suite
    do{

        // Cette boucle va permettre d'accéder à chacun des appareils contraints
        for(int i(0); i<liste_temporaire.size(); i++)
        {

            // Cette boucle va permettre de vérifier le score pour chacun des quarts d'heure
            // de sa contrainte d'utilisation et d'enregistrer sa meilleure valeur dans m_liste_AppareilsContraints
            for(int j = liste_temporaire[i]->getTpsDebut(); j<(liste_temporaire[i]->getTpsFin()-liste_temporaire[i]->getTpsDuree()+1); j++)
            {

                // Fixe le temps de début de fonctionnement au début de la contrainte
                liste_temporaire[i]->setDebutFct(j);
                liste_temporaire[i]->setFinFct();

                // Calcul le score du nouveau planning
                scoreTemp = score(liste_temporaire);


                // Si le score est meilleur, le planning et le score sont enregistrés
                if (m_score > scoreTemp) {

                    m_score=scoreTemp;

                    int debut = liste_temporaire[i]->getDebutFct();
                    m_liste_AppareilsContraints[i]->setDebutFct(debut);

                    m_liste_AppareilsContraints[i]->setFinFct();
                }
            }

            // Enregistre la meilleure position pour l'appareil dans le vecteur temporaire pour la suite de l'optimisation
            liste_temporaire[i]->setDebutFct(m_liste_AppareilsContraints[i]->getDebutFct());
            liste_temporaire[i]->setFinFct();
        }

        // Condition d'arret de notre boucle : elle s'arrête si le meilleur score ne change pas
        if(ancienScore == m_score)
        {
            continuer = false;
        } else {
            ancienScore = m_score;
        }
    } while (continuer);


    // Calcule du score finale, avec le tableau de la consommation pour chaque quart d'heure
    m_score = score(m_liste_AppareilsContraints);
}



double Planning::score(vector<AppareilContraint *> liste){

    double score(0);
    // Réinitialise le tableau de consommation à zero
    for(int i(0); i<m_tableauConso.size(); i++){
        this->m_tableauConso[i] = 0;
    }

    //on recupere la fichier appareil pour pouvoir obtenir les consomations des appareils à partir de leur ID
    FichierAppareils fichier("appareils.txt");

        // Cette boucle va parcourir tous les appareils contraints
        for(int j(0); j<liste.size(); j++)
        {
            // Récuperation de l'Id correspondant a l'appareilContraint
            int idTemp = liste[j]->getId();

            // Récupère l'appareil avec l'id correspondante
            Appareil* appTemp = fichier.getAppById(idTemp);


            // Cette boucle rempli le tableau de consommation et calcul le score
            for(int k(liste[j]->getDebutFct()); k<=liste[j]->getFinFct(); k++)
            {
                this->m_tableauConso[k] += (appTemp->getConso());

                double temp = pow(this->m_tableauConso[k]/1500,2);


                // Si la consommation dépasse la contrainte globale, le score est fortement pénalisé
                if(temp > m_contrainteGlobale->getContGlob()){
                    temp += pow(m_contrainteGlobale->getContGlob()*96/1500,2);
                }
                score += temp;
            }
        }
     return score;
}

