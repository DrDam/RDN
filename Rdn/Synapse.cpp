#include "Neurone.h"
#include "Synapse.h"
#include <vector>
#include <cstddef>
//=> création d'une nouvelle synapse
Synapse::Synapse(int id,Neurone* amont = NULL , Neurone* aval = NULL , int type_in = 1 ) {
    m_id=id;
    neurone_amont = amont ; // on lie la nouvelle synapse à son neurone amont
        if(amont != NULL) { amont->ajout_synapse(this,false); }
    neurone_aval = aval  ;  // on lie la nouvelle synapse à son neurone aval
        if(aval != NULL) { aval->ajout_synapse(this,true); }
    // met à jour les attributs
    type = type_in;
    signal = false;
    coef = 1;


}

Synapse::~Synapse() {};

//=> destructeur "maison"
void Synapse::detruit(bool neuroneAmont) {
    if(neuroneAmont == true ) // si la demande de destruction viens du neurone amont
        { neurone_aval->detruire_synapse( this , false )  ; } // on met à jour le neurone aval
    else { neurone_amont->detruire_synapse( this , true )   ; } // sinon on met à jour le neurone amont
    this->~Synapse() ; //on détruit la synapse => attention à ne pas détruire les neurones !!!
}

void Synapse::transmet(bool value = true) { signal = value; } // met la synapse en marche
bool Synapse::isSignal()  {return  signal ;  }    // informe sur l'état de la synapse
void Synapse::setType( int value )  {  type = value ; } // met à jour le type de syanpse
int Synapse::getType()   {return  type ;  } //retourne le type de synapse
void Synapse::setCoef( int value )  {  coef = value ; } // met à jour le type de syanpse
int Synapse::getCoef()   {return  coef ;  } //retourne le type de synapse

//=> fonctionnement de la synapse
void Synapse::run() {
    if (signal==1&&neurone_aval->isActicf()==1)  // si la synapse transmet un message et que le neurone aval est actif
    {
         neurone_aval->PPS(type,coef); // générer un PPS
         signal = false ; // la synapse a fini sa transmission
    }
}

int Synapse::getId()
 {
     return m_id;
 }
int Synapse::getAmontId()
 {
 return neurone_amont->getId();
 }

 Neurone* Synapse::getAmont()
 {
 return neurone_amont;
 }

int Synapse::getAvalId()
 {
 return neurone_aval->getId();
 }

 Neurone* Synapse::getAval()
 {
 return neurone_aval;
 }
