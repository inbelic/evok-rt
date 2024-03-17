#include "../include/evok/Alterations/Common.h"
#include "../include/evok/Core/Action.h"
#include "../include/evok/Core/Contract.h"
#include "../include/evok/Core/Ledger.h"
#include "../include/evok/Traits/Common.h"

#include <iostream>
#include <string>
#include <utility>

using namespace evok;

std::string fieldString(Field field) {
  switch (field) {
  case Field::Undef:
    return "Undef";
  case Field::SetID:
    return "SetID";
  case Field::ContractID:
    return "ContractID";
  }
}

void printLedger(Ledger ledger) {
  auto cs = ledger.view();

  for (const auto &[id, traits] : cs.ts) {
    std::cout << std::to_string(id) << ": ";
    for (const auto &[field, val] : traits)
      std::cout << fieldString(field) << "->" << std::to_string(val) << " ";
    std::cout << std::endl;
  }
}

int main() {
  Ledger ledger = Ledger();
  ContractPtr base = new Contract();
  alter::set(base, Field::SetID, 1);
  alter::set(base, Field::ContractID, 2);

  ContractPtr c1 = new Contract(base);
  alter::set(c1, Field::SetID, 3);

  ContractPtr c2 = new Contract(base);
  alter::set(c2, Field::ContractID, 4);

  ledger.addContract(c1);
  ledger.addContract(c2);

  printLedger(ledger);

  alter::clampedShift(c1, Field::ContractID, true, 4);
  alter::clampedShift(c2, Field::SetID, false, 5);
  alter::clampedShift(c2, Field::SetID, true, 3);

  printLedger(ledger);

  delete base;
  delete c1;
  delete c2;

  return 0;
}
