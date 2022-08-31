#include <stdlib.h>
#include "../interface/audio_codec_interface.h"
#include "../interface/audio_codec_ops.h"

int audio_codec_init(audio_codec_handle_t handle)
{
    return handle->init(handle);
}

void audio_codec_deinit(audio_codec_handle_t handle)
{
    return handle->deinit(handle);
}

int audio_codec_encode(audio_codec_handle_t handle)
{
    return handle->encode(handle);
}

int audio_codec_decode(audio_codec_handle_t handle)
{
    return handle->encode(handle);
}
