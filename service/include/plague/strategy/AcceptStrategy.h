#ifndef ACCEPTSTRATEGY_H_
#define ACCEPTSTRATEGY_H_

#include "IReactionStrategy.h"

class AcceptStrategy : public IReactionStrategy {
public:
    Disease processDisease(const Disease& disease) const override;
};

#endif
