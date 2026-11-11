# Pre-submission native-code review

Reviewed on 2026-11-07: all C/C++ sources and headers in this package, including
`inst/include/cgltf.h`, `src/gltfheader-test.c`, `src/init.c`, and
`tools/smoke-test.c`.

- No direct `exit`, `_Exit`, `quick_exit`, `abort`, native `stop`, `printf`,
  `fprintf`, `puts`, related console-output calls, `stderr`/`stdout`, or C++
  `cerr`/`cout`/`clog` uses remain.
- No pragmas, `#warning`, `#error`, system RNG calls, `system`/`popen`, or
  `sprintf`/`vsprintf` calls were found.
- The upstream header contains 17 `assert()` uses: 16 index-helper assertions
  and one validation macro controlled by `CGLTF_VALIDATE_ENABLE_ASSERTS`.
  Assertions are disabled by `NDEBUG`, which R supplies when compiling native
  code. Nothing in the bundled header undefines it. Custom downstream build
  systems must retain or supply `-DNDEBUG`; compiling without it can enable
  process-terminating assertions. This requirement is documented in README.md.
- The standalone C test's `puts()` call was removed. Its `main()` return codes
  report test results; they are not calls that terminate an R process.
- Standard file input (`fopen`, `fread`, etc.), allocation, and string operations
  remain in the loader. These are not console-output calls.
- The C check uses R's native `.Call()` interface with explicit routine
  registration and forced symbol lookup. Its implementation symbols are hidden
  from other shared libraries on platforms supporting `C_VISIBILITY`.

The C smoke test builds and runs with:

```sh
clang -std=c99 -DNDEBUG -Wall -Wextra -Iinst/include tools/smoke-test.c -o /tmp/gltfheader-smoke
/tmp/gltfheader-smoke
clang -std=c99 -DNDEBUG -Iinst/include -c tools/smoke-test.c -o /tmp/gltfheader-smoke.o
nm -u /tmp/gltfheader-smoke.o
```

The compiled object has no unresolved assertion, process-exit, or
console-output symbols. This check examines the complete header implementation,
including functions not called by the smoke test. It is a focused source and
symbol review, not an exhaustive memory-safety or portability audit.

The installed header remains byte-for-byte unchanged, with SHA256 matching
`inst/UPSTREAM`:

```text
e378a21c084bf1f288bb799de827bb26906efb024255f1ecf1705ea13f11c6ec
```

Reference: [Writing R Extensions, portable native code](https://cran.r-project.org/doc/manuals/r-release/R-exts.html#Writing-portable-packages).

## Package validation

`R CMD check --as-cran --no-manual` completed on 2026-11-07 using R 4.6.0 on
macOS Sequoia 15.7.3 (arm64): 0 errors, 0 warnings, 1 NOTE ("New submission").
The unconditional example and tests both pass, as do native registration and
compiled-code checks. DESCRIPTION passes `read.dcf()` and R's strict
package-description validation. R CMD build correctly derives
`NeedsCompilation: yes` for the small native check. No additional R package
dependencies are required.

The check used a temporary copy of the local user Makevars with only `CCACHE`
cleared to bypass the unavailable compiler-cache service. No user configuration
was changed. The final check ran with network access for incoming/URL checks.

Check log: `/tmp/gltfheader-native-u5K3sC/gltfheader.Rcheck/00check.log`.
Checked archive: `/tmp/gltfheader-native-u5K3sC/gltfheader_1.15.0.tar.gz`.

After this full check, quotes around 'glTF' and 'GLB' were restored in
DESCRIPTION, following the accepted rgl2gltf metadata supplied by the maintainer.
The revised DESCRIPTION passes strict metadata validation; the archive above
predates this formatting-only change and the accompanying submission-note edits.
The package version was subsequently set to 1.15.0-1, with matching release
documentation. This uses upstream version 1.15.0 and vendored revision 1; the
upstream provenance and header are unchanged. Strict metadata validation passes
for the updated version. The full-check archive above remains version 1.15.0.
