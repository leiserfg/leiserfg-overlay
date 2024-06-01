{
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
  Cocoa,
}:
stdenv.mkDerivation rec {
  pname = "glslViewer";
  version = "3.2.4";
  src = fetchFromGitHub {
    owner = "patriciogonzalezvivo";
    repo = pname;
    fetchSubmodules = true;
    rev = version;
    sha256 = "sha256-Ve3wmX5+kABCu8IRe4ySrwsBJm47g1zvMqDbqrpQl88=";
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
      ffmpeg
    ]
    ++ lib.optional stdenv.isDarwin Cocoa;

  meta = with lib; {
    description = "Live GLSL coding renderer";
    homepage = "http://patriciogonzalezvivo.com/2015/glslViewer/";
    license = licenses.bsd3;
    platforms = platforms.unix;
  };
}
