{
  appimageTools,
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
  fmt_11,
  vulkan-headers,
  glslang,
  spirv-tools,
}:

let
  pname = "eden-emulator";
  version = "0.0.3-rc3";
  sha256 = "sha256-JUTcwjqswdAibxw2UWU/zucCMnSAqtybMfhjOaxfnxc=";

  src = fetchurl {
    # url = "https://github.com/eden-emulator/Releases/releases/download/v${version}/Eden-Linux-v${version}-steamdeck.AppImage";
    url = "https://github.com/pflyly/eden-nightly/releases/download/2025-08-25-27626/Eden-27626-Steamdeck-light-x86_64.AppImage";
    inherit sha256;
  };

in
stdenv.mkDerivation rec {
  inherit src version pname;

  dontUnpack = true;
  nativeBuildInputs = [
    autoPatchelfHook
    wrapQtAppsHook
  ];
  # autoPatchelfIgnoreMissingDeps = true;
  buildInputs = [
    fmt_11
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

    install -D ./AppDir/usr/bin/eden $out/bin/eden
    install -D ./AppDir/org.eden_emu.eden.desktop $out/share/applications/org.eden_emu.eden.desktop
    install -D ./AppDir/org.eden_emu.eden.svg $out/share/icons/hicolor/scalable/apps/org.eden_emu.eden.svg

    for f in ./AppDir/usr/lib/libSPIRV*; do
         install -Dm755 "$f" "$out/lib/$(basename "$f")"
    done
    runHook postInstall
  '';

  meta = with lib; {
    # homepage = "https://studio-link.com";
    # description = "Voip transfer";
    platforms = platforms.linux;
  };
}
