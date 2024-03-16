#ifndef _CORE_HISTORY_HEADER_
#define _CORE_HISTORY_HEADER_

#include <vector>
#include "Alteration.h"

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
    History() {};
};

#endif // _CORE_HISTORY_HEADER_
