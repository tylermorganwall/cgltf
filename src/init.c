#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Visibility.h>

SEXP cgltf_check(void);

static const R_CallMethodDef call_methods[] = {
    {"cgltf_check", (DL_FUNC) &cgltf_check, 0},
    {NULL, NULL, 0}
};

void attribute_visible R_init_cgltf(DllInfo* dll) {
    R_registerRoutines(dll, NULL, call_methods, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
    R_forceSymbols(dll, TRUE);
}
