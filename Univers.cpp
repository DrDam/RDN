#include <vector>
#include "Poisson.h"
#include "Univers.h"
#include <omp.h>

// créer l'univers à partir de rien
Univers::Univers(int nb_org,int *T_reseau )
{
    #pragma omp parallel for
    for(int i=0;i<nb_org;i++)
    {
       population.push_back( new Poisson(T_reseau,600) );
    }
}

// création de l'univers à partir d'un fichier
Univers::Univers( char fichier ) {   }

void Univers::run() {
    //chaque organisme "vie"
    #pragma omp parallel for schedule(dynamic,2)
    for ( unsigned int i=0;i<population.size();++i)
        {
            population[i]->run();
        }
}

// retourn le tableau des organismes
std::vector<Organisme*> Univers::getAllOrganisme()
 {
    return population;
 }
