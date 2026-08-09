{
  stdenv,
  lib,
  zig,
  src,
}:

stdenv.mkDerivation {
  pname = "sokol-shdc";
  version = "0-unstable-2024-08-09";

  inherit src;

  nativeBuildInputs = [ zig ];

  dontUseZigCheck = true;

  meta = with lib; {
    description = "Shader cross-compiler and code-generator for sokol_gfx.h";
    homepage = "https://github.com/floooh/sokol-tools";
    license = licenses.zlib;
    platforms = platforms.unix;
  };
}
