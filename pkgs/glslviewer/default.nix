{
  withFFMPG ? true,
  stdenv,
  cmake,
  ninja,
  lib,
  fetchFromGitHub,
  pkg-config,
  libX11,
  libXrandr,
  libXinerama,
  libXcursor,
  libXi,
  libXext,
  libGLU,
  ffmpeg-full,
  ncurses,
}:
stdenv.mkDerivation rec {
  pname = "glslViewer";
  version = "v3.1.1";
  src = fetchFromGitHub {
    owner = "patriciogonzalezvivo";
    repo = pname;
    fetchSubmodules = true;
    rev = version;
    sha256 = "sha256-JUGtWco2ZN+hMi5s44ckjp6wWG7aC0DQy9+GiWT8aZ8=";
  };
  nativeBuildInputs = [cmake ninja pkg-config];
  buildInputs =
    [
      libX11
      libXrandr
      libXinerama
      libXcursor
      libXi
      libXext
      libGLU
      ncurses
    ]
    ++ lib.optional withFFMPG ffmpeg-full;

  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE='Release'"
    "-GNinja"
  ];

  meta = with lib; {
    description = "Live GLSL coding renderer";
    homepage = "http://patriciogonzalezvivo.com/2015/glslViewer/";
    license = licenses.bsd3;
    platforms = platforms.linux;
  };
}
