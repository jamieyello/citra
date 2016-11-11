// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <SDL.h>
#include "audio_core/audio_core.h"
#include "audio_core/sdl2_mike.h"
#include "common/logging/log.h"

namespace AudioCore {

struct SDL2Mike::Impl {
    unsigned int sample_rate = 0;

    SDL_AudioDeviceID audio_device_id = 0;

    static void Callback(void* impl_, u8* buffer, int buffer_size_in_bytes);
};

SDL2Mike::SDL2Mike() : impl(std::make_unique<Impl>()) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        LOG_CRITICAL(Audio_Sink, "SDL_Init(SDL_INIT_AUDIO) failed");
        impl->audio_device_id = 0;
        return;
    }

    SDL_AudioSpec desired_audiospec;
    SDL_zero(desired_audiospec);
    desired_audiospec.format = AUDIO_S16;
    desired_audiospec.channels = 2;
    desired_audiospec.freq = native_sample_rate;
    desired_audiospec.samples = 512;
    desired_audiospec.userdata = impl.get();
    desired_audiospec.callback = &Impl::Callback;

    SDL_AudioSpec obtained_audiospec;
    SDL_zero(obtained_audiospec);

    impl->audio_device_id =
        SDL_OpenAudioDevice(nullptr, true, &desired_audiospec, &obtained_audiospec, 0);
    if (impl->audio_device_id <= 0) {
        LOG_CRITICAL(Audio_Sink, "SDL_OpenAudioDevice failed");
        return;
    }

    impl->sample_rate = obtained_audiospec.freq;
    // SDL2 audio devices start out paused, unpause it:
    SDL_PauseAudioDevice(impl->audio_device_id, 0);
}

} // namespace
