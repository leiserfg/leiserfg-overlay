{
  clangStdenv,
  cmake,
  ninja,
  lib,
  fetchFromGitHub,
  pkg-config,
  libpng,
  giflib,
  lcms2,
  brotli,
  libhwy,
}:
clangStdenv.mkDerivation rec {
  pname = "jpegli";
  version = "0.1.0-bc19ca2";
  src = fetchFromGitHub {
    owner = "google";
    repo = pname;
    rev = "bc19ca2";
    sha256 = "sha256-8th+QHLOoAIbSJwFyaBxUXoCXwj7K7rgg/cCK7LgOb0=";
  };
    patches = [./lib_path.patch];

  nativeBuildInputs = [
    cmake
    ninja
    pkg-config
  ];
  buildInputs = [
    libhwy
    libpng
    giflib
    lcms2
    brotli
  ];
  meta = with lib; {
    description = "Live GLSL coding renderer";
    homepage = "https://github.com/google/jpegli";
    license = "JPEG XL Project Authors.";
    platforms = platforms.unix;
  };
}
