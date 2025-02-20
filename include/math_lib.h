// include/math_lib.h
#pragma once
#define EXPORT __declspec(dllexport)

namespace MathLib {
    extern "C" {
        EXPORT int add(int a, int b);
    }
}
