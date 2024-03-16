#ifndef _CORE_CONTRACT_HEADER_
#define _CORE_CONTRACT_HEADER_

#include "Alteration.h"
#include "Field.h"
#include "Trait.h"

#include <map>

using Traits = std::map<Field, TraitPtr>;

class Contract;
using ContractPtr = Contract*; // Will have a contract arena for base Contracts

class Contract {
private:
  std::optional<ContractPtr> base = std::nullopt; // Does not own base.

  Traits traits;
  void reload_traits(ContractPtr);

protected:
  // Sets a base contract that it can be reloaded to
  void setBase(ContractPtr);

public:
  Contract() {};

  // Initialize a contract from a given base.
  Contract(ContractPtr base);

  virtual ~Contract() {};

  // Will reset the contract to its base reference if the base is not a nullptr
  // and denote if it does by return an empty Changes or a Changes with a
  // Reload
  Alteration reload();

  // Will append the Trait to the Field and will output an Alter Alteration
  Alteration modify(Field, TraitPtr);

  // Will replace the Traits of Field with the given Trait and will output a
  // Alter Alteration
  Alteration replace(Field, TraitPtr);
};

#endif // _CORE_CONTRACT_HEADER_
