#include "dmc.h"
#include "walker.h"

DMC::DMC(System* system, int N_c)
{
    m_numberOfWalkers = N_c;
    m_system = system;

    m_trialWalker = new Walker(m_numberOfParticles, m_numberOfDimensions);
    m_setOfWalkers = new Walker*[m_numberOfWalkers];

    for (int i = 0; i < m_numberOfWalkers; i++) {
        m_setOfWalkers[i] = new Walker(m_numberOfParticles, m_numberOfDimensions);
    }
}

void DMC::runDMC() {
    //equlibration steps:
    for (int cycle = 1; cycle <= m_numberOfEquilibrationSteps; cycle++) {
        for (int iWalker = 0; iWalker < m_numberOfWalkers; iWalker++) {
            moveWalkerDMC(iWalker);
        }
    }

    //actual dmc steps:
    for (int cycle = 1; cycle <= m_numberOfWalkers; cycle++) {
        for (int iWalker = 0; iWalker < m_numberOfWalkers; iWalker++) {
            moveWalkerDMC(iWalker);
        }

    }


}

void DMC::setEquilibrationSteps(int equilibration) {
    m_numberOfEquilibrationSteps = equilibration;
}

void DMC::copyWalker(Walker* originalWalker, Walker* newWalker) {
    newWalker->setPosition(originalWalker->getPosition());
    newWalker->setE(originalWalker->getE());
}

void DMC::moveWalkerDMC(int iWalker) {
    copyWalker(m_setOfWalkers[iWalker], m_trialWalker);

    for (int currentParticle = 0; currentParticle < m_numberOfParticles; currentParticle++){
        bool acceptedStep;
        // Ask Metropolis step functions whether the step was accepted or not
        acceptedStep = m_trialWalker->getSystem()->metropolisStepImpSampling(currentParticle);

        //This is the sampling part of the iteration:

        //if (i >= m_trialWalker->getSystem()->getNumberOfMetropolisSteps()){
        //    // Sample energy etc.
        //    m_trialWalker->getSystem()->m_sampler->sample(acceptedStep);
        //}
    }
}
