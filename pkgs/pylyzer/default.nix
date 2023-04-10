{
  lib,
  fetchFromGitHub,
  rustPlatform,
  libclang,
  stdenv
}: let
 ergup =  stdenv.mkDerivation rec {
   pname = "ergup";
   version = "0.0.1";

   src = fetchFromGitHub {
        owner = "mtshiba";
        repo = pname;
        rev = "6adbebb";
        sha256 = "sha256-+Nkw7JS3AIAOLFAFyww7gDKzLKYlqdxudb5fx1KH6RM=";
   };

   installPhase = ''
    mkdir -p $out/bin/
    cp $src/ergup.py $out/bin/
   '';
};
in

rustPlatform.buildRustPackage rec {
  pname = "pylyzer";
  version = "0.0.18";

  src = fetchFromGitHub {
    owner = "mtshiba";
    repo = pname;
    rev = "3b7cd75";
    sha256 = "sha256-o97murz+YFWGXE+ujdlyeKz6lpnVoHRWzpoTSp95csQ=";
  };
  buildInputs = [ergup];
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
