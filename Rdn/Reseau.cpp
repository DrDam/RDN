#include <vector>
#include "Neurone.h"
#include "Synapse.h"
#include "Reseau.h"
#include "../lib/alea/alea.h"
#include <cstddef>


Reseau::Reseau( char URL ) { }

//=> cr�ation du r�seau : nb_synapse : nombre de synapse aval par neurone
Reseau::Reseau( int nb_Neurone, int nb_Synapse, int nb_Input, int nb_Output ) {

   // cr�ation des neurone
    for ( int i(0);i<nb_Neurone;++i) {
            T_Neurones.push_back( new Neurone(i) );
        }

bool creee = false; // si on a cr�er la synapse
int syncrees = 0; // un compteur de synapse cr�e
int nombre_aleat;

while(syncrees<nb_Synapse)
{
    for ( int j=0;j<nb_Neurone;j++) //pour chaque neurone
        {
            //nombre_aleat = rand()%(nb_Neurone-1); // on tire un premier neurone al�atoirement
            nombre_aleat = alea(nb_Neurone-1);
            while ( nombre_aleat == j ){nombre_aleat = alea(nb_Neurone-1);} //rand()%(nb_Neurone-1);}

            int type = alea(9); //rand()%(9); // on prend un chiffre entre 0 et 9 si <5 => -1 si >5 =>+1
            if (type<5)type=-1;
            else type=1;


            creee =  false; // si on a cr�er la synapse


                for ( int unsigned t=0;t<T_Synapses.size();t++)
                      {
                            //on v�rifie s'il existe d�j� une connection entre le neurone j et nombre-aleat
                           if (T_Synapses[t]->getAmontId()==j&&T_Synapses[t]->getAvalId()==nombre_aleat&&creee==0) // S'il existe d�j� une synapse on incr�mente le coef
                            {
                                T_Synapses[t]->setCoef(T_Synapses[t]->getCoef()+1);
                                creee = true; // on informe qu'on a ajouter une synapse
                            }


                            // S'il existe une boucle directe ( de nombrealeat vers j ), on branche la synapse dans le bon sens (de j vers nombrealaet)
                            if (T_Synapses[t]->getAmontId()==nombre_aleat&&T_Synapses[t]->getAvalId()==j&&creee==0)
                            {

                                    for (unsigned int k=0;k<T_Synapses.size();k++) // On v�rifi s'il existe d�j� une connection dans le sens inverse
                                        {
                                        if (T_Synapses[t]->getAmontId()==nombre_aleat&&T_Synapses[t]->getAvalId()==j&&creee==0) // S'il existe d�j� une synapse on incr�mente le coef
                                            {
                                            T_Synapses[t]->setCoef(T_Synapses[t]->getCoef()+1);
                                            creee = true; // on informe qu'on a ajouter une synapse
                                            }
                                        }

                                    if (!creee)T_Synapses.push_back( new Synapse(syncrees,T_Neurones[nombre_aleat],T_Neurones[j],type )); // si aucune conenction a �t� trouv� on en cr�er une

                            }

                        }

            //S'Il n'y a pas de doublon, ni de boucle, donc on cr�er une noubelle synapse
            if(!creee){
            T_Synapses.push_back( new Synapse(syncrees,T_Neurones[j],T_Neurones[nombre_aleat],type )); // on lie les 2 neurones par une synapse
            creee = true;
            }

            if(creee) { syncrees ++ ;} // on incremente le nombre de synapses cr�es
        }
}

    //=> �volutions � pr�voir : controler que deux neurones ne soit pas li� dans un sens par une synapse et dans l'autre sens par une seconde

        // cr�ation entr�s
        for ( int i=0;i<nb_Input;i++) // pour chaque entr� du r�seau demande
            {
             int nombre_aleat = alea(nb_Neurone-1); //rand()%(nb_Neurone-1); // on choisi un neurone
             T_Input.push_back( new Synapse(syncrees+i, NULL ,T_Neurones[nombre_aleat],1) ); //on lui cr�e une synapse d'entr�e
            }

        // cr�ation sortie
        for ( int i=0;i<nb_Output;i++)// pour chaque sortie du r�seau demande
            {
             int nombre_aleat = alea(nb_Neurone-1);//rand()%(nb_Neurone-1);// on choisi un neurone
             T_Output.push_back( new Synapse(syncrees+nb_Input+i,T_Neurones[nombre_aleat],NULL,1) );//on lui cr�e une synapse de sortie

            }


 }

void Reseau::integration() {
     for ( unsigned int i=0;i<T_Input.size();i++)
            {
                T_Input[i]->run();
            }} // met � jour les synapses d'entr�e


void Reseau::run() {

            integration() ;

            //run des synapses
            for ( unsigned int i=0;i<T_Synapses.size();i++)
            {
                T_Synapses[i]->run();
            }

             //pour les neurones
            for ( unsigned int i=0;i<T_Neurones.size();i++)
            {
                T_Neurones[i]->run();
            }

    };

std::vector<Neurone*> Reseau::getallNeurone()
 {
    return T_Neurones;
 }

std::vector<Synapse*> Reseau::getallSynapse()
 {
    return T_Synapses;
 }

std::vector<Synapse*> Reseau::getallSynapseIN()
 {
    return T_Input;
 }

 std::vector<Synapse*> Reseau::getallSynapseOUT()
 {
    return T_Output;
 }

Neurone * Reseau::getNeurone(int id)
 {
    return T_Neurones[id];
 }

Synapse * Reseau::getSynapse(int id)
 {
    return T_Synapses[id];
 }
Synapse * Reseau::getSynapseIN(int id)
 {
    return T_Input[id];
 }

Synapse * Reseau::getSynapseOUT(int id)
 {
    return T_Output[id];
 }
