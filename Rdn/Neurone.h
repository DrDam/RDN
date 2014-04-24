#ifndef NEURONE_H_INCLUDED
#define NEURONE_H_INCLUDED
#include <vector>
#include "Synapse.h"


class Neurone {

    //attributs
     private:

    static int m_seuil;
    static int m_seuil_bas;
    static int m_taux_stab;
    static int m_base_pps;
    bool m_actif ;           // le neurone est il actif
    std::vector<Synapse*> T_amont ;// tableau qui contient les synapses amont
    std::vector<Synapse*> T_aval ;// tableau qui contient les synapses aval
    float m_potentiel; // valeur du potentiel

    int m_id; // ID du neurone

    //méthodes

    public:

    Neurone(int id); // constructeur
    ~Neurone();
    void PPS( int type,int coef); // le neurone reçoit un signal d'une synapse
    void stabilise(); // le potentiel du neurone retourne à la normal
    void ajout_synapse(Synapse* synapse ,bool amont = true); // ajoute une synapse au neurone
    void detruire_synapse(Synapse* synapse_cible , bool amont = true); // détruit une synapse
    void run(); // fonctionnement du neurone
    bool isActicf(); // renvoi l'état du neurone
    static void setstatic( int setseuil, int setbas, int settaux, int setpss) ; // met à jour les static au début du programme
    float getpotentiel() ; // renvoi la valeur du potentiel
    int getId();

    std::vector<Synapse*> getAllAmont();
    std::vector<Synapse*> getAllAval();


};
#endif // NEURONE_H_INCLUDED
