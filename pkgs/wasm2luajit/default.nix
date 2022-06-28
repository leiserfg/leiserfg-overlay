{
  lib,
  stdenv,
  fetchurl,
  autoPatchelfHook,
}: stdenv.mkDerivation rec {
    pname = "wasm2luajit";
    version = "0.10.0";
    src = fetchurl {
      url = "https://github.com/Rerumu/Wasynth/releases/download/v${version}/wasm2luajit";
      sha256 = "sha256-9Cj8SnVwfbMxKI3O+4wZytsJGL3V1xhQ0bay9zGOpRs=";
    };
    nativeBuildInputs = [
      autoPatchelfHook
    ];
    # unpackCmd = "cp";
    sourceRoot = ".";
    dontUnpack = true;

    installPhase = ''
        install -m755 -D ${src} $out/bin/wasm2luajit
    '';

    meta = with lib; {
      description = "Translate wasm to lua";
      homepage = "https://github.com/Rerumu/Wasynth";
      license = licenses.gpl3;
      platforms = platforms.unix;
    };
  }
