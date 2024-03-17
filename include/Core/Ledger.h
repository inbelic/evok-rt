#ifndef _CORE_LEDGER_HEADER_
#define _CORE_LEDGER_HEADER_

#include "Contract.h"
#include "ContractState.h"
#include "History.h"

#include <map>

using Contracts = std::map<ID, ContractPtr>;

class Ledger {
private:
  Contracts contracts;
  History history;

public:
  Ledger(){};

  // Add a contract to the Ledger map and returned the generated ID
  ID addContract(ContractPtr);

  // Evaluate the traits of all contracts to get a state with types
  ContractState view();
};

#endif // _CORE_LEDGER_HEADER_
