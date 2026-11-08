#define CGLTF_IMPLEMENTATION
#include <cgltf.h>
#include <string.h>

int main(void) {
    const char json[] = "{\"asset\":{\"version\":\"2.0\"},"
        "\"nodes\":[{\"translation\":[1,2,3]}],"
        "\"scenes\":[{\"nodes\":[0]}],\"scene\":0}";
    cgltf_options options = {0};
    cgltf_data *data = NULL;
    cgltf_float transform[16];
    if (cgltf_parse(&options, json, strlen(json), &data) != cgltf_result_success) {
        return 1;
    }
    if (cgltf_validate(data) != cgltf_result_success || data->nodes_count != 1) {
        cgltf_free(data);
        return 2;
    }
    cgltf_node_transform_world(&data->nodes[0], transform);
    if (transform[12] != 1 || transform[13] != 2 || transform[14] != 3) {
        cgltf_free(data);
        return 3;
    }
    cgltf_free(data);
    return 0;
}
