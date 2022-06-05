#include "Livre.h"

bool operator<(Livre const & a,Livre const & b)
{
  if (a.auteur != b.auteur)
  return (a.auteur < b.auteur);

    else if (a.categorie != b.categorie)
    return (a.categorie < b.categorie);

      else return (a.titre < b.titre);
}

bool operator==(Livre const & a,Livre const & b)
{
  return ( (a.auteur == b.auteur) && (a.categorie == b.categorie) && (a.titre == b.titre) );
}

bool operator<(LivreParType const & a,LivreParType const & b)
{
  return (a.titre < b.titre);
}

bool operator==(LivreParType const & a,LivreParType const & b)
{
  return (a.titre == b.titre);
}
