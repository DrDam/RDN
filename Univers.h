#ifndef UNIVERS_H_INCLUDED
#define UNIVERS_H_INCLUDED
#include <vector>
#include "Organisme.h"

class Univers {

    //attributs
    private:
    std::vector<Organisme*> population ;// tableau qui contient les organismes �voluant dans l'univers

    //m�thodes
    public:
    Univers(int nb_org, int *T_reseau ) ; // cr�ation de l'univers � partir de rien
    Univers(char fichier) ; // cr�ation de l'univers � partir d'un fichier
    void run(); // et pourtant il tourne !!
    std::vector<Organisme*> getAllOrganisme();
};

#endif // UNIVERS_H_INCLUDED
