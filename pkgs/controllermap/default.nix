{
  withFFMPG ? true,
  stdenv,
  lib,
  fetchFromGitHub,
  pkg-config,
  SDL2
}:
stdenv.mkDerivation rec {
  pname = "controllermap";
  version = "2.1.14";
  src = SDL2.src;
  nativeBuildInputs = [pkg-config];
  custom_SDL = (SDL2.override { udevSupport = true; });
  buildInputs = [
      custom_SDL
    ];
  dontConfigure = true;
  buildPhase = ''
      cd ./test
      echo $C_INCLUDE_PATH
      sed -i '/bmp/s%"\([^"][^"]*\)"%"/'$out'/share/controllermap/\1"%' controllermap.c

      SDLCONFIG=${custom_SDL}/bin/sdl2-config
      $CC \
      -I ${custom_SDL.dev}/include/SDL2 \
      -L ${custom_SDL}/lib/ \
      -l SDL2 \
      -o controllermap \
      controllermap.c
  '';

 installPhase = ''
    install -Dm755 controllermap $out/bin/controllermap
    install -Dm644 controllermap.bmp $out/share/controllermap/controllermap.bmp
    install -Dm644 controllermap_back.bmp $out/share/controllermap/controllermap_back.bmp
    install -Dm644 axis.bmp $out/share/controllermap/axis.bmp
    install -Dm644 button.bmp $out/share/controllermap/button.bmp
 '';
  meta = with lib; {
    description = "SDL stuff";
    license = licenses.bsd3;
    platforms = platforms.linux;
  };
}
