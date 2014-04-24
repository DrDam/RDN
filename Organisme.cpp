#include <vector>
#include "Organisme.h"
#include "Rdn/Reseau.h"

Organisme::Organisme( int *T_reseau, int in, int out ) {

    // création du Cerveau de l'organisme
        if(in == 0) { in = 10 ;}
        if(out == 0) { out = 2 ;}
        SNC =  new Reseau(  T_reseau[0], T_reseau[1], in, out);
}

void Organisme::run() {
     sentir();
     SNC->run();
     agir();
}

Organisme::~Organisme() {}

void Organisme::sentir () {}

void Organisme::agir () {}

int Organisme::getX() { return x; };
int Organisme::getY() { return y; };

Reseau* Organisme::getSNC()
 {
    return SNC;
 }
