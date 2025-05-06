#ifndef IREACTIONSTRATEGY_H_
#define IREACTIONSTRATEGY_H_

#include "Disease.h"

/**
 * @interface IReactionStrategy
 * @brief Base class for deciding how a human reacts to incoming diseases.
 */
class IReactionStrategy {
public:
    virtual ~IReactionStrategy() = default;

    /**
     * @brief Returns the processed disease (may be rejected, mutated, or accepted).
    * @param disease The incoming disease.
    * @return Some new disease that can have an applied effect.
     */
    virtual Disease processDisease(const Disease& disease) const = 0;
};

#endif
