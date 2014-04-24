#ifndef POISSON_H_INCLUDED
#define POISSON_H_INCLUDED
#include "Organisme.h"

class Poisson : public Organisme
{
 private:
   // bool out1,out2,out3 ; // controle d'existance des sorties

public:
    Poisson(int *T_reseau , int max_ecran);
    void sentir() ; // interprete l'univers => methode virtuel d'organisme
    void agir() ; // agit sur/avec l'univers  => methode virtuel d'organisme
};

#endif // POISSON_H_INCLUDED
