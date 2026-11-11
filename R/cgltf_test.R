#' Check the Bundled cgltf Library
#'
#' Verify that the bundled library can parse and validate a small glTF scene
#' and compute a node transformation.
#'
#' @return A logical scalar: \code{TRUE} if all checks pass, otherwise
#'   \code{FALSE}.
#' @export
#' @useDynLib cgltf, .registration = TRUE, .fixes = "C_"
#' @details
#' Calls a small C routine compiled against the bundled header when the package
#' is installed. The checks also verify that malformed JSON is rejected.
#' No compiler is needed to run this function in an installed package.
#' @examples
#' # Check parsing and transformations for a scene with a translated node.
#' stopifnot(cgltf_test())
cgltf_test <- function() {
  .Call(C_cgltf_check)
}
