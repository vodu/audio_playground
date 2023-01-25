#include <stdio.h>

#include "audio_loader.c"
#include "gain.c"
#include "converter.c"

int main(void)
{
    // 
    audio_pcm_t audio = { 0 };
    audio.bitrate = 16;
    audio.num_channels = 2;

    //  load audio from file
    if (audio_load_pcm_stereo_16("audio/sine_1kHz_in.pcm", &audio) < 0) {
        fprintf(stderr, "Error: Unable to load audio data \n");
        return 1;
    }

    // create audio processing buffers (stereo) for fixed point type
    int16_t **audio_buffer_fxp = malloc(audio.num_channels * sizeof (int16_t));
    for (uint16_t ch = 0; ch < audio.num_channels; ++ch) {
        audio_buffer_fxp[ch] = malloc(audio.num_samples * sizeof (int16_t));
    }

    deinterleave_audio(audio.data, audio_buffer_fxp, audio.num_samples, audio.num_channels);

    // create audio processing buffers (stereo) for floating point type
    float **audio_buffer_fl = malloc(audio.num_channels * sizeof (float));
    for (uint16_t ch = 0; ch < audio.num_channels; ++ch) {
        audio_buffer_fl[ch] = malloc(audio.num_samples * sizeof (float));
    }
    
    convert_fixed_to_float(audio_buffer_fxp, audio_buffer_fl, audio.num_samples, audio.num_channels);

    // processing samples float type
    gain_process_stereo(audio_buffer_fl, audio.num_samples, audio.num_channels);

    convert_float_to_fixed(audio_buffer_fl, audio_buffer_fxp, audio.num_samples, audio.num_channels);

    interleave_audio(audio_buffer_fxp, audio.data, audio.num_samples, audio.num_channels);

    if (audio_pcm_save("audio/sine_1kHz_out.pcm", &audio) < 0) {
        fprintf(stderr, "Error: Unable to save audio data \n");
        return 1;
    }

    // clean up
    for (uint16_t ch = 0; ch < audio.num_channels; ++ch) {
        free(audio_buffer_fxp[ch]);
        free(audio_buffer_fl[ch]);
    }
    free(audio_buffer_fxp);
    free(audio_buffer_fl);


    audio_free(&audio);

    return 0;
}
