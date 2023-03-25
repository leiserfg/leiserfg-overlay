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
    rev = "91afe67";
    sha256 = "sha256-E2BHSdehY/R1S0IiobOcz1QRs77fDWgD1aRgd0RsEFE=";
  };
  LIBCLANG_PATH = "${libclang.lib}/lib";
  BINDGEN_EXTRA_CLANG_ARGS = "-isystem ${libclang.lib}/lib/clang/${lib.getVersion clang}/include";
  cargoSha256 = "sha256-lKRduO+MFmW1axqF/3U30R0KThVEX/stoItugKOO/XU=";

  meta = with lib; {
    description = "Do the LLaMA thing, but now in Rust crabrocketllama";
    homepage = "https://github.com/setzer22/llama-rs/";
    license = licenses.unlicense;
    maintainers = [maintainers.tailhook];
  };
}
