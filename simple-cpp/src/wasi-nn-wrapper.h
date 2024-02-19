namespace wasi_ephemeral_nn {

extern "C" {
__attribute__((import_module("wasi_ephemeral_nn"))) extern int load(int arg0, int arg1, int arg2, int arg3, int arg4);
__attribute__((import_module("wasi_ephemeral_nn"))) extern int load_by_name(int arg0, int arg1, int arg2);
__attribute__((import_module("wasi_ephemeral_nn"))) extern int init_execution_context(int arg0, int arg1);
__attribute__((import_module("wasi_ephemeral_nn"))) extern int set_input(int arg0, int arg1, int arg2);
__attribute__((import_module("wasi_ephemeral_nn"))) extern int get_output(int arg0, int arg1, int arg2, int arg3, int arg4);
__attribute__((import_module("wasi_ephemeral_nn"))) extern int get_output_single(int arg0, int arg1, int arg2, int arg3, int arg4);
__attribute__((import_module("wasi_ephemeral_nn"))) extern int compute(int arg0);
__attribute__((import_module("wasi_ephemeral_nn"))) extern int compute_single(int arg0);
__attribute__((import_module("wasi_ephemeral_nn"))) extern int fini_single(int arg0);
__attribute__((import_module("wasi_ephemeral_nn"))) extern int load_by_name_with_config(int arg0, int arg1, int arg2, int arg3, int arg4);
}

}
