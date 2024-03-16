#ifndef _CORE_ACTION_HEADER_
#define _CORE_ACTION_HEADER_

// A function that will check if the action triggers. ID denotes the ID of the
// action that the contract is owned by.
struct Trigger {
  virtual bool isTriggered(const ContractState&, ID /*ContractID*/) = 0;
  virtual ~Trigger();
};
// Will be a pointer to a trigger arena
using TriggerPtr = std::unique_ptr<Trigger>;

// The types of targeting
enum class TargetType : uint8_t {
  Given, // We already know which contract to target
  Inquire, // We will need to request a target from the domain
  Void // We will need to create a new contract for the action to use
};

struct Target {
  ID resolveID; // Which resolve will be acted with
  TargetType type;
  std::vector<ID> domain; // The range of possible targets to inquire from
};

// A function that will generate a set of targets for an Action to resolve on
struct Targeting {
  virtual std::vector<Target> getTargets(const ContractState&, ID) = 0;
  virtual ~Targeting();
};
// Will be a pointer to a targeting arena
using TargetingPtr = std::unique_ptr<Targeting>;

// A function that will alter a contract and output matching alterations
struct Resolve {
  virtual Alterations resolve(ID, ID, const ContractState&, ContractPtr) = 0;
  virtual ~Resolve();
};
// Will be a pointer to a resolve arena
using ResolvePtr = std::unique_ptr<Resolve>;

struct Action {
  ID statementID = 0; // Allows for text association of the the action

  // Determines whether the targeting should occur on trigger or if it should
  // occur on resolve
  bool targetOnTrigger;
  TriggerPtr trigger;
  TargetingPtr targeting;

  virtual ~Action() {};
};

#endif // _CORE_ACTION_HEADER_
