
#include "Commandes.h"

using namespace std;



bool isOption(string const & mot)
{
  return (mot[0] == '-' && isalpha(mot[1]) );
}

string & extractCh(iss & is,string & ch) //on suppose que is.fail() == false et que la premiere lettre de ch est un guillemet '"'
{
  string mot {ch};
    while (mot.back()!='"')
    {
      is >> mot;
      if (mot.back()!='"' && is.eof()) throw /*gerer l'erreur */; // l'autre guillemet
      ch += ' ' + mot;
    }
    ch.erase(ch.begin());
    ch.erase(ch.size()-1,1);
  return ch;
}



bool trouvAndSupp(vector<string> & t,string const & ch)
{
  if (t[0]=="*") return true;
  bool trouv{false};

  erase_if(t,[&trouv,ch](string const & s)->bool{
    if ( s == ch )
    {
      trouv = true;
      return true;
    }
    else return false;
  });
  return trouv;
}

void Add::f(iss &ligneDeCommande, setBib &biblio)
{
  string mot{""};
  string auteur{ns};
  string type{ns};
  int option{0}; //option vaut 0 si aucune option n'a été entrée,1 si seulement -a a été entrée, 2 si seulement -t a été entrée, 3 si les deux ont été entrées; cela nous servira a gerer les erreurs
  vector<string> livres{};
  while (ligneDeCommande >> mot)
  {
    if (isOption(mot))
    {
      if (mot=="-a")
      {
        if (ligneDeCommande.eof()) throw /*gerer l'erreur*/; //l'utilisateur n'a pas entré le parametre de l'option
        if (option==1 || option ==3) throw /*gerer l'erreur*/ ; //option deja entrée
        ligneDeCommande >> auteur;
        if (auteur[0]=='"') auteur = extractCh(ligneDeCommande,auteur);
        ++option;
      }
      else if (mot=="-t")
      {
        if (ligneDeCommande.eof()) throw /*gerer l'erreur*/; //l'utilisateur n'a pas entré le parametre de l'option
        if (option == 2 || option == 3) throw /*gerer l'erreur */;
        ligneDeCommande >> type;
        if (type[0]=='"') type = extractCh(ligneDeCommande,type);
        option += 2;
      }
      else throw /*gerer l'erreur*/; //option inconnue
    }
    else if (option) throw /*gerer l'erreur*/; //trop de parametres
    else
    {
      if (mot[0]=='"')  mot = extractCh(ligneDeCommande, mot);
      livres.push_back(mot);
    }
  }


  if (livres.empty()) throw /*gerer l'erreur*/; //l'utilisateur n'a entré aucun livre
  int cpt{0}; //compteur de livres ajoutés
  for (auto livre:livres)
  {
    auto check = biblio.insert({livre,auteur,type});
    if (check.second)
    {
      ++cpt;
      cout << quoted(livre) << " a bien été ajouté." << endl;
    }
    else
    {
      cout << quoted(livre) << " de l'auteur " << quoted(auteur) << " existe déjà dans votre bibliothèque" << endl;
    }
  }
  cout << "nombre de livres ajoutés : " << cpt << endl;
}

void Supp::f(iss &is, setBib & biblio)
{
  std::string mot{""};
  std::string auteur{ns};
  std::string type{ns};
  int option{0};
  vector<string> aSupp{};
  while (is >> mot)
  {
    if (isOption(mot))
    {
      if (mot == "-a")
      {
        if (is.eof()) throw /*gerer l'erreur*/; //l'utilisateur n'a pas entré le parametre de l'option
        if (option==1 || option ==3) throw /*gerer l'erreur*/ ; //option deja entrée
        is >> auteur;
        cout << auteur << "h\n";
        if (auteur[0]=='"') extractCh(is, auteur);
        ++option ;
      }
      else if (mot == "-t")
      {
        if (is.eof()) throw /*gerer l'erreur*/; //l'utilisateur n'a pas entré le parametre de l'option
        if (option==2 || option ==3) throw /*gerer l'erreur*/ ; //option deja entrée
        is >> type;
        if (type[0]=='"') extractCh(is, type);
        option+=2 ;
      }
      else throw /*gerer l'erreur*/ ; //option invalide
    }
    else
    {
      if (mot[0]=='"') extractCh(is, mot);
      aSupp.push_back(mot);
    }
  }

  if (aSupp.empty()) throw /*gerer /'erreur*/ ; //rien a supp
  if (find(aSupp.begin(),aSupp.end(),"*")!=aSupp.end())
  {
    aSupp.clear();
    aSupp.push_back("*");
  }

int cpt {0};

auto affichSupp = [option](setBib::iterator const & trouv){
  std::cout << "Le livre " << trouv->titre;
  switch(option)
  {
    case 1:
      std::cout << " de l'auteur " << quoted(trouv->auteur);
      break;
    case 2:
      std::cout << " classé dans la catégorie " << quoted(trouv->categorie);
      break;
    case 3:
      std::cout << " de l'auteur " << quoted(trouv->auteur) << " classé dans la catégorie " << quoted(trouv->categorie);
      break;
  }
  std::cout << " a bien été supprimé.\n";
};

for (std::string livre : aSupp)
{
  if (livre != "*")
  {
    auto liste {findAll(biblio,livre,auteur,type)};
    if (liste.empty()) std::cout << quoted(livre) << " de l'auteur " << quoted(auteur) << " classé dans la catégorie " << quoted(type)<<" est introuvable dans votre bibliothéque." << std::endl;
    else {
      for (auto&& trouv : liste)
      {
        ++cpt;
        biblio.erase(trouv);
        affichSupp(trouv);
      }
    }
  }
  else
  {
    auto trouv = findAll(biblio,ns,auteur,type);
    if (trouv.empty()) std::cout << "Aucun livre trouvé\n";
    else  for (auto&& it : trouv)
      {
        ++cpt;
        biblio.erase(it);
        affichSupp(it);
      }
    }
  }

  std::cout << "nombre de livres supprimés : " << cpt << "." << std::endl;

}

void Affich::f(iss &is, setBib &biblio)
{
  std::string mot{""};
  std::string livre {ns};
  std::string auteur{ns};
  std::string type{ns};
  std::string mode {ns};
  set<char> options {};
  while (is >> mot)
  {
    if (isOption(mot))
    {
      if (mot == "-a")
      {
        if (is.eof()) throw /*gerer l'erreur*/; //l'utilisateur n'a pas entré le parametre de l'option
        if (options.find('a')==options.end() ) throw /*gerer l'erreur*/ ; //option deja entrée
        is >> auteur;
        if (auteur == "") throw ;
        cout << auteur << "h\n";
        if (auteur[0]=='"') extractCh(is, auteur);
        options.insert('a') ;
      }
      else if (mot == "-t")
      {
        if (is.eof()) throw /*gerer l'erreur*/; //l'utilisateur n'a pas entré le parametre de l'option
        if (options.find('t')==options.end()) throw /*gerer l'erreur*/ ; //option deja entrée
        is >> type;
        if (type[0]=='"') extractCh(is, type);
        options.insert('t') ;
      }
      else if (mot == "-o")
      {
        if (is.eof()) throw /*gerer l'erreur*/; //l'utilisateur n'a pas entré le parametre de l'option
        if (options.find('o')==options.end()) throw /*gerer l'erreur*/ ; //option deja entrée
        is >> mode;
        if (mode[0]=='"') extractCh(is, mode);
        options.insert('o') ;
      }
      else throw /*gerer l'erreur*/ ; //option invalide
    }
    else if (!options.empty()) throw ; //trop de parametres
    else if (options.find('l') == options.end()) throw ; //livre deja entré
    {
      if (mot[0]=='"') extractCh(is, mot);
      livre = mot;
      options.insert('l');
    }
  }

  if (mode == ns)
  {
    affichLivres(biblio,livre,auteur,type);
  }
  else if (mode == auteur)
  {
    affichParAuteur(biblio, livre, auteur, type);
  }
  else if (mode == type)
  {
    affichParType(biblio, livre, auteur, type);
  }
  else throw ; //mode inconnu

}

std::list<setBib::iterator> findAll(setBib const & biblio,std::string const & titre,std::string const & auteur,std::string const & type)
{
  list<setBib::iterator> liste {};
  for (auto it {biblio.begin()};it != biblio.end();++it)
  {
    if ((it->auteur == auteur || auteur ==ns) && (it->categorie==type || type == ns) && (titre ==ns || titre == it->titre)) {
      liste.push_back(it);
    }
  }
  return liste;
}
