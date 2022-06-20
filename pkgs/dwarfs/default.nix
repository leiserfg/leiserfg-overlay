{
  stdenv,
  cmake,
  ninja,
  lib,
  fetchFromGitHub,
  bison,
  flex,
  ronn,
  fuse3,
  pkg-config,
}:
stdenv.mkDerivation rec {
  pname = "dwarfs";
  version = "0.6.1";
  src = fetchFromGitHub {
    owner = "mhx";
    repo = "v${pname}";
    fetchSubmodules = true;
    rev = version;
    sha256 = "sha256-3wT2fyznMkmyls4wUmBKZDIMo35qEfKjLkUYWd+UTLE=";
  };
  nativeBuildInputs = [cmake ninja

  bison
  flex
  ronn
  fuse3
  pkg-config

  ];
  buildInputs = [ ];


  meta = with lib; {
    description = "A fast high compression read-only file system";
    homepage = "http://patriciogonzalezvivo.com/2015/glslViewer/";
    license = licenses.gnu;
    platforms = platforms.linux;
  };
}
