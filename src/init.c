#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Visibility.h>

SEXP gltfheader_check(void);

static const R_CallMethodDef call_methods[] = {
    {"gltfheader_check", (DL_FUNC) &gltfheader_check, 0},
    {NULL, NULL, 0}
};

void attribute_visible R_init_gltfheader(DllInfo* dll) {
    R_registerRoutines(dll, NULL, call_methods, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
    R_forceSymbols(dll, TRUE);
}
