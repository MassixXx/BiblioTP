#include "Livre.h"
#include "Commandes.h"

void Affich::affichLivres(setBib & biblio,std::string & titre,std::string & auteur,std::string & type)
{
  int range{0};
  std::set<Livre> livres{};
  filtrBiblio(biblio, livres, titre, auteur, type);
  for (auto livre : livres)
  std::cout << "\t" << ++range << ")-----|\t" << livre.titre  << "\t auteur: " << livre.auteur << "\t type: " << livre.categorie << std::endl;
}



void Affich::affichParAuteur(setBib & biblio,std::string &titre,std::string & auteur,std::string & type)
{
  std::set<Livre,ordonParAuteur> biblioFiltree{};
  filtrBiblio(biblio,biblioFiltree,titre, auteur, type);
  std::string aut{};
  for (auto it{biblioFiltree.begin()};it != biblioFiltree.end();++it)
  {
    if (aut != it->auteur)
    {
      std::cout << it->auteur << ":\n";
      aut = it->auteur;
    }
      std::cout << '\t' << it->titre << "\ttype: " << it->categorie << '\n';
  }
}

void Affich::affichParType(setBib & biblio,std::string &titre,std::string & auteur,std::string & type)
{
  std::set<Livre,ordonParType> biblioFiltree{};
  filtrBiblio(biblio,biblioFiltree,titre, auteur, type);
  std::string typ{};
  for (auto it{biblioFiltree.begin()};it != biblioFiltree.end();++it)
  {
    if (typ != it->categorie)
    {
      std::cout << it->categorie << ":\n";
      typ = it->categorie;
    }
      std::cout << '\t' << it->titre << "\tauteur: " << it->auteur << '\n';
  }
}

template<class Comp>
void Affich::filtrBiblio(setBib const & biblio,std::set<Livre,Comp> & filtred,std::string & titre,std::string & auteur,std::string & type)
{
  for (auto livre : biblio)
  {
    if ((livre.titre==titre || titre ==ns) && (livre.auteur==auteur || auteur ==ns) && (livre.categorie==type || type==ns)) filtred.insert(livre);
  }
}
/*
void Affich::ordonLivre(setBib const & biblio,std::set<Livre> & livres)
{
  for (auto auteur : biblio)
  {
    for (auto livre : auteur.second)
    {
      livres.insert(livre);
    }
  }
}

void Affich::ordonParType(setBib const & biblio,std::map<std::string,std::set<LivreParType>> & bibType)
{
  for (auto auteur : biblio)
  {
    for (auto livre : auteur.second)
    {
      bibType[livre.categorie].insert({livre.titre,auteur.first});
    }
  }
}



void Affich::affichParType(setBib const & biblio,std::string typ)
{
  std::map<std::string,std::set<LivreParType>> bibType {};
  ordonParType(biblio,bibType);
  for (auto type : bibType)
  {
    if (typ == "*" || typ == type.first)
    {
      std::cout << "categorie : " << type.first << '\n' << "\t|\n";
      int range {0};
      for (auto livre : type.second )
      {
        std::cout << "\t|" << ++range << ")-------" << livre.titre << '\t' << "auteur : " << livre.auteur << '\n';
      }
      std::cout << "\t|___\n";
    }
  }
}
*/
