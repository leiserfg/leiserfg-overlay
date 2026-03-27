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
  sha256 = "0jr0ljrd0v7zf3k50ypfj86xwcmbdwji27fxfkwdj5hrpq5agl5l";

  src = fetchurl {
    url = "https://github.com/Eden-CI/Nightly/releases/download/v1774464339.f0d77e86e3/Eden-Linux-f0d77e86e3-steamdeck-clang-pgo.AppImage";
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
