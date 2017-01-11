#ifndef PLANNING_H
#define PLANNING_H
#include <vector>
#include <cmath>
#include "Foyer.h"
#include "FichierAppareils.h"

class Planning
{

public:
    Planning(Foyer* foyer);

    //Getteur
    double getScore();

    //Etat de base
    void etatBase();

    //Modifie la liste optimisee
    void optimiser();

    //Calcul du score
    double score(vector<AppareilContraint *> liste);
    vector <double>getTabConso();

    //Algorithme
    void Algorithme();


private:
    vector<AppareilContraint*> m_liste_AppareilsContraints;
    ContrainteGlobale* m_contrainteGlobale;

    double m_score;
    vector <double> m_tableauConso;
};

#endif // PLANNING_H
