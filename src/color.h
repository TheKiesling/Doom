#pragma once
#include <iostream>

struct Color {
    uint8_t r;
    uint8_t g; 
    uint8_t b; 

    Color() : r(0), g(0), b(0) {}

    Color(uint8_t red, uint8_t green, uint8_t blue)
    : r(clamp(red)), g(clamp(green)), b(clamp(blue)) {}

    friend std::ostream& operator<<(std::ostream& os, const Color& color) {
        os << "RGB(" << static_cast<int>(color.r) << ", " << static_cast<int>(color.g) << ", " << static_cast<int>(color.b) << ")";
        return os;
    }

    Color operator+(const Color& other) const {
        return Color (
            (int(r) + int(other.r)),
            (int(g) + int(other.g)),
            (int(b) + int(other.b))
        );
    }

    Color operator*(float value) const {
        return Color (
            static_cast<uint8_t>(r * value),
            static_cast<uint8_t>(g * value),
            static_cast<uint8_t>(b * value)
        );
    }

private:
    uint8_t clamp(uint8_t value) {
        return value < 0 ? 0 : (value > 255 ? 255 : static_cast<uint8_t>(value));
    }

};
