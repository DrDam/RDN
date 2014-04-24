#ifndef UNIVERS_H_INCLUDED
#define UNIVERS_H_INCLUDED
#include <vector>
#include "Organisme.h"

class Univers {

    //attributs
    private:
    std::vector<Organisme*> population ;// tableau qui contient les organismes évoluant dans l'univers

    //méthodes
    public:
    Univers(int nb_org, int *T_reseau ) ; // création de l'univers à partir de rien
    Univers(char fichier) ; // création de l'univers à partir d'un fichier
    void run(); // et pourtant il tourne !!
    std::vector<Organisme*> getAllOrganisme();
};

#endif // UNIVERS_H_INCLUDED
