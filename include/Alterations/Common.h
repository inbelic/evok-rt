#ifndef _ALTERATIONS_COMMON_HEADER_
#define _ALTERATIONS_COMMON_HEADER_

// Helpers for common types of alterations that can be applied to a contract.

#include "../Core/Alteration.h"
#include "../Core/Contract.h"
#include "../Traits/Common.h"

namespace alter {

Alteration set(ContractPtr contract, Field field, BaseType val) {
  auto trait = TraitPtr(new ConstantTrait(val));
  auto alteration = Alteration{AlterationType::Set, field, val};

  contract->replace(field, std::move(trait));
  return alteration;
}

MaybeAlteration clampedShift(ContractPtr contract, Field field, bool pos, BaseType val) {
  auto trait = TraitPtr(new ClampedShiftTrait(pos, val));
  auto type = pos ? AlterationType::PosShift : AlterationType::NegShift;
  std::optional<Alteration> alteration = Alteration{type, field, val};

  return contract->modify(field, std::move(trait)) ? alteration : std::nullopt;
}

} // alter

#endif // _ALTERATIONS_COMMON_HEADER_
