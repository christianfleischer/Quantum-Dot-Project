#ifndef SQUAREWELL_H
#define SQUAREWELL_H

#include "wavefunction.h"

class SquareWell : public WaveFunction {
public:
    SquareWell(class System* system, double omega, double V0);
    vec harmonicOscillatorBasis(mat x, int n);
    vec potential (vec r, double L);
private:
    double m_V0 = 0;
};

#endif // SQUAREWELL_H
