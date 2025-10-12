{
  stdenv,
  cmake,
  ninja,
  lib,
  fetchFromGitHub,
  pkg-config,
  ffmpeg,
  ncurses,
  glfw,
  Cocoa,
}:
stdenv.mkDerivation rec {
  pname = "glslViewer";
  version = "3.2.4-42c1898";
  src = fetchFromGitHub {
    owner = "patriciogonzalezvivo";
    repo = pname;
    fetchSubmodules = true;
    rev = "42c1898";
    sha256 = "sha256-hWnv11oZTbXCSECZFtR2fow/+Z3qVNyuHSFpehlWUB8=";
  };
  nativeBuildInputs = [cmake ninja pkg-config];
  buildInputs =
    [
      ncurses
      ffmpeg
      glfw
    ]
    ++ lib.optional stdenv.isDarwin Cocoa;
  patchPhase = ''
    echo "" > ./deps/vera/deps/CMakeLists.txt
  '';

  cmakeFlags = [ "-DCMAKE_POLICY_VERSION_MINIMUM=3.20" ];

  meta = with lib; {
    description = "Live GLSL coding renderer";
    homepage = "http://patriciogonzalezvivo.com/2015/glslViewer/";
    license = licenses.bsd3;
    platforms = platforms.unix;
  };
}
