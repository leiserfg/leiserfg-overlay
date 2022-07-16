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
  ffmpeg,
  ncurses,
}:
stdenv.mkDerivation rec {
  pname = "glslViewer";
  version = "2.1.2-f4d6790";
  src = fetchFromGitHub {
    owner = "patriciogonzalezvivo";
    repo = pname;
    fetchSubmodules = true;
    rev = "f4d6790";
    sha256 = "sha256-0xQEtWyy4bYvLph5bj4Wn09hNnMJlgtuiHe1DviG21U=";
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
    ++ lib.optional withFFMPG ffmpeg;

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
