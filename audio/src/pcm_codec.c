#include <stdlib.h>
#include "../interface/audio_codec_interface.h"
#include "../include/audio_codec.h"

typedef struct {
    audio_codec_t base;
    void *in_dev;
    void *out_dev;
    void *work;
    bool work_need_free;
    int work_index;
    size_t work_bytes_sz;
    size_t audio_bytes_sz;
    int sample_bytes;
    audio_encode_read_t read;
    audio_encode_read_t write;
} pcm_codec_t;

static int init(audio_codec_handle_t codec);
static void deinit(audio_codec_handle_t codec);
static int encode(audio_codec_handle_t codec);

int audio_codec_new_pcm(audio_codec_config_t *config, audio_codec_handle_t *handle)
{
    if (!config || !handle) {
        AUDIO_LOG("invaild params");
        return -1;
    }
    pcm_codec_t *codec = (pcm_codec_t *)malloc(sizeof(pcm_codec_t));
    if (!codec) {
        AUDIO_LOG("malloc failed");
        return -1;
    }

    codec->in_dev = config->in_dev;
    codec->out_dev = config->out_dev;
    codec->work = config->work;
    codec->work_need_free = false;
    codec->work_bytes_sz = config->work_bytes_sz;
    codec->sample_bytes = config->sample_bits / 8;
    codec->audio_bytes_sz = config->audio_sample_sz * codec->sample_bytes;
    codec->read = config->read_func;
    codec->write = config->write_func;

    codec->base.init = init;
    codec->base.deinit = deinit;
    codec->base.encode = encode;

    *handle = &codec->base;

    return 0;
}

static int init(audio_codec_handle_t codec)
{
    pcm_codec_t *pcm_codec = (pcm_codec_t *)codec;
    void *work = pcm_codec->work;
    if (!work) {
        work = (void *)malloc(pcm_codec->work_bytes_sz * pcm_codec->sample_bytes);
        if (!work) {
            AUDIO_LOG("malloc failed");
            return -1;
        }
        pcm_codec->work_need_free = true;
        pcm_codec->work = work;
    }
    pcm_codec->work_index = 0;

    return 0;
}

static void deinit(audio_codec_handle_t codec)
{
    pcm_codec_t *pcm_codec = (pcm_codec_t *)codec;
    if (pcm_codec->work_need_free) {
        free(pcm_codec->work);
    }
    free(pcm_codec);
}

static int encode(audio_codec_handle_t codec)
{
    pcm_codec_t *pcm_codec = (pcm_codec_t *)codec;
    size_t work_bytes_sz = pcm_codec->work_bytes_sz;
    void *work = pcm_codec->work;
    int sample_bytes = pcm_codec->sample_bytes;
    size_t audio_bytes = pcm_codec->audio_bytes_sz;
    audio_encode_read_t read = pcm_codec->read;
    audio_encode_write_t write = pcm_codec->write;
    size_t work_index = pcm_codec->work_index;
    size_t res_bytes;
    size_t read_bytes = 0, write_bytes = 0;
    size_t target_bytes = work_bytes_sz;
    int i = 0, j = 0;

    do {
        if ((audio_bytes != 0) && (target_bytes + work_index > audio_bytes)) {
            target_bytes = audio_bytes - work_index;
        }
        read_bytes = 0;
        j = 0;
        while (read_bytes < target_bytes) {
            res_bytes = read(pcm_codec->in_dev, work, target_bytes - read_bytes);
            read_bytes += res_bytes;
            if ((res_bytes == 0) && (read_bytes < target_bytes)) {
                AUDIO_LOG("read error, count: %d-%d", i, j);
                return -1;
            }
            work += res_bytes;
            j++;
        }
        work -= target_bytes;
        write_bytes = 0;
        j = 0;
        while (write_bytes < target_bytes) {
            res_bytes = write(pcm_codec->out_dev, work, target_bytes - write_bytes);
            write_bytes += res_bytes;
            if ((res_bytes == 0) && (write_bytes < target_bytes)) {
                AUDIO_LOG("write error, count: %d-%d", i, j);
                return -1;
            }
            work += res_bytes;
            j++;
        }
        work -= target_bytes;
        work_index += target_bytes;
        i++;
    } while(work_index < audio_bytes);

    pcm_codec->work_index = (audio_bytes == 0) ? work_index : 0;

    return 0;
}
