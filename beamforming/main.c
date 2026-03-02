#include "beamforming.h"
#include <stdint.h>

int main(void){

    float carrier_frequency = 5.8e9f;
    float c = 299792458.0f;
    float lambda = c / carrier_frequency;
    float dx = lambda / 2.0f;
    float dy = lambda / 2.0f;


    init(carrier_frequency, dx, dy);

    float u0 = 0.2f;
    float v0 = 0.2f;

    uint8_t output_phases[NUM_ELEMENTS];
    
    compute_phase_angles(u0, v0, output_phases);

    while (1) {
    // send output_phases to DAC here
    }
}



// (u,v) → 16 phase states → DAC
