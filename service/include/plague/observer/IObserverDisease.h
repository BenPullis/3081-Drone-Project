#ifndef IOBSERVERDISEASE_H_
#define IOBSERVERDISEASE_H_

#include "Disease.h"

/**
 * @interface IObserverDisease
 * @brief Interface for receiving a disease from a publisher.
 */
class IObserverDisease {
public:
    virtual ~IObserverDisease() = default;

    /**
     * @brief Called when an observer receives a disease.
     * @param disease The Disease object received.
     */
    virtual void onDiseaseReceived(const Disease& disease) = 0;
};

#endif
