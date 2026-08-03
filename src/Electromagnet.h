#pragma once

#include <Arduino.h>

#define PWMA 14
#define STBY 27
#define AIN1 26
#define AIN2 25

enum Polarity {
    NORTH,
    SOUTH
};

enum class Strength {
    WEAK = 0,
    MEDIUM = 100,
    STRONG = 255
};

class Electromagnet{
    private:
        Polarity polarity;
        bool isOn;
    public:
        Electromagnet();
        void enable(){digitalWrite(STBY, HIGH);}
        void disable(){digitalWrite(STBY, LOW);}
        void setPolarity(Polarity polarity);
        void flipPolarity();
        void setStrength(Strength strength);
        Polarity getPolarity(){return polarity;}
};