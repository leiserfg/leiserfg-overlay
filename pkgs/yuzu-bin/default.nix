{
  lib,
  stdenv,
  fetchurl,
  autoPatchelfHook,
  libdrm,
  wrapQtAppsHook,
  qtbase,
  openssl,
  glibc,
  libX11,
  libXext,
  libva
}:
stdenv.mkDerivation rec {
  pname = "yuzu-bin";
  version = "1105";
  hash = "20220723-eb14b2edf";
  src = fetchurl {
    url = "https://github.com/yuzu-emu/yuzu-mainline/releases/download/mainline-0-1105/yuzu-linux-20220723-eb14b2edf.tar.xz";
    # url = "https://github.com/yuzu-emu/yuzu-mainline/releases/download/meanline-0-${version}/yuzu-linux-${hash}.tar.xz";
    sha256 = "sha256-tBhRE8wDT3eygESB0aucGwB+ZuMoJOP755c+4adlvbo=";
  };
  nativeBuildInputs = [
    autoPatchelfHook
    wrapQtAppsHook
  ];
  # dontWrapQtApps=true;
  buildInputs = [
      libdrm
      openssl
      glibc
      libX11
      libXext
      qtbase
      libva
  ];

  installPhase = ''
    ls -al .
    install -m755 -D yuzu $out/bin/yuzu
    install -m755 -D yuzu-cmd $out/bin/yuzu-cmd
  '';

  meta = with lib; {
    description = "Translate wasm to lua";
    homepage = "https://github.com/Rerumu/Wasynth";
    license = licenses.gpl3;
    platforms = platforms.unix;
  };
}
