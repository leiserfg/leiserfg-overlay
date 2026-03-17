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
  sha256 = "07924jw727adyf5sqid77cd7bkvzv6yw2kkbchw2d0n88bwy3j69";

  src = fetchurl {
    url = "https://github.com/Eden-CI/Nightly/releases/download/v1773776627.af554c0baa/Eden-Linux-af554c0baa-steamdeck-clang-pgo.AppImage";
    inherit sha256;
  };

in
stdenv.mkDerivation rec {
  inherit src version pname;

  dontUnpack = true;
  dontStrip = true;
  sourceRoot = ".";

  installPhase = ''
    runHook preInstall
    install -D $src $out/bin/eden
    chmod +x $out/bin/eden
    $out/bin/eden --appimage-extract

    install -D ./AppDir/dev.eden_emu.eden.desktop $out/share/applications/dev.eden_emu.eden.desktop
    install -D ./AppDir/dev.eden_emu.eden.svg $out/share/icons/hicolor/scalable/apps/dev.eden_emu.eden.svg

    runHook postInstall
  '';

  meta = with lib; {
    platforms = platforms.linux;
  };
}
