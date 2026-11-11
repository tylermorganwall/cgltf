#include <Rinternals.h>

#define CGLTF_IMPLEMENTATION
#include "../inst/include/cgltf.h"

SEXP cgltf_check(void) {
    const char json[] = "{\"asset\":{\"version\":\"2.0\"},"
        "\"nodes\":[{\"translation\":[1,2,3]}],"
        "\"scenes\":[{\"nodes\":[0]}],\"scene\":0}";
    cgltf_options options = {0};
    cgltf_data* data = NULL;
    if (cgltf_parse(&options, json, sizeof(json) - 1, &data) != cgltf_result_success) {
        return Rf_ScalarLogical(0);
    }
    if (cgltf_validate(data) != cgltf_result_success || data->nodes_count != 1) {
        cgltf_free(data);
        return Rf_ScalarLogical(0);
    }
    cgltf_float transform[16];
    cgltf_node_transform_world(&data->nodes[0], transform);
    int valid = data->scene == &data->scenes[0] &&
        cgltf_node_index(data, &data->nodes[0]) == 0 &&
        transform[0] == 1 && transform[5] == 1 &&
        transform[10] == 1 && transform[15] == 1 &&
        transform[12] == 1 && transform[13] == 2 && transform[14] == 3;
    cgltf_free(data);

    // A truncated document must return an error without terminating R.
    const char invalid_json[] = "{\"asset\":{\"version\":\"2.0\"}";
    data = NULL;
    cgltf_result result = cgltf_parse(
        &options, invalid_json, sizeof(invalid_json) - 1, &data);
    cgltf_free(data);
    return Rf_ScalarLogical(valid && result == cgltf_result_invalid_json);
}
