#include "config.h"
#include "common.h"
#include "ini.h"
#include <filesystem>
#include <iostream>
#include <paths.h>
#include <string>

template<std::unsigned_integral T>
static bool parse_uint(const std::string &string, T &value) {
    try {
        value = static_cast<u8>(std::stoull(string));
        return true;
    }
    catch (...) {
        return false;
    }
}

static bool parse_bool(const std::string &string, bool &value) {
    if (string.empty()) return false;
    std::string lower = string;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    if (lower == "1" || lower == "true") {
        value = true;
        return true;
    }
    else if (lower == "0" || lower == "false") {
        value = false;
        return true;
    }
    else return false;
}

// TODO: if cwd not writeable, save in XDG_CONFIG_HOME
fs::path config_get_path() {
    fs::path config_dir = fs::current_path();
    config_dir.append("config.ini");
    return config_dir;
}

orb_Error config_write(orb_Config &config, fs::path path) {
    mINI::INIStructure ini;
    mINI::INIFile file(path);

    ini["graphics"]["fps"] = std::to_string(config.graphics.fps);
    ini["graphics"]["vsync"] =
        (config.graphics.flags & CONFIG_GRAPHICS_FLAGS::VSYNC) ? "true"
                                                               : "false";

    ini["graphics.window"]["w"] = std::to_string(config.graphics.window.w);
    ini["graphics.window"]["h"] = std::to_string(config.graphics.window.h);
    ini["graphics.window"]["borderless"] =
        (config.graphics.flags & CONFIG_GRAPHICS_FLAGS::WINDOW_BORDERLESS)
            ? "true"
            : "false";
    ini["graphics.window"]["fullscreen"] =
        (config.graphics.flags & CONFIG_GRAPHICS_FLAGS::WINDOW_FULLSCREEN)
            ? "true"
            : "false";

    ini["audio"]["sfx"] = std::to_string(config.sound.sfx);
    ini["audio"]["music"] = std::to_string(config.sound.music);

    if (!file.write(ini, true)) {
        std::cout << "Failed to write config.ini\n";
        return orb_Error::FWRITE_ERROR;
    }

    return orb_Error::SUCCESS;
}

orb_Error config_read(fs::path path, orb_Config& config) {
    mINI::INIStructure ini;
    mINI::INIFile file(path);

    if (!file.read(ini)) {
        std::cout << "Failed to read config\n";
        return orb_Error::GENERIC;
    }

    config = {};
    bool dirty = false;

    std::string g_fps               = ini["graphics"]["fps"];
    std::string g_vsync             = ini["graphics"]["vsync"];
    std::string g_window_w          = ini["graphics.window"]["w"];
    std::string g_window_h          = ini["graphics.window"]["h"];
    std::string g_window_borderless = ini["graphics.window"]["borderless"];
    std::string g_window_fullscreen = ini["graphics.window"]["fullscreen"];
    std::string a_sfx               = ini["audio"]["sfx"];
    std::string a_music             = ini["audio"]["music"];

    u16 fps;
    if (parse_uint(g_fps, fps)) config.graphics.fps = fps;
    else dirty = true;

    bool b;
    if (parse_bool(g_vsync, b) && b)
        config.graphics.flags = static_cast<CONFIG_GRAPHICS_FLAGS::ENUM>(
            config.graphics.flags | CONFIG_GRAPHICS_FLAGS::VSYNC);
    else if (!parse_bool(g_vsync, b)) dirty = true;

    if (parse_bool(g_window_borderless, b) && b)
        config.graphics.flags = static_cast<CONFIG_GRAPHICS_FLAGS::ENUM>(
            config.graphics.flags | CONFIG_GRAPHICS_FLAGS::WINDOW_BORDERLESS);
    else if (!parse_bool(g_window_borderless, b)) dirty = true;

    if (parse_bool(g_window_fullscreen, b) && b)
        config.graphics.flags = static_cast<CONFIG_GRAPHICS_FLAGS::ENUM>(
            config.graphics.flags | CONFIG_GRAPHICS_FLAGS::WINDOW_FULLSCREEN);
    else if (!parse_bool(g_window_fullscreen, b)) dirty = true;

    u16 w, h;
    if (parse_uint(g_window_w, w)) config.graphics.window.w = w;
    else dirty = true;
    if (parse_uint(g_window_h, h)) config.graphics.window.h = h;
    else dirty = true;

    u8 sfx, music;
    if (parse_uint(a_sfx,   sfx))   config.sound.sfx   = sfx;
    else dirty = true;
    if (parse_uint(a_music, music)) config.sound.music = music;
    else dirty = true;

    if (dirty) {
        std::cout << "Config has missing fields, rewriting with defaults\n";
        return config_write(config, path);
    }

    return orb_Error::SUCCESS;
}

orb_Config config_init() {
    orb_Config config = {};
    fs::path config_file = config_get_path();

    if (!fs::exists(config_file))
        config_write(config, config_file);
    else
        config_read(config_file, config);

    return config;
}
