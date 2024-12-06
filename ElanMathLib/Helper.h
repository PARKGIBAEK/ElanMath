#pragma once

#include <numbers>
#include <type_traits>
#include <concepts>
template <typename T>
concept Numeric = std::is_integral_v<T> || std::is_floating_point_v<T>;
constexpr double PI = std::numbers::pi;


template <typename T>
concept Countable = std::is_integral_v<T> || std::is_floating_point_v<T>;