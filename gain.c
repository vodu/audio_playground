#include <stdlib.h>

void gain_process_stereo(float **audio_buffer, size_t num_samples, uint16_t num_channels)
{
    for (uint16_t ch = 0; ch < num_channels; ++ch) {
        for (size_t idx = 0; idx < num_samples; ++idx) {
            audio_buffer[ch][idx] = audio_buffer[ch][idx] * 0.5;
        }
    }
}
