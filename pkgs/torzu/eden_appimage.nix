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
  version = "0.2.0";
  sha256 = "sha256-0DEcK9tbKgyEjw40l3SlIetPqMUCdSNhnqO8nfkJufk=";

  src = fetchurl {

    # url = "https://stable.eden-emu.dev/v0.2.0/Eden-Linux-v0.2.0-rog-ally-clang-pgo.AppImage";
    url = "https://nightly.eden-emu.dev/v1781122546.5219b9f3d2/Eden-Linux-5219b9f3d2-steamdeck-clang-pgo.AppImage";
    inherit sha256;
  };

in
stdenv.mkDerivation rec {
  inherit src version pname;

  dontUnpack = true;
  dontStrip = true;
  sourceRoot = ".";
  nativeBuildInputs = [ makeWrapper ];
  installPhase = ''
    runHook preInstall
    install -D $src $out/bin/eden-unwrapped
    chmod +x $out/bin/eden-unwrapped
    $out/bin/eden-unwrapped --appimage-extract

    install -D ./AppDir/dev.eden_emu.eden.desktop $out/share/applications/dev.eden_emu.eden.desktop
    install -D ./AppDir/dev.eden_emu.eden.svg $out/share/icons/hicolor/scalable/apps/dev.eden_emu.eden.svg

    makeWrapper  $out/bin/eden-unwrapped  $out/bin/eden --set ALSA_PLUGIN_DIR ${alsa-plugins}/lib/alsa-lib/ 

    runHook postInstall
  '';

  meta = with lib; {
    platforms = platforms.linux;
  };
}
