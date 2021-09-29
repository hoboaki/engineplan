// 文字コード：UTF-8
#pragma once

#include <ae/base/Os.hpp>

#define VULKAN_HPP_NO_EXCEPTIONS
#define VULKAN_HPP_TYPESAFE_CONVERSION

#if defined(AE_BASE_OS_WINDOWS)
#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#if defined(AE_BASE_OS_MACOSX)
#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
#define VK_USE_PLATFORM_METAL_EXT
#define VK_ENABLE_BETA_EXTENSIONS
#endif

#include <vulkan/vk_sdk_platform.h>

#include <vulkan/vulkan.hpp>

// EOF
