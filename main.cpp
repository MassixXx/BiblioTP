#include "Commandes.h"

using namespace std;

int main()
{
  Commande *ajouter = new Add;
  Commande *supprimer = new Supp;
  Commande *affich = new Affich;
/*  Commande *afficher = new Affich;*/
  string cmd{""};
  unordered_map<string,Commande*> commandes
  {
    {"ajouter",ajouter},
    {"add",ajouter},
    {"supp",supprimer},
    {"afficher",affich},
    {"print",affich}
    /*{"supprimer",supprimer},
    {"afficher",afficher}*/
  };
  bool quit {false};
  setBib biblio{};
  while (1){
    string input{""};
    cout << ">>> " ;
    getline(cin,input);
    iss ligneDeCommande {input};
    ligneDeCommande >> cmd;
    commandes[cmd]->f(ligneDeCommande,biblio);
  }
}
