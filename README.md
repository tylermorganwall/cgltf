# cgltf

An R package containing the unmodified, header-only cgltf v1.15 loader for loading glTF and GLB files. The package supplies headers for downstream R packages and includes a small compiled C check accessible from R.

Package versions use `major.minor.patch-revision`: `1.15.0` corresponds to
upstream cgltf 1.15, and `-1` identifies the first vendored revision. The suffix
tracks package-specific changes, including adaptations for CRAN.

Install locally with `R CMD INSTALL /path/to/cgltf`.
Consumer R packages add `cgltf (>= 1.15.0-1)` to `LinkingTo` in DESCRIPTION
and include `<cgltf.h>`. Define `CGLTF_IMPLEMENTATION` before the include in
exactly one C or C++ translation unit per downstream package:

```c
#define CGLTF_IMPLEMENTATION
#include <cgltf.h>
```

Keep R's standard `-DNDEBUG` compilation flag when compiling the implementation.
It disables upstream assertions that could otherwise terminate the R process.
Custom build systems must also define `NDEBUG`.

The exported `cgltf_test()` function calls a registered C routine that
checks scene parsing, validation, node transformations, and rejection of
malformed JSON. The routine is compiled when installing from source; running
the function requires no compiler or additional R packages:

```r
stopifnot(cgltf::cgltf_test())
```

The package is fully developed for its intended role as a header provider.
The R function verifies the installation; a general R interface to cgltf is
outside the scope of this submission.
