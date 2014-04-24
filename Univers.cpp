#include <vector>
#include "Poisson.h"
#include "Univers.h"

// cr�er l'univers � partir de rien
Univers::Univers(int nb_org,int *T_reseau )
{
    for(int i=0;i<nb_org;i++)
    {
       population.push_back( new Poisson(T_reseau,600) );
    }
}

// cr�ation de l'univers � partir d'un fichier
Univers::Univers( char fichier ) {   }

void Univers::run() {
    //chaque organisme "vie"
    for ( unsigned int i(0);i<population.size();++i)
        {
            population[i]->run();
        }
}

// retourn le tableau des organismes
std::vector<Organisme*> Univers::getAllOrganisme()
 {
    return population;
 }