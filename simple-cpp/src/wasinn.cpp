#include <iostream>
#include <string>
#include "graph.h"

using namespace std;

int main(int argc, const char **argv) {
    const string Data = "{ \
        \"enable-log\" : true, \
        \"enable-debug-log\" : false, \
        \"stream-stdout\": true \
    }";

    auto *Graph = GraphBuilder()
                        .config(Data)
                        .buildFromCache("default");

    auto *Ctx = Graph->initExecutionContext();
    const string Prompt = "You are a user-assistant and need to answer the question asked as accurately as you can in english. Answer in this form: \
    Question: {Q} \
    Answer: {A} \
    where {Q} is the question asked and {A} is the answer. Ensure to follow the the given format to word. \
    Q. Who was Robert OppenHeimer in 2-3 lines?";

    Ctx->setInput<uint8_t>(0, U8, {{ 1 }}, {(uint8_t*)Prompt.c_str(), Prompt.size()});
    Ctx->compute();

    uint8_t *Buf = new uint8_t[4096 * 6];

    size_t BufferSize = 0;
    Ctx->getOutput(0, Buf, 4096 * 6, BufferSize);
    
    const string Out((char*)Buf, min<size_t>(BufferSize, 4096 * 6));
    cout << "Out buffer: " << Out << "\n";
    
    return 0;
}
