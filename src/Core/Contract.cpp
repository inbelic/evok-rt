#include "evok/Core/Contract.h"

namespace evok {

void Contract::reload_traits(ContractPtr base) {
  traits.clear();
  // Deep copy traits
  for (const auto &[field, trait] : base->traits)
    traits[field] = TraitPtr(trait->clone());
}

Contract::Contract(ContractPtr base) : base{base} { reload_traits(base); }

void Contract::markTraits(TraitSet &marked) {
  for (auto it : traits) {
    it.second->mark(marked);
  }
}

std::optional<BaseType> Contract::view(const ContractState &cs, Field field,
                                       bool &found) const {
  if (auto search = traits.find(field); search != traits.end()) {
    return search->second->eval(cs);
  }
  found = false;
  return std::nullopt;
}

MaybeAlteration Contract::reload() {
  return base.transform([&](ContractPtr contract) {
    this->reload_traits(contract);
    return Alteration{AlterationType::Reload};
  });
}

bool Contract::modify(Field field, TraitPtr next) {
  if (auto search = traits.find(field); search != traits.end()) {
    next->modify(search->second);
    search->second = next;
    return true;
  }
  return false;
}

void Contract::replace(Field field, TraitPtr next) {
  traits.insert_or_assign(field, next);
}

} // namespace evok
