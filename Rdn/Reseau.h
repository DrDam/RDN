#ifndef RESEAU_H_INCLUDED
#define RESEAU_H_INCLUDED
#include <vector>
#include "Neurone.h"
#include "Synapse.h"

class Reseau {

    //attributs
    private:
    std::vector<Neurone*> T_Neurones ;// tableau qui contient les neurones du r�seau
    std::vector<Synapse*> T_Synapses ;// tableau qui contient les synapses du r�seau
    bool end ; // signal de FIN

    public:
    std::vector<Synapse*> T_Input ;// tableau qui contient les synapses d'entr�es du r�seau
    std::vector<Synapse*> T_Output ;// tableau qui contient les synapses de sorties du r�seau

    //m�thodes
    public:
    Reseau( char URL );
    Reseau( int nb_Neurone, int nb_Synapse, int nb_Input, int nb_Output ) ;
    void integration(); // => transmet au r�seau l'�tat des synapses d'entr�
    void run() ;

    std::vector<Neurone*> getallNeurone();
    std::vector<Synapse*> getallSynapse();
    std::vector<Synapse*> getallSynapseIN();
    std::vector<Synapse*> getallSynapseOUT();

    Neurone * getNeurone(int id);
    Synapse * getSynapse(int id);
    Synapse * getSynapseIN(int id);
    Synapse * getSynapseOUT(int id);

};

#endif // RESEAU_H_INCLUDED
