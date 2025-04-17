#ifndef REJECTSTRATEGY_H_
#define REJECTSTRATEGY_H_

#include "IReactionStrategy.h"

class RejectStrategy : public IReactionStrategy {
public:
    Disease processDisease(const Disease& disease) const override;
};

#endif
