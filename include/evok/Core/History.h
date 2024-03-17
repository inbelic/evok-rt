#ifndef _EVOK_CORE_HISTORY_HEADER_
#define _EVOK_CORE_HISTORY_HEADER_

#include "Alteration.h"
#include <vector>

namespace evok {

struct Event {
  ID actor;
  ID recipient;
  Alteration alteration;
};

class History {
private:
  std::vector<Event> curr;
  std::vector<Event> past;

public:
  History(){};
};

} // namespace evok

#endif // _EVOK_CORE_HISTORY_HEADER_
