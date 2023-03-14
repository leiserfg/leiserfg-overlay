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
    rev = "e4986a1";
    sha256 = "sha256-qJQLSNsnAxRRFXtW5FMJvBZ3gtGe1nhaRuHeULc9Nf0=";
  };
  LIBCLANG_PATH = "${libclang.lib}/lib";
  BINDGEN_EXTRA_CLANG_ARGS = "-isystem ${libclang.lib}/lib/clang/${lib.getVersion clang}/include";
  cargoSha256 = "sha256-aSQn49uicTta4zN3oNJRQrurbhGk4xafI9Phlkea6VA=";

  meta = with lib; {
    description = "Do the LLaMA thing, but now in Rust crabrocketllama";
    homepage = "https://github.com/setzer22/llama-rs/";
    license = licenses.unlicense;
    maintainers = [maintainers.tailhook];
  };
}
