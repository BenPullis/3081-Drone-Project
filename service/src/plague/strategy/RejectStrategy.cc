#include "RejectStrategy.h"

Disease RejectStrategy::processDisease(const Disease& disease) const {
    Disease rejected = disease;
    rejected.setDuration(0);
    return rejected;
}
