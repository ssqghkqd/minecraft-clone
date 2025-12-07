// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2025 ss
//
module;

export module impl:Error;

namespace mc::impl::error
{
export enum class ErrorType
{
    file_not_found,
    file_open_failed,

    shader_vert_failed,
    shader_frag_failed,
    shader_program_failed,

    init_glfw_failed,
    init_glad_failed,

    window_create_window_failed,

    texture_load_failed
};

export const char* getError(ErrorType type)
{
    switch (type)
    {
        case ErrorType::file_not_found:
            return "File not found";
        case ErrorType::file_open_failed:
            return "File open failed";
        case ErrorType::shader_vert_failed:
            return "Shader vert failed";
        case ErrorType::shader_frag_failed:
            return "Shader frag failed";
        case ErrorType::shader_program_failed:
            return "Shader program failed";
        case ErrorType::init_glfw_failed:
            return "Init GLFW failed";
        case ErrorType::init_glad_failed:
            return "Init GLAD failed";
        case ErrorType::window_create_window_failed:
            return "Window creation failed";
        case ErrorType::texture_load_failed:
            return "Texture load failed";
        default:
            return "Unknown error";
    }
}
} // namespace mc::impl::error