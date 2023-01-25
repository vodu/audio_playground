#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
signed 16bit pcm
little endian
2 channels (stereo) interleaved
44100 Hz samplerate
*/

typedef struct audio_pcm_t {
    int16_t *data;
    size_t size;
    size_t num_samples;
    uint16_t bitrate;
    uint16_t num_channels;
} audio_pcm_t;

int audio_load_pcm_stereo_16(const char* filename, audio_pcm_t *audio)
{
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error: Unable to open file\n");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    audio->size = ftell(file);
    rewind(file);
    printf("audio file size: %zu \n", audio->size);

    int16_t bytes_per_sample = audio->bitrate / 8;
    audio->num_samples = audio->size / bytes_per_sample / audio->num_channels;
    printf("audio num sampes: %zu \n", audio->num_samples);
    printf("audio num channels: %d \n", audio->num_channels);

    audio->data = malloc(audio->size * sizeof *audio->data);
    if (!audio->data) {
        fprintf(stderr, "Error: Unable to allocate memory for audio->data \n");
        fclose(file);
        return -1;
    }

    size_t read_size = fread(audio->data, 1, audio->size, file);
    printf("read file size: %zu \n", read_size);

    if (file) {
        fclose(file);
    }
    return 0;
}

int audio_pcm_save(const char *filename, audio_pcm_t *audio)
{
    FILE *file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Error: Unable to open file \n");
        return -1;
    }

    fwrite(audio->data, 1, audio->size, file);
    fflush(file);

    if (file) {
        fclose(file);
    }
    return 0;
}

void audio_free(audio_pcm_t *audio)
{
    free(audio->data);
    audio->data = NULL;
    audio->size = 0;
    audio->num_samples = 0;
    audio->num_channels = 0;
    audio->bitrate = 0;
}
