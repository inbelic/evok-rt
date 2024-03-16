#include "../../include/Core/Contract.h"

void Contract::reload_traits(ContractPtr base) {
  traits.clear();
  // Deep copy traits
  for (const auto& [field, trait] : base->traits)
    traits[field] = TraitPtr(trait->clone());
}

Contract::Contract(ContractPtr base) : base { base } {
  reload_traits(base);
}

Alteration Contract::reload() {
  return base.transform([&](ContractPtr contract) {
    this->reload_traits(contract);
    return _Alteration{AlterationType::Reload};
  });
}

Alteration Contract::modify(Field field, TraitPtr next) {
  if (auto search = traits.find(field); search != traits.end()) {
    search->second->modify(std::move(next));
    return _Alteration{AlterationType::Alter};
  }
  return std::nullopt;
}

Alteration Contract::replace(Field field, TraitPtr next) {
  traits.insert_or_assign(field, std::move(next));
  return _Alteration{AlterationType::Alter};
}
