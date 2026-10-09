#ifndef ACCEPTSTRATEGY_H_
#define ACCEPTSTRATEGY_H_

#include "IReactionStrategy.h"

/**
 * @class AcceptStrategy
 * @brief Accepts and returns the disease without any modification.
 */
class AcceptStrategy : public IReactionStrategy {
public:

    /**
    * @brief Return the given disease unchanged.
    * @param disease The incoming disease.
    * @return A copy of the disease (no mutation applied).
    */
    Disease processDisease(const Disease& disease) const override;
};

#endif
