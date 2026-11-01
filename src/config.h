#ifndef ORBITRA_CONFIG_H
#define ORBITRA_CONFIG_H

#include "common.h"

namespace CONFIG_GRAPHICS_FLAGS {
    enum ENUM: u8 {
        NONE = 0,
        VSYNC = 0b1,
        WINDOW_BORDERLESS = 0b10,
        WINDOW_FULLSCREEN = 0b100
    };
}

struct orb_Config {
    struct Graphics {
        CONFIG_GRAPHICS_FLAGS::ENUM flags = CONFIG_GRAPHICS_FLAGS::NONE;
        u16 fps = 165;
        struct Window {
            u16 w = 640, h = 480;
        } window;
    } graphics;
    struct {
        u8 sfx = 255, music = 255;
    } sound;
};

fs::path config_get_path();
orb_Error config_write(orb_Config &config, fs::path path = config_get_path());
orb_Config config_init();

#endif
