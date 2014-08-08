#include <vector>
#include "Organisme.h"
#include "rdn/Reseau.h"

Organisme::Organisme( int *T_reseau, int in, int out ) {

    // création du Cerveau de l'organisme
    if(in == 0) { in = 10 ;}
    if(out == 0) { out = 2 ;}
    SNC =  new Reseau(  T_reseau[0], T_reseau[1], in, out);

    point_vie = 100;
}

void Organisme::run() {
     point_vie --;
     if(point_vie <= 0){
        mourir();
        return ;
     }
     sentir();
     SNC->run();
     agir();
}

Organisme::~Organisme() {}

void Organisme::sentir () {}

void Organisme::agir () {}

int Organisme::getX() { return x; };
int Organisme::getY() { return y; };

void Organisme::add_life(int nb){
    point_vie += nb;
}

int Organisme::getPointVie(){
    return point_vie;
}

void Organisme::mourir() {
    SNC->~Reseau();
  //  delete this;
}

Reseau* Organisme::getSNC()
 {
    return SNC;
 }
