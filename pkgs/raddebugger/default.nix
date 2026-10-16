{
  lib,
  clangStdenv,
  src,
  pkg-config,
  freetype,
  libX11,
  libXext,
  libXfixes,
  libXrandr,
  libGL,
  libglvnd,
}:

clangStdenv.mkDerivation {
  pname = "raddebugger";
  version = "unstable-2026-10-15";
  inherit src;

  nativeBuildInputs = [
    pkg-config
  ];

  buildInputs = [
    freetype
    libX11
    libXext
    libXfixes
    libXrandr
    libGL
    libglvnd
  ];

  buildPhase = ''
    runHook preBuild
    ${clangStdenv.shell} ./build.sh release
    runHook postBuild
  '';

  installPhase = ''
    runHook preInstall
    install -Dm755 build/raddbg $out/bin/raddbg
    install -Dm644 LICENSE $out/share/licenses/raddebugger/LICENSE
    runHook postInstall
  '';

  meta = {
    description = "Native user-mode graphical debugger from Epic Games";
    homepage = "https://github.com/EpicGames/raddebugger";
    license = lib.licenses.mit;
    platforms = [ "x86_64-linux" ];
    mainProgram = "raddbg";
  };
}
