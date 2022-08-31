#include <stdio.h>
#include "media_codec.h"

#if CONFIG_MEDIA_CODEC_LOG_PRINTF
media_codec_log_t media_codec_log = printf;
#else
media_codec_log_t media_codec_log = NULL;
#endif

void media_codec_log_register(media_codec_log_t log_func)
{
    media_codec_log = log_func;
}
