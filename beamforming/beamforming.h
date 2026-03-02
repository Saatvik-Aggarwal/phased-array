
#ifndef BEAMFORMING_H
#define BEAMFORMING_H

#include <stdint.h>


#define ROWS 4
#define COLS 4
#define NUM_ELEMENTS (ROWS * COLS)



// carrier_frequency: RF carrier frequency in Hz
// d_x: inter-element spacing along the x-axis in meters
// d_y: inter-element spacing along the y-axis in meters

void beamforming_init (float carrier_frequency, float d_x, float d_y);


// Beamforming Algorithm
// u0: sine-space direction cosine along the x-axis 
// v0: sine-space direction cosine along the y-axis 
// output_phases: output array of 16 quantized 4-bit phase states (0–15)

void beamforming_compute (float u_0, float v_0, uint8_t output_phases[NUM_ELEMENTS]);

#endif // BEAMFORMING_H
