{
  lib,
  stdenv,
  fetchFromGitHub,
  godot,
  godotPackages,
  # godot4-export-templates,
  libglvnd,
  libX11,
  libXcursor,
  libXext,
  libXfixes,
  libXi,
  libXinerama,
  libXrandr,
  libXrender,
  nix-update-script,
}:

stdenv.mkDerivation (finalAttrs: {
  pname = "material-maker";
  version = "1.4";

  src = fetchFromGitHub {
    owner = "RodZill4";
    repo = "material-maker";
    rev = finalAttrs.version;
    hash = "sha256-33MR57etKX7Hv3lwYVZ8Pwj5Krs7uhP7UY5vTbAMcSI=";
  };

  nativeBuildInputs = [ godot ];

  buildInputs = [
    libglvnd

    libXinerama
    libXcursor
    libXext
    libXrandr
    libXrender
    libX11
    libXi
    libXfixes
  ];

  buildPhase = ''
    runHook preBuild

    export HOME=$TMPDIR

    # Link the export-templates to the expected location. The --export-* commands
    # expects the template-file at .../templates/{godot-version}.stable/
    mkdir -p $HOME/.local/share/godot
    ln -s ${godotPackages.export-template}/share/godot/templates $HOME/.local/share/godot

    mkdir -vp build
    godot --headless -v --export-release 'Linux/X11' build/material-maker
    runHook postBuild
  '';

  installPhase = ''
    runHook preInstall

    mkdir -vp $out/share/material-maker
    cp -vr \
      ./build/* \
      ./addons/material_maker/nodes  \
      ./material_maker/environments  \
      ./material_maker/examples  \
      ./material_maker/library  \
      ./material_maker/meshes  \
      ./material_maker/misc/export \
      $out/share/material-maker

    mkdir -vp $out/bin
    ln -vs $out/share/material-maker/material-maker $out/bin/material-maker

    runHook postInstall
  '';

  fixupPhase = ''
    runHook preFixup

    # patchelf \
    #   --set-interpreter '${stdenv.cc.bintools.dynamicLinker}' \
    #   --set-rpath ${lib.makeLibraryPath finalAttrs.buildInputs} \
    #   $out/share/material-maker/material-maker

    runHook postFixup
  '';
  dontStrip = true;
  passthru.updateScript = nix-update-script { };

  meta = {
    description = "Procedural materials authoring tool";
    mainProgram = "material-maker";
    homepage = "https://www.materialmaker.org";
    license = lib.licenses.mit;
    platforms = [ "x86_64-linux" ];
    maintainers = with lib.maintainers; [ lelgenio ];
  };
})
