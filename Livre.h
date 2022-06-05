#ifndef LIVRE_H
#define LIVRE_H

#include <string>

std::string ns {"non specifié"};

struct Livre
{
  std::string titre;
  std::string auteur;
  std::string categorie;

};

class ordonParAuteur {
public:
  bool operator()(Livre const & a, Livre const & b)
  {
    if (a.auteur != b.auteur)
    return (a.auteur < b.auteur);

      else if (a.categorie != b.categorie)
        return (a.categorie < b.categorie);

      else return (a.titre < b.titre);
  }
};

class ordonParType {
public:
  bool operator()(Livre const & a, Livre const & b)
  {

     if (a.categorie != b.categorie)
    return (a.categorie < b.categorie);

    else if (a.auteur != b.auteur)
    return (a.auteur < b.auteur);

        else return (a.titre < b.titre);
  }
};

struct LivreParType
{
  std::string titre;
  std::string auteur;
};

bool operator<(Livre const & a,Livre const & b);
bool operator==(Livre const & a,Livre const & b);


//std::string keyLivre(Livre const & livre) {return livre.auteur + livre.categorie + livre.titre; }

bool operator<(LivreParType const & a,LivreParType const & b);
bool operator==(LivreParType const & a,LivreParType const & b);

#endif
