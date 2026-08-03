#include "Electromagnet.h"

Electromagnet::Electromagnet()
{
    pinMode(PWMA, OUTPUT);
    pinMode(STBY, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
}

void Electromagnet::setPolarity(Polarity polarity)
{
    digitalWrite(AIN1, polarity == Polarity::NORTH ? HIGH : LOW);
    digitalWrite(AIN2, polarity == Polarity::NORTH ? LOW : HIGH);
}

void Electromagnet::flipPolarity()
{
    polarity = polarity == Polarity::NORTH ? Polarity::SOUTH : Polarity::NORTH;
}

void Electromagnet::setStrength(Strength strength)
{
    analogWrite(PWMA, static_cast<uint8_t>(strength));
}
