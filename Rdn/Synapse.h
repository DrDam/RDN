#ifndef SYNAPSE_H_INCLUDED
#define SYNAPSE_H_INCLUDED
#include <vector>
#include "Neurone_fwd.h"

class Synapse {

    //attributs
    private:
    Neurone* neurone_amont ; // neurone amont
    Neurone* neurone_aval ; // neurone aval
    int type ; // ( +1 ou -1 => excitateur ou inhibiteur .... base de départ)
    int coef ; // force de la synapse ( nombre de synapses regroupés)
    bool signal ; // la synapse transmet elle qqch
    int m_id; // id de ma synapse

    //méthodes
    public:
    Synapse(int id,Neurone* amont, Neurone* aval, int type_in ) ;  // constructeur => les neurones amont/aval et type de la synapse
    ~Synapse();
    void detruit( bool amont ); // destructeur particulier => transmet le signal de destruction de la synapse au neurone voisin
    void run(); // fonctionnement de la synapse
    bool isSignal(); // renvoi la valeur du signal
    void setType( int value ); // fixe la valeur du type
    int getType() ; // renvoi le type
    void setCoef( int value ); // fixe le coef
    int getCoef() ; // renvoi le coef
    void transmet( bool value) ; // met à jour le "signal"

    int getId();
    Neurone* getAmont();
    int getAmontId();
    Neurone* getAval();
    int getAvalId();
};
#endif // SYNAPSE_H_INCLUDED
