cmake_minimum_required(VERSION 3.6)
add_library(
        imgui STATIC
        imconfig.h
        imgui.cpp
        imgui.h
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_impl_glfw_gl3.cpp
        imgui_impl_glfw_gl3.h
        imgui_internal.h
        stb_rect_pack.h
        stb_textedit.h
        stb_truetype.h
        )