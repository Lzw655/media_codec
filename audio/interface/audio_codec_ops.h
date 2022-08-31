#ifndef AUDIO_CODEC_OPS_H
#define AUDIO_CODEC_OPS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct audio_codec_t *audio_codec_handle_t;

int audio_codec_init(audio_codec_handle_t handle);
void audio_codec_deinit(audio_codec_handle_t handle);
int audio_codec_encode(audio_codec_handle_t handle);
int audio_codec_decode(audio_codec_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif