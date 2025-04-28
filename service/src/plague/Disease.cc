#include "Disease.h"

Disease::Disease(std::string name, float duration, float recoveryRate, float severity)
    : name(name), duration(duration), recoveryRate(recoveryRate), severity(severity) {}

std::string Disease::getName() const {
    return name;
}

float Disease::getDuration() const {
    return duration;
}

float Disease::getRecoveryRate() const {
    return recoveryRate;
}

float Disease::getSeverity() const {
    return severity;
}

void Disease::setDuration(float newDuration) {
    duration = newDuration;
}

bool Disease::isCured() const {
    return duration <= 0;
}

void Disease::setSeverity(float s) {
    severity = s;
}

void Disease::setName(const std::string& n) {
    name = n;
}
