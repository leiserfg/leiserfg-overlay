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
  libpulseaudio
}:

let
  pname = "eden-emulator";
  version = "0.0.4-rc3";
  sha256 = "sha256-Y0sHMxcxOj1FdTUFxXX8skXHJg2btwLJhuCD0Z2Trc8=";

  src = fetchurl {
    # url = "https://github.com/eden-emulator/Releases/releases/download/v${version}/Eden-Linux-v${version}-steamdeck.AppImage";
    url = "https://github.com/pflyly/eden-nightly/releases/download/2025-10-26-27884/Eden-27884-Steamdeck-PGO-x86_64.AppImage";
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
    install -D ./AppDir/dev.eden_emu.eden.desktop $out/share/applications/org.eden_emu.eden.desktop
    install -D ./AppDir/dev.eden_emu.eden.svg $out/share/icons/hicolor/scalable/apps/org.eden_emu.eden.svg

    wrapProgram "$out/bin/eden" \
        --set ALSA_PLUGIN_DIR ${alsa-plugins}/lib/alsa-lib \
       --suffix LD_LIBRARY_PATH : ${
            lib.makeLibraryPath [
              libpulseaudio
              alsa-lib]};

    for f in ./AppDir/shared/lib/libSPIRV*; do
         install -Dm755 "$f" "$out/lib/$(basename "$f")"
    done
    runHook postInstall
  '';

  meta = with lib; {
    platforms = platforms.linux;
  };
}
