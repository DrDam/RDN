#ifndef ORGANISME_H_INCLUDED
#define ORGANISME_H_INCLUDED
#include <vector>
#include "Rdn/Reseau.h"



class Organisme {

    //attributs
    protected:
    int x; // position X
    int y; // position Y
    Reseau* SNC ;// tableau qui contient les synapses amont
    int TailleX;// taille du mondeX
    int TailleY;// taille du mondeY

    //méthodes
    public:
    virtual void sentir() ; // interprete l'univers
    virtual void agir() ; // agit sur/avec l'univers
    Organisme( int *T_reseau, int in = 0, int out = 0) ; // constructeur
    virtual ~Organisme(); // destucteur
    void run(); // fonctionnement
    int getX(); // renvoi la valeur X
    int getY(); // renvoi la valeur Y


    Reseau* getSNC();

};

#endif // ORGANISME_H_INCLUDED
