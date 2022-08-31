#ifndef AUDIO_CODEC_INTERFACE_H
#define AUDIO_CODEC_INTERFACE_H

#include "../../media_codec_types.h"

#if CONFIG_AUDIO_CODEC_LOG
#define AUDIO_LOG(fmt, ...)           MEDIA_LOG("%s:%d (%s): "fmt"\n",      \
                                        __FILE__, __LINE__,                 \
                                        __FUNCTION__, ##__VA_ARGS__)
#else
#define AUDIO_LOG
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct audio_codec_t audio_codec_t;

struct audio_codec_t {
    int (* init)(audio_codec_t *handle);
    void (* deinit)(audio_codec_t *handle);
    int (* encode)(audio_codec_t *handle);
    int (* decode)(audio_codec_t *handle);
};

#ifdef __cplusplus
}
#endif

#endif