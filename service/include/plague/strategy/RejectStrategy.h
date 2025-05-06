#ifndef REJECTSTRATEGY_H_
#define REJECTSTRATEGY_H_

#include "IReactionStrategy.h"

/**
 * @class RejectStrategy
 * @brief Rejects and returns an expired disease.
 */
class RejectStrategy : public IReactionStrategy {
public:
    /**
    * @brief Return an expired version of the disease.
    * @param disease The incoming disease.
    * @return An expired copy of the disease, with a duration of 0.
    */
    Disease processDisease(const Disease& disease) const override;
};

#endif
