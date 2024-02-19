#pragma once
#include <optional>
#include <string>
#include <iostream>
#include <span>
#include "types.h"
#include "tensor.h"
#include "wasi-nn-wrapper.h"

using namespace std;

class GraphExecutionContext {
    class Graph* Graph;
    CtxHandle Handle;

    public:
    GraphExecutionContext(class Graph *graph, ::CtxHandle handle): Graph(graph), Handle(handle) {

    }

    int compute() {
        return wasi_ephemeral_nn::compute(Handle);
    }

    template<typename T> int setInput(int Idx, TensorType Type, const span<const uint32_t> &Dimensions, const span<const T> &Data) {
        Tensor<T> *Ten = new Tensor<T>(Dimensions, Type, Data);
        int Res = wasi_ephemeral_nn::set_input(Handle, Idx, (int)Ten);
        delete Ten;
        return Res;
    }

    int getOutput(int Idx, uint8_t *OutBuffer, size_t BufferMaxSize, size_t& BufferSize) {
        size_t *Buffersize = new size_t;
        int Res = wasi_ephemeral_nn::get_output(Handle, Idx, (int)OutBuffer, BufferMaxSize, (int)BufferSize);
        BufferSize = *Buffersize;
        delete Buffersize;
        return Res;
    }
};

class Graph {
    public:
    class GraphBuilder *BuildInfo;
    GraphHandle Handle;

    public:
        Graph(class GraphBuilder *builder, GraphHandle handle) : BuildInfo(builder), Handle(handle) {

        }

        GraphExecutionContext* initExecutionContext() {
            int32_t *CtxH = new int32_t;
            int Res = wasi_ephemeral_nn::init_execution_context((int)Handle, (int)CtxH);
            return new GraphExecutionContext(this, *CtxH);
        }
};


class GraphBuilder {
    GraphEncoding Encoding;
    ExecutionTarget Target;
    optional<string> Options;

    public:

        GraphBuilder() {
            Encoding = GraphEncoding::Openvino;
            Target = ExecutionTarget::CPU;
            Options = nullopt;
        }

        GraphBuilder(GraphEncoding e, ExecutionTarget t) : Encoding(e), Target(t), Options(nullopt) {

        }

        GraphBuilder& config(string Config) {
            Options = { Config };
            return *this;
        }

        Graph* buildFromCache(const string &Name) {
            int32_t *GraphH = new int32_t;
            auto Config = *Options;
            int Res = -1;
            if (Options == nullopt) {
                Res = wasi_ephemeral_nn::load_by_name((int)Name.c_str(), Name.size(), (int)GraphH);
            } else {
                Res = wasi_ephemeral_nn::load_by_name_with_config((int)Name.c_str(), 
                            Name.size(), (int)Config.c_str(), Config.size(), (int)GraphH);
            }
            return new Graph(new GraphBuilder(*this), (GraphHandle)*GraphH);
        }
};