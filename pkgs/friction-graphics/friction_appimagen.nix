{
  makeWrapper,
  fetchurl,
  lib,
  stdenv,
  autoPatchelfHook,
  vulkan-utility-libraries,
  wrapQtAppsHook,
  ffmpeg_4-full,
  fontconfig,
  freetype,
  glib,
  harfbuzzFull,
  icu,
  libGL,
  libGLU,
  libjpeg_turbo,
  libpng,
  qt5,
  libunwind,
  libwebp,

  libpulseaudio,
  alsa-lib,
}:

let
  pname = "friction";
  version = "1.0.0-rc2";
  sha256 = "sha256-QZXb++ylt39V0iLoAS2+Ab2lXuHA69jX4oHtacKg/DI=";

  src = fetchurl {
    # url = "https://github.com/eden-emulator/Releases/releases/download/v${version}/Eden-Linux-v${version}-steamdeck.AppImage";
    url = "https://github.com/friction2d/friction/releases/download/v1.0.0-rc.2/Friction-1.0.0-rc.2-x86_64.AppImage";
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
    libjpeg_turbo
    libpng
    libunwind
    libwebp
    ffmpeg_4-full
  ]
  ++ (with qt5; [

    qtbase
    qtmultimedia
    qtsvg
  ]);

  sourceRoot = ".";

  installPhase = ''
    runHook preInstall
    cp $src ./appimage
    chmod +x ./appimage
    ./appimage --appimage-extract
    install -d -D ./squashfs-root/usr/share $out/share
    install -D ./squashfs-root/usr/bin/friction $out/bin/friction

    wrapProgram "$out/bin/friction" \
       --suffix LD_LIBRARY_PATH : ${
         lib.makeLibraryPath [
           libpulseaudio
           alsa-lib
         ]
       };

    # for f in ./AppDir/shared/lib/libSPIRV*; do
    #      install -Dm755 "$f" "$out/lib/$(basename "$f")"
    # done

    runHook postInstall
  '';

  meta = with lib; {
    platforms = platforms.linux;
  };
}
