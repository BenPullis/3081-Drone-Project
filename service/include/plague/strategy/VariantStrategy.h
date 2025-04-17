#ifndef VARIANTSTRATEGY_H_
#define VARIANTSTRATEGY_H_

#include "IReactionStrategy.h"
#include <string>

class VariantStrategy : public IReactionStrategy {
public:
    Disease processDisease(const Disease& disease) const override;
};

#endif
