#pragma once

#include <format>
#include <iostream>

template <typename... Args>
void LOG(std::string_view format, Args&&... args)
{
    std::cout << std::vformat(format, std::make_format_args(std::forward<Args>(args)...)) << std::endl;
}