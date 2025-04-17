#include "Disease.h"

Disease::Disease(std::string name, float duration, float radius, float recoveryRate, float severity)
    : name(name), duration(duration), radius(radius), recoveryRate(recoveryRate), severity(severity) {}

std::string Disease::getName() const {
    return name;
}

float Disease::getDuration() const {
    return duration;
}

float Disease::getRadius() const {
    return radius;
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

void Disease::setRadius(float r) {
    radius = r;
}

void Disease::setSeverity(float s) {
    severity = s;
}

void Disease::setName(const std::string& n) {
    name = n;
}
