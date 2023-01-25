#include <stdlib.h>
#include <limits.h>

/*
    src[]  = L1 R1 L2 R2 L3 R3 ...
    dst[0] = L1 L2 L3 ...
    dst[1] = R1 R2 R3 ...
*/

void deinterleave_audio(int16_t *src, int16_t **dst, size_t num_samples, uint16_t num_channels)
{
    for (uint16_t ch = 0; ch < num_channels; ++ch) {
        for (size_t idx = 0; idx < num_samples; ++idx) {
            dst[ch][idx] = src[idx * num_channels + ch];
        }
    }
}

void interleave_audio(int16_t **src, int16_t *dst, size_t num_samples, uint16_t num_channels)
{
    for (uint16_t ch = 0; ch < num_channels; ++ch) {
        for(size_t idx = 0; idx < num_samples; ++idx) {
            dst[idx * num_channels + ch] = src[ch][idx];
        }
    }
}


/*
    Convert fixed point value Q0.15 to float value
*/

void convert_fixed_to_float(int16_t **src, float **dst, size_t num_samples, uint16_t num_channels)
{
    for (uint16_t ch = 0; ch < num_channels; ++ch) {
        for(size_t idx = 0; idx < num_samples; ++idx) {
            float value = (float) src[ch][idx] / 32768;
            if (value > 1.0)
                value = 1.0;
            if (value < -1.0)
                value = -1.0;
            dst[ch][idx] = value;
        }
    }
}

void convert_float_to_fixed(float **src, int16_t **dst, size_t num_samples, uint16_t num_channels)
{
    for (uint16_t ch = 0; ch < num_channels; ++ch) {
        for(size_t idx = 0; idx < num_samples; ++idx) {
            int32_t value = (int32_t) (src[ch][idx] * 32768);
            if (value > 32768)
                value = 32768;
            if (value < -32767)
                value = -32767;
            dst[ch][idx] = value;
        }
    }
}
