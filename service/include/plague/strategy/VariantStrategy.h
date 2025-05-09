#ifndef VARIANTSTRATEGY_H_
#define VARIANTSTRATEGY_H_

#include "IReactionStrategy.h"
#include <string>

/**
 * @class VariantStrategy
 * @brief Mutates the disease and returns a new variant.
 */
class VariantStrategy : public IReactionStrategy {
public:
    /**
     * @brief Mutates the disease and returns a new variant.
     * @param disease The incoming disease.
     * @return A mutated version of the disease with increased severity and duration.
     */
    Disease processDisease(const Disease& disease) const override;
};

#endif
