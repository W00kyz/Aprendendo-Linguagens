// MathHelpers.hpp

#ifndef MATH_HELPERS_HPP
#define MATH_HELPERS_HPP

namespace MathHelpers {
    inline float toRadians(float degrees) {
        return degrees * 3.14159265358979323846f / 180.0f;
    }

    inline float toDegrees(float radians) {
        return radians * 180.0f / 3.14159265358979323846f;
    }
}

#endif // MATH_HELPERS_HPP
