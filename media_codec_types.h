#ifndef MEDIA_CODEC_TYPES_H
#define MEDIA_CODEC_TYPES_H

#include "media_codec.h"

#if CONFIG_MEDIA_CODEC_LOG
#define MEDIA_LOG(fmt, ...)     media_codec_log(fmt, ##__VA_ARGS__)

#else
#define MEDIA_LOG(fmt, ...)
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern media_codec_log_t media_codec_log;

#ifdef __cplusplus
}
#endif

#endif