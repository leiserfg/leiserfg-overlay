{
  lib,
  fetchFromGitHub,
  rustPlatform,
  libclang,
  stdenv
}:
rustPlatform.buildRustPackage rec {
  pname = "pylyzer";
  version = "0.0.18";

  src = fetchFromGitHub {
    owner = "mtshiba";
    repo = pname;
    rev = "3b7cd75";
    sha256 = "sha256-o97murz+YFWGXE+ujdlyeKz6lpnVoHRWzpoTSp95csQ=";
  };
  #  LIBCLANG_PATH = "${libclang.lib}/lib";
  #  BINDGEN_EXTRA_CLANG_ARGS = "-isystem ${libclang.lib}/lib/clang/${lib.getVersion clang}/include";
  cargoSha256 = "sha256-kZLlF6C3fG04o7isJBlLJohdgSlDWLtN1rHMO7amKcg=";

  doCheck = false; # Don't run the tests
  meta = with lib; {
    description = "Do the LLaMA thing, but now in Rust pylyzer is a static code analyzer / language server for Python, written in Rust.";
    homepage = "https://github.com/mtshiba/pylyzer";
    license = licenses.mit;
    maintainers = ["leiserfg"];
  };
}
