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

public:
  Contract() {};

  // Initialize a contract from a given base.
  Contract(ContractPtr base);

  virtual ~Contract() {};

  // Evaluates the trait of the given field, will set found to false if the
  // Contract does not have the trait
  std::optional<BaseType> view(const ContractState&, Field, bool& found) const;

  // Will reset the contract to its base reference if the base is not a nullptr
  // and denote if it does by return an empty Changes or a Changes with a
  // Reload
  MaybeAlteration reload();

  // Will append the Trait to the Field and will output an Alter Alteration.
  // It will output nullopt if the Field is not found
  MaybeAlteration modify(Field, TraitPtr, Alteration = Alteration{AlterationType::Alter});

  // Will replace the Traits of Field with the given Trait and will output a
  // Alter Alteration
  MaybeAlteration replace(Field, TraitPtr, Alteration = Alteration{AlterationType::Alter});
};

#endif // _CORE_CONTRACT_HEADER_
