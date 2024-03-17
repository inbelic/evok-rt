#include "../include/Core/Contract.h"
#include "../include/Core/Ledger.h"
#include "../include/Traits/Common.h"
#include "../include/Core/Action.h"

#include <iostream>
#include <utility>
#include <string>

std::string fieldString(Field field) {
  switch (field) {
    case Field::Undef: return "Undef";
    case Field::SetID: return "SetID";
    case Field::ContractID: return "ContractID";
  }
}

void printLedger(Ledger ledger) {
  auto cs = ledger.view();

  for (const auto& [id, traits] : cs.ts) {
    std::cout << std::to_string(id) << ": ";
    for (const auto& [field, val] : traits)
      std::cout << fieldString(field) << "->" << std::to_string(val) << " ";
    std::cout << std::endl;
  }
}

int main() {
  Ledger ledger = Ledger();
  ContractPtr base = new Contract();
  auto one   = TraitPtr(new ConstantTrait(1));
  auto two   = TraitPtr(new ConstantTrait(2));
  auto three = TraitPtr(new ConstantTrait(3));
  auto four  = TraitPtr(new ConstantTrait(4));
  base->replace(Field::SetID, std::move(one));
  base->replace(Field::ContractID, std::move(two));

  ContractPtr c1 = new Contract(base);
  c1->replace(Field::SetID, std::move(three));

  ContractPtr c2 = new Contract(base);
  c2->replace(Field::ContractID, std::move(four));

  ledger.addContract(c1);
  ledger.addContract(c2);

  printLedger(ledger);

  auto shift4 = TraitPtr(new ClampedShiftTrait(true, 4));
  auto shift5 = TraitPtr(new ClampedShiftTrait(false, 5));
  auto shift4c = TraitPtr(shift4->clone());

  c1->modify(Field::ContractID, std::move(shift4));
  c2->modify(Field::SetID, std::move(shift5));
  c2->modify(Field::SetID, std::move(shift4c));

  printLedger(ledger);

  delete base;
  delete c1;
  delete c2;

  return 0;
}
