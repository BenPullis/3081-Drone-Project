#include "VariantStrategy.h"

Disease VariantStrategy::processDisease(const Disease& disease) const {
    Disease variant = disease;
    variant.setDuration(disease.getDuration() + 2);
    variant.setSeverity(disease.getSeverity() + 2);
    variant.setName(disease.getName() + "I");
    // todo: check if disease ends with -I, if so increment roman numeral properly
    return variant;
}
