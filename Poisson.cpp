#include <vector>
#include "Organisme.h"
#include "Rdn/Reseau.h"
#include "Poisson.h"
#include "lib/alea/alea.h"

Poisson::Poisson(int *T_reseau, int max_ecran ):  Organisme::Organisme(T_reseau,50,4)
{
    x = 10+alea(max_ecran-20) ;
    y = 10+alea(max_ecran-20) ;
    TailleX = TailleY = max_ecran;
   // out1 = out2 = out3 = false ;
}

void Poisson::sentir()// interprete l'univers
{
    for(unsigned int i(0) ; i<SNC->T_Input.size() ; i++)    // pour chaque entrée du réseau
        {
            if(alea(10)>5) {   SNC->T_Input[i]->transmet( true );  } // si on est >5 sur un D10 , on active l'entré
        }
} ;
void Poisson::agir() // agit sur/avec l'univers
{
    // en attente
    int old_x = x;
    int old_y = y;

    // en attente d'organes moteurs
    for(unsigned int i=0 ; i<SNC->T_Output.size() ; i++)  // pour chaque sortie
        {
            if( SNC->T_Output[i]->isSignal() ) // si le neurone transmet qqch
            {
                SNC->T_Output[i]->transmet(false); // on répond que le neurone à transmit

                if( i==0) { // si c'est la sortie 0 qui réagit
                    x += 10;
                    if(x > TailleX) x = x%TailleX ;
                    }

                if( i==1) {// si c'est la sortie 1 qui réagit
                    y += 10;
                    if(y > TailleY) y = y%TailleY ;
                    }

                if( i==2) {// si c'est la sortie 2 qui réagit
                    y -= 10;
                    if(y<0) y = TailleY-y;
                    }

                if( i==3) {// si c'est la sortie 3 qui réagit
                    x -= 10;
                    if(x<0) x = TailleX-x;
                    }

            }
        }

        if(old_x != x || old_y != y) {
            add_life(50);
        }
} ;

