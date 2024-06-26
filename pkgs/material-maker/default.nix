{
  lib,
  stdenv,
  fetchurl,
  autoPatchelfHook,
  makeDesktopItem,
  copyDesktopItems,
  libX11,
  libXrandr,
  libXinerama,
  libXcursor,
  libXi,
  libXext,
  libGLU,
  libXrender,
  libva,
  openssl,
}: let
  _tr = text: (builtins.replaceStrings ["." "-"] ["_" "_"] text);
in
  stdenv.mkDerivation rec {
    pname = "material-maker";
    version = "1.3";

    src = fetchurl {
      url = "https://github.com/RodZill4/${pname}/releases/download/${version}/${_tr pname}_${_tr version}_linux.tar.gz";
      sha256 = "sha256-Y8+ZwXy3zqnsxqqaZeVgFSxLzmUkq+rBzbq8tEDc8/g=";
    };
    desktopItems = [
      (makeDesktopItem {
        desktopName = "MaterialMaker";
        exec = "material_maker";
        name = "MaterialMaker";
        icon = "material_maker";
      })
    ];

    buildInputs = [
      libX11
      libXrandr
      libXinerama
      libXcursor
      libXi
      libXext
      libGLU
      libXrender
      libva
      openssl
    ];

    nativeBuildInputs = [
      autoPatchelfHook
      copyDesktopItems
    ];

    installPhase = ''
      mkdir -p $out/bin/ $out/share/icons/hicolor/256x256/apps/
      cp -r . $out/material_maker/

      cat <<-EOF > $out/bin/material_maker
      #!/usr/bin/env bash
      $out/material_maker/material_maker.x86_64
      EOF

      chmod +x $out/bin/material_maker
      cp $out/material_maker/examples/mm_icon.png   $out/share/icons/hicolor/256x256/apps/material_maker.png
      copyDesktopItems
    '';

    meta = with lib; {
      description = "This is a tool based on Godot Engine that can be used to create textures procedurally and paint 3D models.";
      homepage = "https://www.materialmaker.org/";
      license = licenses.mit;
      platforms = platforms.unix;
    };
  }
