{
  lib,
  fetchFromGitHub,
  rustPlatform,
  libclang,
  clang,
}:
rustPlatform.buildRustPackage rec {
  pname = "llama-rs";
  version = "0.0.1";
  /*
  nativeBuildInputs = [libclang];
  */
  src = fetchFromGitHub {
    owner = "setzer22";
    repo = pname;
    rev = "4a207f0";
    sha256 = "sha256-Qhs6Ap2A53wPJLvGaEfZWIdHiqdDQRokC8k/iFD5C0k=";
  };
  LIBCLANG_PATH = "${libclang.lib}/lib";
  BINDGEN_EXTRA_CLANG_ARGS = "-isystem ${libclang.lib}/lib/clang/${lib.getVersion clang}/include";
  cargoSha256 = "sha256-fTdcy2icxe9RmXFNBpSGhM2AwnLklZ4v/wdabEIMNtk=";

  meta = with lib; {
    description = "Do the LLaMA thing, but now in Rust crabrocketllama";
    homepage = "https://github.com/setzer22/llama-rs/";
    license = licenses.unlicense;
    maintainers = [maintainers.tailhook];
  };
}
