#ifndef AUDIO_CODEC_H
#define AUDIO_CODEC_H

#include <stdbool.h>
#include <stddef.h>
#include "../interface/audio_codec_ops.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    AUDIO_CODEC_SAMPLE_8BITS = 8,
    AUDIO_CODEC_SAMPLE_16BITS = 16,
} audio_codec_sample_bits_t;

typedef size_t (*audio_encode_read_t)(void *in_dev, void *buff, size_t data_bytes_sz);
typedef size_t (*audio_encode_write_t)(void *out_dev, void *buff, size_t data_bytes_sz);

typedef struct {
    void *in_dev;
    void *out_dev;
    void *work;
    size_t work_bytes_sz;
    size_t audio_sample_sz;
    audio_codec_sample_bits_t sample_bits;
    audio_encode_read_t read_func;
    audio_encode_read_t write_func;
} audio_codec_config_t;

int audio_codec_new_pcm(audio_codec_config_t *config, audio_codec_handle_t *handle);

#ifdef __cplusplus
}
#endif

#endif