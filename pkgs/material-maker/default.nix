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
  libXrender
}:
let 
    _tr = text : (builtins.replaceStrings ["." "-"] ["_" "_"] text);
in
stdenv.mkDerivation rec {
  pname = "material-maker";
  version = "0.99";

  src = fetchurl {
    url="https://github.com/RodZill4/${pname}/releases/download/${version}/${_tr pname}_${_tr version}_linux.tar.gz";
    sha256 = "1gqb095dn6agqafnr53lya91jh20xlgdfp5cg5l72a6rps1i8j47";
  };
  desktopItems = [
    (makeDesktopItem {
      desktopName = "MaterialMaker";
      exec = "material-maker";
      name = "MaterialMaker";
      icon = "material-maker";
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
  ];

  nativeBuildInputs = [
    autoPatchelfHook
    copyDesktopItems
  ];

  installPhase = ''
    mkdir -p $out/bin/ $out/share/pixmaps/
    # cp material_maker.x86_64  $out/bin/material_maker
    cp -r . $out/material_maker/

    cat <<-EOF > $out/bin/material_maker
    #!/usr/bin/env bash
    $out/material_maker/material_maker.x86_64
    EOF

    chmod +x $out/bin/material_maker
    cp $out/material_maker/examples/mm_icon.png   $out/share/pixmaps/material_maker.png
    copyDesktopItems
  '';

  meta = with lib; {
    description = "This is a tool based on Godot Engine that can be used to create textures procedurally and paint 3D models.";
    homepage = "https://www.materialmaker.org/";
    license = licenses.mit;
    platforms = platforms.unix;
  };
}
