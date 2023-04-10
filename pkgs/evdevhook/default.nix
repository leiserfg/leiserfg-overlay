{
  withFFMPG ? true,
  stdenv,
  cmake,
  ninja,
  lib,
  fetchFromGitHub

,        libevdev
,        udev
,        glibmm
,        nlohmann_json
,        zlib
,  pkg-config
}:
stdenv.mkDerivation rec {
  pname = "evdevhook";
  version = "0.1";
  src = fetchFromGitHub {
    owner = "v1993";
    repo = pname;
    fetchSubmodules = true;
    rev = "e822870";
    sha256 = "sha256-af9B04k8+7nO3rhsYx223N+fpcVjExi9KDXF+b719/8=";
  };
  nativeBuildInputs = [cmake ninja pkg-config];
  buildInputs =
    [
        libevdev
        udev
        glibmm
        nlohmann_json
        zlib
    ];

  meta = with lib; {
    description = "Live GLSL coding renderer";
    homepage = "http://patriciogonzalezvivo.com/2015/glslViewer/";
    license = licenses.bsd3;
    platforms = platforms.linux;
  };
}
