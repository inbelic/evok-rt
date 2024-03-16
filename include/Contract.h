#ifndef _CONTRACT_HEADER_
#define _CONTRACT_HEADER_

#include "Alteration.h"
#include "Field.h"
#include "Trait.h"

#include <map>

using Traits = std::map<Field, TraitPtr>;

class Contract {
private:
  Traits traits;

  Contract* base = nullptr;

protected:
  // Sets a base contract that it can be reloaded to
  void setBase(Contract*);

public:
  Contract() {};

  // Initialize a contract from a given base.
  Contract(Contract* base);

  // Will reset the contract to its base reference if the base is not a nullptr
  // and denote if it does by return an empty Changes or a Changes with a
  // Reload
  Alterations reload();

  // Will append the Trait to the Field and will output an Alter Alteration
  Alterations modify(Field, TraitPtr);

  // Will replace the Traits of Field with the given Trait and will output a
  // Alter Alteration
  Alterations replace(Field, TraitPtr);
};

#endif // _CONTRACT_HEADER_
