#include <iostream>
#include "Univers.h"
#include "Rdn/Neurone.h"
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <omp.h>

using namespace std;

// on crée une fenetre
sf::RenderWindow ecran;

// affichage graphique
void out_monde(Univers monde,int cycle)
{
    std::string cycles = std::to_string(cycle);

    std::vector<Organisme*> population = monde.getAllOrganisme(); // on récupère tout les organismes

    ecran.clear(sf::Color::Black); // on efface le contenu de la fenetre

    // Affichage du temps

    sf::Font font;
    font.loadFromFile("./Arial.ttf");

    sf::Text text;
    text.setFont(font); // font est un sf::Font
    text.setString("Tu : " + cycles);
    text.setCharacterSize(24); // exprimée en pixels, pas en points !
    text.setColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    ecran.draw(text);

    // Trouver moyen de threader ça aussi !
    for ( unsigned int i=0;i<population.size();++i) // pour chaque organisme
            {   // on trace un "cercle de 5 pixels
                sf::CircleShape myCircle = sf::CircleShape(5);
                // de couleur verte
                myCircle.setFillColor(sf::Color(0, 255, 100));
                // positionné
                myCircle.setPosition(population[i]->getX(), population[i]->getY());

                ecran.draw(myCircle);
            }

    ecran.display(); // on affiche le tout
}



// débug des réseau en console
void out_console(Univers monde, int cycle)
{
    std::cout <<  "TU = "<< cycle << std::endl; // on affiche le "cycle en cours"

    std::vector<Organisme*> population = monde.getAllOrganisme(); // on récupère tout les organismes

    #pragma omp parallel for
    for ( unsigned int i =0;i<population.size();++i) // pour chaque organisme
        {
            cout <<"organisme" << i <<" :"<<endl;
            Reseau * reseau = population[i]->getSNC(); // on récupère sont RdN
            for ( unsigned int i(0);i<reseau->getallSynapse().size();++i) //on récupère l'ensemble des synapses
                {
                    int idn1 = reseau->getSynapse(i)->getAmontId(); // on récupère le numéro du neurone en amont de la synapse i
                    Neurone* a = reseau->getNeurone(idn1);          // on réucpère l'objet Neurone

                    int idn2 = reseau->getSynapse(i)->getAvalId();  // on récupère le numéro du neurone en aval de la synapse i
                    Neurone* b =reseau->getNeurone(idn2);           // on réucpère l'objet Neurone

                    // On affiche les connections des neurones, le potentiel entre paranthèse
                    cout << "neurone" << reseau->getSynapse(i)->getAmontId()<<"("<< "pot = " << a->getpotentiel()<< ") ---" ;
                    cout <<reseau->getSynapse(i)->getCoef()<<"--> "<< "neurone" <<reseau->getSynapse(i)->getAvalId() ;
                    cout <<"("<< "pot = " << b->getpotentiel()<<")"<<endl;
                }
        }
}



int main()
{
    // initialisation des constantes du programme

    // param des neurones
    int setseuil = 100;
    int setbase = 40;
    int setstab = 10;
    int setpps = 1;

    //param des réseau
    int nbneu = 100;
    int nbsyn = 20;

    // param de l'univers
    int nbcycle = -1; // => nb cycle infinie
    int nborg = 10 ;
    int nb_thread = 4;

    // Variable de programme
    int cycle = 0;
    bool end = true;
    bool pause = false;
    bool console = false;

    // choix du fonctionnement : paramètres personalisés ?
    int test = 0;
    cout << "test automatique ? oui=>1 ; non=>0" << endl;
    cin >> test;

    if(test == 0) // si on rentre des param personalisé
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
            cout << "nombre d'organisme (>0, exemple 10) " <<endl;
                cin >> nborg;
            cout << "nombre de cycle du programme(>0, exemple 50, -1 si infini) " <<endl;
                cin >> nbcycle;
            cout << "nombre de thread du programme(>0, exemple "<< omp_get_num_procs() <<") " <<endl;
                cin >> nb_thread;
    }

    // set nb thread
    omp_set_num_threads(nb_thread);

    // met à jour les statics des neurones
    Neurone::setstatic(setseuil,setbase,setstab,setpps);

    cout << "Début du programme" << endl << endl;

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

    //création de l'univers
    Univers monde(nborg, Tab_SNC) ;

    //attendre que l'utilisateur "lance le programme" => disparaitra avec le debug en GUI
    cout << endl << endl << "appuyer sur ''return'' pour commencer" << endl;
        while(getchar()) {  break; }
        while(getchar()) {  break; }

    //lancement du jeu
    while( end )
        {

        // gestion des évenements
        sf::Event Event;

        while(ecran.pollEvent(Event)) // Tant qu'il y a un évènement, on le récupère
            {
            if (Event.type == sf::Event::Closed)  // On quitte si on clique sur la croix rouge
                end = false;

            if ((Event.type == sf::Event::KeyPressed))    // Evènement clavier
                {
                    if(Event.key.code == sf::Keyboard::Escape || Event.key.code == sf::Keyboard::Q )     // On quitte si on appuy sur échap oui Q
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
            out_monde(monde,cycle);

            //incrémente le cycle
            cycle++;
            }

            if( nbcycle != -1 && cycle > nbcycle ) end = false  ;
        }

    cout << "Fin du programme" << endl;
    cout << endl << endl << "Fin !!! ( appuyer sur ''return'' )" << endl;
    while(getchar()) {  break; }

 return 0;

}





