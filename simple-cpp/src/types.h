#pragma once
#include <cstdint>

enum GraphEncoding {
    Openvino = 0,
    Onnx,
    Tensorflow,
    Pytorch,
    TensorflowLite,
    Autodetec,
    Ggml,
};

enum ExecutionTarget {
    CPU = 0,
    GPU,
    TPU,
    AUTO,
};

enum TensorType : uint32_t {
    F16 = 0,
    F32,
    F64,
    U8,
    I32,
    I64
};

typedef int32_t GraphHandle;
typedef int32_t CtxHandle;