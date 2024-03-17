#include "../../include/evok/Core/Ledger.h"
#include "../../include/evok/Core/FieldMask.h"

#include <queue>

namespace evok {

static ID computeID(const Contracts &contracts) {
  // Simply increment on the maximum contract ID
  ID gen_id = 0;
  for (const auto &[key, contract] : contracts) {
    if (key > gen_id)
      gen_id = key;
  }
  return gen_id + 1;
}

ID Ledger::addContract(ContractPtr contract) {
  ID id = computeID(contracts);
  contracts[id] = contract;
  return id;
}

using WorkQueue = std::queue<std::pair<ID, FieldMask>>;

static WorkQueue initWorkQueue(const Contracts &contracts) {
  WorkQueue work_queue;

  // If field is set then it is unresolved (this will set all fields to
  // unresolved)
  for (const auto &[id, _contract] : contracts)
    work_queue.push({id, baseMask});
  return work_queue;
}

// Naive workload implementation
ContractState Ledger::view() {
  // Init our variables
  bool found = true;
  ContractState cs{};
  cs.history = &this->history;
  WorkQueue work_queue = initWorkQueue(contracts);

  // Iteratively work through the queue as long as there are unresolved trait
  // evaluations
  for (; !work_queue.empty(); work_queue.pop()) {
    // Retrieve the current work item
    std::pair<ID, FieldMask> work_pair = work_queue.front();
    auto id = work_pair.first;
    auto mask = work_pair.second;

    // Find the contract to work on
    auto search = contracts.find(id);
    // If not found then we can skip (shouldn't happen)
    if (search == contracts.end())
      continue;
    // Otherwise, extract out for ease of use
    ContractPtr contract = search->second;

    // Iterate through all possible fields be evaluated
    for (uint8_t field_id = 0; field_id < NUM_FIELDS; field_id++) {
      // If field is set then it is unresolved, so attempt to evaluate it
      Field field = FIELDS[field_id];
      if (isFieldSet(mask, field)) {
        found = true;
        auto val = contract->view(cs, field, found);
        // If we successfully evaluated it then we can insert it into the
        // ContractState, cs
        if (val)
          cs.insert(id, field, *val);
        // When successfully evaluated or not found then we the field is
        // resolved (if it is not found then the contract does not have the
        // field and there is nothing to resolve)
        if (val || !found)
          mask = clearField(mask, field);
      } else {
        mask = clearField(mask, field);
      }
    }
    // If the mask is 0 then all fields are resolved, otherwise we will need to
    // put it back on the work queue
    if (mask != 0)
      work_queue.push({id, mask});
  }
  return cs;
}

} // namespace evok
