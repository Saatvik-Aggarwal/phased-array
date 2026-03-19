#include "beamforming.h"
#include <math.h>

#define SPEED_OF_LIGHT_MPS 299792458.0f // metres per second
#define BEAMFORMING_PI 3.14159265358979323846f

static float k = 0.0f; // wave number
static float dx = 0.0f; // x spacing
static float dy = 0.0f; // y spacing

// Static Helper Functions


// Wraps angle from radians to to [0,2pi]
static float wrap(float x){
    
    float y = fmodf(x, 2.0f * BEAMFORMING_PI);

    if (y < 0.0f){
        y += 2.0f * BEAMFORMING_PI;
    }
    return y;
}


// Maps phase from radians to 4 bit state [0, 15]
static uint8_t quantize_4_bit(float phase_radians){

    float normalized = phase_radians / (2.0f * BEAMFORMING_PI);  // [0,1)
    uint8_t state = (uint8_t)(normalized * 16.0f);               // nearest integer  
    
    return state & 0x0F;                              // modulo 16
}



// Store elemtent spacing and precomputes wave number
void beamforming_init (float carrier_frequency, float d_x, float d_y){

    if (carrier_frequency <= 0.0f || d_y <= 0.0f || d_x <= 0.0f) return;
    dx = d_x;
    dy = d_y;

    k = 2.0f * BEAMFORMING_PI * (carrier_frequency / SPEED_OF_LIGHT_MPS);

}

// Computes phases for each antenna
// Applies sign convention, wraps, quantizes
// OUTPUTS 16 states
void beamforming_compute (float u_0, float v_0, uint8_t output_phases[NUM_ELEMENTS]){
   
    if ((u_0*u_0 + v_0*v_0) > 1.0f) return;

    for (int m = 0; m < ROWS; m++){
        for (int n = 0; n < COLS; n++){
            float phase = -k * ((float)m * dy * v_0 + (float)n * dx * u_0);

            float wrapped = wrap(phase);

            // flatten 4x4 array so each element maps cleanly to DAC channel
            // check logic below!!!! confrm with PCB wiring

            output_phases[m * COLS + n] = quantize_4_bit(wrapped);

        }
    }
}






