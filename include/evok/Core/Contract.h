#ifndef _EVOK_CORE_CONTRACT_HEADER_
#define _EVOK_CORE_CONTRACT_HEADER_

#include "Alteration.h"
#include "Field.h"
#include "Trait.h"

#include <map>

namespace evok {

using Traits = std::map<Field, TraitPtr>;

class Contract;
using ContractPtr = Contract *; // Will have a contract arena for base Contracts

class Contract {
private:
  std::optional<ContractPtr> base = std::nullopt; // Does not own base.

  Traits traits;
  void reload_traits(ContractPtr);

public:
  Contract(){};

  // Initialize a contract from a given base.
  Contract(ContractPtr base);

  virtual ~Contract(){};

  // Goes through all the stored traits and marks them as allocated
  void markTraits(TraitSet &);

  // Evaluates the trait of the given field, will set found to false if the
  // Contract does not have the trait. nullopt denotes that is was unable to
  // evaluate the field
  std::optional<BaseType> view(const ContractState &, Field, bool &found) const;

  // Will reset the contract to its base reference if the base is not a nullptr
  // and denote if it does by return an empty Changes or a Changes with a
  // Reload
  MaybeAlteration reload();

  // Will append the Trait to the Alteration.Field and will output an
  // Alter Alteration. Boolean output denotes if the field was found and applied
  bool modify(Field, TraitPtr);

  // Will replace the Traits of Alteration.Field with the given Trait
  void replace(Field, TraitPtr);
};

} // namespace evok

#endif // _EVOK_CORE_CONTRACT_HEADER_
