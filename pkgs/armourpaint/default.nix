{
  lib,
  stdenv,
  fetchFromGitHub,
  autoPatchelfHook,
  git,
  utillinux,
  glib,
  gnome2,
  harfbuzz,
  cairo,
  gdk-pixbuf,
  atk,
  pkg-config,
  nodejs,
  gnumake,
  clang,
  xorg,
  alsaLib,
  gtk3-x11,
  udev,
  makeDesktopItem,
  copyDesktopItems,
}:
stdenv.mkDerivation rec {
  pname = "armorpaint";
  version = "21.10";

  src = fetchFromGitHub {
    repo = "armorpaint";
    owner = "armory3d";
    rev = version;
    sha256 = "sha256-CcxU0qXDFxm4kjDXfZowlNH9DRH0HBnDpqNW9/WgGs4=";
    fetchSubmodules = true;
    deepClone = true;
  };

  desktopItems = [
    (makeDesktopItem {
      desktopName = "ArmorPaint";
      exec = "armorpaint";
      name = "ArmorPaint";
      icon = "armorpaint";
    })
  ];
  patchPhase = ''
    sed -i "s_exec('lscpu.*_'6'_" armorcore/Kinc/Tools/kincmake/node_modules/physical-cpu-count/index.js
    substituteInPlace armorcore/kincfile.js \
      --replace /usr/include/gtk-3.0 ${gtk3-x11.dev}/include/gtk-3.0 \
      --replace /usr/include/glib-2.0 '${glib.dev}/include/glib-2.0"); project.addIncludeDir("${glib.out}/lib/glib-2.0/include' \
      --replace /usr/include/pango-1.0 ${gnome2.pango.dev}/include/pango-1.0 \
      --replace /usr/include/harfbuzz ${harfbuzz.dev}/include/harfbuzz \
      --replace /usr/include/cairo ${cairo.dev}/include/cairo \
      --replace /usr/include/gdk-pixbuf-2.0 ${gdk-pixbuf.dev}/include/gdk-pixbuf-2.0 \
      --replace /usr/include/atk-1.0 ${atk.dev}/include/atk-1.0

    cat armorcore/kincfile.js
    copyDesktopItems
  '';

  buildInputs =
    [
      git
      utillinux.bin
      glib
      nodejs
      gnumake
      alsaLib
      gtk3-x11.dev
      udev.dev
    ]
    ++ (with xorg; [
      libXinerama
      xrandr
      libXi
      libXcursor
    ]);

  nativeBuildInputs = [
    autoPatchelfHook
    clang
    pkg-config
    copyDesktopItems
  ];

  installPhase = ''
    autoPatchelf .

    node armorcore/make -g opengl

    cd armorcore
    node Kinc/make -g opengl --compiler clang --compile

    cd Deployment
    strip ArmorPaint

    mkdir -p $out/bin
    cp -r ../../ $out

    cat <<-EOF > $out/bin/armorpaint
    #!/usr/bin/env bash
    $out/armorcore/Deployment/ArmorPaint $out/build/krom
    EOF

    chmod +x $out/bin/armorpaint
  '';

  meta = with lib; {
    description = "3D PBR Texture Painting Software";
    homepage = "https://github.com/armory3d/armorpaint";
    license = licenses.zlib;
    maintainers = with maintainers; [shou];
    platforms = platforms.unix;
  };
}
