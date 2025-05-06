#include "VariantStrategy.h"

Disease VariantStrategy::processDisease(const Disease& disease) const {
    Disease variant = disease;
    variant.setDuration(disease.getDuration() + 2);
    variant.setSeverity(disease.getSeverity() + 2);
    variant.setName(disease.getName() + "I");
    variant.incrementVariant();
    return variant;
}
