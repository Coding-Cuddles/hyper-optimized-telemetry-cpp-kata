#pragma once

#include <cstring>
#include <vector>

class BitConverter {
public:
    template <typename T, typename U> static std::vector<char> get_bytes(U value)
    {
        std::vector<char> bytes(sizeof(T));
        std::memcpy(bytes.data(), &value, sizeof(T));
        return bytes;
    }

    template <typename T> static T to_integer(const std::vector<char>& bytes)
    {
        T value;
        std::memcpy(&value, bytes.data(), sizeof(T));
        return value;
    }
};
