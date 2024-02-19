#pragma once
#include <span>
#include "types.h"

template<typename T> struct Tensor {
    uint32_t DimensionPtr;
    uint32_t DimensionLen;
    TensorType Type;
    uint32_t DataPtr;
    uint32_t TensorLen;

    Tensor(const std::span<const uint32_t> &dimensions, TensorType type, const std::span<const T> &data) : Type(type) {
        DimensionPtr = (uint32_t)dimensions.data();
        DimensionLen = dimensions.size();
        DataPtr = (uint32_t)data.data();
        TensorLen = data.size();
    }
};