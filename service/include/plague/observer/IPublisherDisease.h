#ifndef IPUBLISHERDISEASE_H_
#define IPUBLISHERDISEASE_H_

class Human;

/**
 * @interface IPublisherDisease
 * @brief Interface for publishing diseases to nearby humans.
 */
class IPublisherDisease {
public:
    virtual ~IPublisherDisease() = default;

    /**
     * @brief Publishes a disease to all subscribers within range.
     */
    virtual void publishDisease() = 0;

    /**
     * @brief Subscribes a human to this publisher's disease broadcast.
     * @param human The Human to subscribe.
     */
    virtual void subscribe(Human* human) = 0;

    /**
     * @brief Unsubscribes a human from this publisher.
     * @param human The Human to remove.
     */
    virtual void unsubscribe(Human* human) = 0;
};

#endif
