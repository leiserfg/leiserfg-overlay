{
  stdenv,
  lib,
  src,
}:

stdenv.mkDerivation {
  pname = "sokol-shdc";
  version = "0-unstable-2024-08-09";

  inherit src;

  dontConfigure = true;
  dontBuild = true;

  installPhase = ''
    mkdir -p $out/bin
    cp sokol-shdc $out/bin/sokol-shdc
    chmod +x $out/bin/sokol-shdc
  '';

  meta = with lib; {
    description = "Shader cross-compiler and code-generator for sokol_gfx.h";
    homepage = "https://github.com/floooh/sokol-tools-bin";
    license = licenses.zlib;
    platforms = [ "x86_64-linux" ];
    mainProgram = "sokol-shdc";
  };
}
