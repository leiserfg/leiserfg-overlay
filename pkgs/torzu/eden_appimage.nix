{
  makeWrapper,
  fetchurl,
  lib,
  stdenv,
  autoPatchelfHook,
  vulkan-utility-libraries,
  wrapQtAppsHook,
  qtbase,
  qtmultimedia,
  qtwayland,
  qtwebengine,
  libopus,
  libusb1,
  fmt_12,
  vulkan-headers,
  glslang,
  spirv-tools,
  alsa-plugins,
  alsa-lib,
  libpulseaudio,
  enet,
  boost189,
}:

let
  pname = "eden-emulator";
  version = "0.1.1";
  sha256 = "sha256-29OWAyJZdKGFT59dN8QuCKMOMvRFCErQH4I5GEbT2Ak==";

  src = fetchurl {
    # url = "https://github.com/eden-emulator/Releases/releases/download/v${version}/Eden-Linux-v${version}-steamdeck.AppImage";
    url = "https://github.com/Eden-CI/Nightly/releases/download/v1770316725.5acddfde16/Eden-Linux-5acddfde16-steamdeck-clang-pgo.AppImage";
    inherit sha256;
  };

in
stdenv.mkDerivation rec {
  inherit src version pname;

  dontUnpack = true;
  nativeBuildInputs = [
    autoPatchelfHook
    wrapQtAppsHook
    makeWrapper
  ];
  # autoPatchelfIgnoreMissingDeps = true;
  buildInputs = [
    enet
    fmt_12
    vulkan-utility-libraries
    glslang
    libopus
    libusb1
    spirv-tools
    vulkan-headers
    qtbase
    qtmultimedia
    qtwayland
    qtwebengine
    boost189
  ];

  sourceRoot = ".";

  installPhase = ''
    runHook preInstall
    cp $src ./appimage
    chmod +x ./appimage
    ./appimage --appimage-extract
    rm ./appimage
    ls ./AppDir/
    install -D ./AppDir/shared/bin/eden $out/bin/eden
    install -D ./AppDir/dev.eden_emu.eden.desktop $out/share/applications/dev.eden_emu.eden.desktop
    install -D ./AppDir/dev.eden_emu.eden.svg $out/share/icons/hicolor/scalable/apps/dev.eden_emu.eden.svg

    wrapProgram "$out/bin/eden" \
        --set ALSA_PLUGIN_DIR ${alsa-plugins}/lib/alsa-lib \
       --suffix LD_LIBRARY_PATH : ${
         lib.makeLibraryPath [
           libpulseaudio
           alsa-lib
         ]
       };

    for f in ./AppDir/shared/lib/libSPIRV*; do
         install -Dm755 "$f" "$out/lib/$(basename "$f")"
    done
    runHook postInstall
  '';

  meta = with lib; {
    platforms = platforms.linux;
  };
}
