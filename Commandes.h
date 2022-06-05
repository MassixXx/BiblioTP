//Bismillah
#ifndef COMM_H
#define COMM_H

#include <string>
#include "Livre.h"
#include <map>
#include <sstream>
#include <string>
#include <cctype>
#include "Commandes.h"
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <iomanip> //pour le std::quoted()
#include <map>
#include <unordered_set>
#include <list>


using iss = std::istringstream;

using setBib = std::set<Livre>;

class Commande
{
public:
  virtual void f(iss & ligneDeCommande,setBib & biblio) = 0;
};

class Add : public Commande
{
public:
  virtual void f(iss & ligneDeCommande,setBib & biblio);
};

class Supp : public Commande
{
public:
  virtual void f(iss & ligneDeCommande,setBib & biblio);
};

class Affich : public Commande
{
public:
  virtual void f(iss & ligneDeCommande,setBib & biblio);
private:
  void affichParAuteur(setBib & biblio,std::string & titre,std::string & auteur,std::string & type);
  void affichLivres(setBib & biblio,std::string & titre=ns,std::string & auteur=ns,std::string & type=ns);
  void affichParType(setBib & biblio,std::string &titre,std::string & auteur,std::string & type);
  void ordonLivre(setBib const & biblio,std::set<Livre> & livres);
  //void ordonParType(setBib const & biblio,std::map<std::string,std::set<LivreParType>> & bibType);
  template<class Comp>
  void filtrBiblio(setBib const & biblio,std::set<Livre,Comp> & filtred,std::string & titre,std::string & auteur,std::string & type);

};


bool isOption(std::string const & mot);
std::string &  extractCh(iss & is,std::string & ch); //on suppose que is.fail() == false
std::list<setBib::iterator> findAll(setBib const & biblio,std::string const & titre,std::string const & auteur,std::string const  & type );

#endif
