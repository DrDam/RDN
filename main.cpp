#include <iostream>
#include "Univers.h"
#include "Rdn/Neurone.h"
#include "time.h"
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <time.h> //=> pour le noyau de la fonction al�atoire
#include <cstdlib>
#include <omp.h>

// on cr�e une fenetre
sf::RenderWindow ecran;

using namespace std;

void out_monde(Univers monde) // affichage graphique
{
    std::vector<Organisme*> population = monde.getAllOrganisme(); // on r�cup�re tout les organismes

    ecran.clear(sf::Color::Black); // on efface le contenu de la fenetre

    for ( unsigned int i=0;i<population.size();++i) // pour chaque organisme
            {   // on trace un "cercle de 5 pixels
                sf::CircleShape myCircle = sf::CircleShape(5);
                // de couleur verte
                myCircle.setFillColor(sf::Color(0, 255, 100));
                // positionn�
                myCircle.setPosition(10, 50);

                ecran.draw(myCircle);
            }

    ecran.display(); // on affiche le tout
}

void out_console(Univers monde, int cycle) // d�bug des r�seau en console
{
    std::cout <<  "TU = "<< cycle << std::endl; // on affiche le "cycle en cours"

    std::vector<Organisme*> population = monde.getAllOrganisme(); // on r�cup�re tout les organismes

    for ( unsigned int i(0);i<population.size();++i) // pour chaque organisme
        {
            cout <<"organisme" << i <<" :"<<endl;
            Reseau * reseau = population[i]->getSNC(); // on r�cup�re sont RdN
            for ( unsigned int i(0);i<reseau->getallSynapse().size();++i) //on r�cup�re l'ensemble des synapses
                {
                    int idn1 = reseau->getSynapse(i)->getAmontId(); // on r�cup�re le num�ro du neurone en amont de la synapse i
                    Neurone* a = reseau->getNeurone(idn1);          // on r�ucp�re l'objet Neurone

                    int idn2 = reseau->getSynapse(i)->getAvalId();  // on r�cup�re le num�ro du neurone en aval de la synapse i
                    Neurone* b =reseau->getNeurone(idn2);           // on r�ucp�re l'objet Neurone

                    // On affiche les connections des neurones, le potentiel entre paranth�se
                    cout << "neurone" << reseau->getSynapse(i)->getAmontId()<<"("<< "pot = " << a->getpotentiel()<< ") ---" ;
                    cout <<reseau->getSynapse(i)->getCoef()<<"--> "<< "neurone" <<reseau->getSynapse(i)->getAvalId() ;
                    cout <<"("<< "pot = " << b->getpotentiel()<<")"<<endl;
                }
        }
}



int main()
{
    // initialisation des constantes du programme
    std::srand(time(NULL)); // racine pour les al�atoires

    // param des neurones
    int setseuil = 100;
    int setbase = 40;
    int setstab = 10;
    int setpps = 1;

    //param des r�seau
    int nbneu = 100;
    int nbsyn = 20;

    // param de l'univers
    int nbcycle = -1; // => nb cycle infinie
    bool end = true;
    bool pause = false;
    bool console = false;


    // choix du fonctionnement : param�tres personalis�s ?
    int test = 0;
    cout << "test automatique ? oui=>1 ; non=>0" << endl;
    cin >> test;

    if(test == 0) // si on rentre des param personalis�
    {
        cout << "merci d'entrer que des entiers" << endl <<"sinon je garantie pas les effet sur votre machine" << endl;
        cout << endl<< "parametres du programme : " << endl;
            cout << "seuil a atteindre pour qu'un neurone s'active ( exemple : 100)" <<endl;
                cin >> setseuil;
            cout << "potentiel minimal du neurone ( inferieur au seuil, exemple 40) " <<endl;
                cin >> setbase;
            cout << "stabiliation du potentiel ( >0 et <100 , exemple : 10)" <<endl;
                cin >> setstab;
            cout << "sensibilite du neurone ( 1: sensible max, >0, exemple 2) " <<endl;
                cin >> setpps;
        cout << endl<< "parametres du reseau  : " << endl;
            cout << "nombre de neurone du reseau ( >0, exemple 10) " <<endl;
                cin >> nbneu;
            cout << "nombre de sortie de chaque neurone ( >0, exemple 3) " <<endl;
                cin >> nbsyn;
        cout << endl<< "parametre de fonctionnement  : " << endl;
            cout << "nombre de cycle du programme(>0, exemple 50, -1 si infini) " <<endl;
                cin >> nbcycle;
    }

    // met � jour les statics des neurones
    Neurone::setstatic(setseuil,setbase,setstab,setpps);

    //cout << "D�but du programme" << endl;

    //instructions
    cout << "Pour les touches, veuillez selectionner la fenetre graphique" << endl;
    cout << "Touches utilisables" << endl;
    cout << "Quitter : Q ou echap" << endl;
    cout << "Pause : P" << endl;
    cout << "Afficher Feed_back : K" << endl;

    // ouverture fenetre
    ecran.create(sf::VideoMode(800, 600), "My window");

    //initialisation du SNC des organismes
    int Tab_SNC[] = { nbneu , nbsyn};

    //cout << endl;

    //cr�ation de l'univers
    Univers monde(1, Tab_SNC) ;
    //cout << endl;

    //attendre que l'utilisateur "lance le programme" => disparaitra avec le debug en GUI
    cout << endl << endl << "appuyer sur ''return'' pour commencer" << endl;
        while(getchar()) {  break; }
        while(getchar()) {  break; }

    //lancement du jeu
    int cycle = 0;
    while( end )
        {
        // gestion des �venements

        sf::Event Event;

        while(ecran.pollEvent(Event)) // Tant qu'il y a un �v�nement, on le r�cup�re
            {
            if (Event.type == sf::Event::Closed)  // On quitte si on clique sur la croix rouge
                end = false;

            if ((Event.type == sf::Event::KeyPressed))    // Ev�nement clavier
                {
                    if(Event.key.code == sf::Keyboard::Escape || Event.key.code == sf::Keyboard::Q )     // On quitte si on appuy sur �chap oui Q
                        end =  false;

                    if(Event.key.code == sf::Keyboard::P)          // On met en pause/reprend le programme sur l'appuy de la touche P
                        pause = pause xor true;

                    if(Event.key.code == sf::Keyboard::K)          // On met en pause/reprend le programme sur l'appuy de la touche P
                        console = console xor true;
                }
            }

        if(!pause)
            {

            // run du monde
            monde.run();

            // remonte les infos
            if(console) out_console(monde,cycle);

            //affichage du graphisme
            out_monde(monde);

            //incr�mente le cycle
            cycle++;
            }

            if( nbcycle != -1 && cycle > nbcycle ) end = false  ;
        }

    //cout << "Fin du programme" << endl;
    //cout << endl << endl << "Fin !!! ( appuyer sur ''return'' )" << endl;
    //while(getchar()) {  break; }

 return 0;

}




