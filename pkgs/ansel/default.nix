{
  lib,
  stdenv,
  fetchFromGitHub,
  fetchurl,
  libsoup,
  graphicsmagick,
  json-glib,
  wrapGAppsHook,
  cairo,
  cmake,
  ninja,
  curl,
  perl,
  llvm_13,
  desktop-file-utils,
  exiv2,
  glib,
  glib-networking,
  ilmbase,
  gtk3,
  intltool,
  lcms2,
  lensfun,
  libX11,
  libexif,
  libgphoto2,
  libjpeg,
  libpng,
  librsvg,
  libtiff,
  openexr_3,
  osm-gps-map,
  pkg-config,
  sqlite,
  libxslt,
  openjpeg,
  pugixml,
  colord,
  colord-gtk,
  libwebp,
  libsecret,
  gnome,
  SDL2,
  ocl-icd,
  pcre,
  gtk-mac-integration,
  isocodes,
  llvmPackages,
  gmic,
  libavif,
  icu,
  jasper,
  libheif,
  libaom,
  portmidi,
  fetchpatch,
  lua,
}:
stdenv.mkDerivation rec {
  version = "4.0.0";
  pname = "ansel";

  src = fetchFromGitHub {
    owner = "aurelienpierreeng";
    repo = "ansel";
    rev = "f6f9100";
    sha256 = "sha256-iFl+a0esZChErLdoK2+jSMi8/ArmqYFmNQukmBp4myg=";
    fetchSubmodules = true;
  };

  nativeBuildInputs = [cmake ninja llvm_13 pkg-config intltool perl desktop-file-utils wrapGAppsHook];

  buildInputs =
    [
      cairo
      curl
      exiv2
      glib
      glib-networking
      gtk3
      ilmbase
      lcms2
      lensfun
      libexif
      libgphoto2
      libjpeg
      libpng
      librsvg
      libtiff
      openexr_3
      sqlite
      libxslt
      libsoup
      graphicsmagick
      json-glib
      openjpeg
      pugixml
      libwebp
      libsecret
      SDL2
      gnome.adwaita-icon-theme
      osm-gps-map
      pcre
      isocodes
      gmic
      libavif
      icu
      jasper
      libheif
      libaom
      portmidi
      lua
    ]
    ++ lib.optionals stdenv.isLinux [
      colord
      colord-gtk
      libX11
      ocl-icd
    ]
    ++ lib.optional stdenv.isDarwin gtk-mac-integration
    ++ lib.optional stdenv.cc.isClang llvmPackages.openmp;

  cmakeFlags =
    [
      "-DBUILD_USERMANUAL=False"
    ]
    ++ lib.optionals stdenv.isDarwin [
      "-DUSE_COLORD=OFF"
      "-DUSE_KWALLET=OFF"
    ];

  # ansel changed its rpath handling in commit
  # 83c70b876af6484506901e6b381304ae0d073d3c and as a result the
  # binaries can't find libansel.so, so change LD_LIBRARY_PATH in
  # the wrappers:
  preFixup = let
    libPathEnvVar =
      if stdenv.isDarwin
      then "DYLD_LIBRARY_PATH"
      else "LD_LIBRARY_PATH";
    libPathPrefix = "$out/lib/ansel" + lib.optionalString stdenv.isLinux ":${ocl-icd}/lib";
  in ''
    for f in $out/share/ansel/kernels/*.cl; do
      sed -r "s|#include \"(.*)\"|#include \"$out/share/ansel/kernels/\1\"|g" -i "$f"
    done

    gappsWrapperArgs+=(
      --prefix ${libPathEnvVar} ":" "${libPathPrefix}"
    )
  '';

  meta = with lib; {
    description = "Virtual lighttable and darkroom for photographers";
    homepage = "ansel.photos";
    license = licenses.gpl3Plus;
    platforms = platforms.linux ++ platforms.darwin;
    maintainers = with maintainers; [goibhniu flosse mrVanDalo paperdigits];
  };
}
