#ifndef _EVOK_ALTERATIONS_COMMON_HEADER_
#define _EVOK_ALTERATIONS_COMMON_HEADER_

// Helpers for common types of alterations that can be applied to a contract.

#include "../Core/Alteration.h"
#include "../Core/Contract.h"
#include "../Traits/Common.h"

namespace evok {
namespace alter {

Alteration set(ContractPtr contract, Field field, BaseType val) {
  auto trait = TraitPtr(new trait::ConstantTrait(val));
  auto alteration = Alteration{AlterationType::Set, field, val};

  contract->replace(field, trait);
  return alteration;
}

MaybeAlteration clampedShift(ContractPtr contract, Field field, bool pos,
                             BaseType val) {
  auto trait = TraitPtr(new trait::ClampedShiftTrait(pos, val));
  auto type = pos ? AlterationType::PosShift : AlterationType::NegShift;
  std::optional<Alteration> alteration = Alteration{type, field, val};

  return contract->modify(field, trait) ? alteration : std::nullopt;
}

} // namespace alter
} // namespace evok

#endif // _EVOK_ALTERATIONS_COMMON_HEADER_
