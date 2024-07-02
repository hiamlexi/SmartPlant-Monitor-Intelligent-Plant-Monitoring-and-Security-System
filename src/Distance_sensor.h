#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

#include <Arduino.h>  // Include Arduino core library for types and functions

extern const int trigPin;
extern const int echoPin;
extern const int buzzer;
extern const int ledPin;

void setupDistanceSensor() {
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
    pinMode(buzzer, OUTPUT);
    pinMode(ledPin, OUTPUT);
}

// Function to check distance sensor and return distance
int checkDistanceSensor() {
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    int distance = duration * 0.034 / 2;

    // Handle safety distance logic
    if (distance <= 5) {
        digitalWrite(ledPin, HIGH);
    } else {
        digitalWrite(ledPin, LOW);
    }

    // Return the calculated distance
    return distance;
}

#endif
