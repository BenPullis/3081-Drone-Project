#ifndef DISEASE_H
#define DISEASE_H

#include <string>

/**
 * @class Disease
 * @brief Represents a disease that can infect a human in the simulation.
 */
class Disease {
  private:
    std::string name;
    float duration;
    float radius;
    float recoveryRate;
    float severity;

  public:
    /**
    * @brief Constructs a new Disease object.
    * @param name Name of the disease.
    * @param duration Duration of the disease.
    * @param radius Radius of infection.
    * @param recoveryRate Rate at which the disease heals over time.
    * @param severity Severity of the disease.
    */
    Disease(std::string name, float duration, float radius, float recoveryRate, float severity);

    
    /** @brief Gets the name of the disease. */
    std::string getName() const;

    /** @brief Gets the current duration of the disease. */
    float getDuration() const;

    /** @brief Gets the infection radius of the disease. */
    float getRadius() const;

    /** @brief Gets the recovery rate of the disease. */
    float getRecoveryRate() const;

    /** @brief Gets the severity of the disease. */
    float getSeverity() const;

    /**
     * @brief Sets the duration of the disease.
     * @param newDuration The new duration value.
     */
    void setDuration(float newDuration);

    /**
     * @brief Updates the disease's state by decreasing its duration.
     */
    void update();

    /**
     * @brief Checks if the disease has been cured.
     * @return true if duration <= 0, false otherwise.
     */
    bool isCured() const;

    /**
     * @brief Sets the radius of the disease.
     * @param r The new radius value.
     */
    void setRadius(float r);

    /**
     * @brief Sets the severity of the disease.
     * @param severity The new severity value.
     */
    void setSeverity(float severity);
    
    /**
     * @brief Sets the name of the disease.
     * @param name The new name value.
     */
    void setName(const std::string& name);

};

#endif
