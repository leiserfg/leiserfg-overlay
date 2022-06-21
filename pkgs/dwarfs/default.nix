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
    repo = pname;
    fetchSubmodules = true;
    rev = "v${version}";
    sha256 = "sha256-bGJkgcq8JxueRTX08QpJv1A0O5wXbiIgUY7BrY0Ln/M=";
  };
  nativeBuildInputs = [
  cmake
  ninja
  bison
  flex
  ronn
  fuse3
  pkg-config

  ];
  buildInputs = [ ];
    
  patchPhase = ''
    sed '31 i set(PRJ_GIT_REV  v${version})' -i cmake/version.cmake
    sed '52 i set(PRJ_GIT_DESC v${version})' -i cmake/version.cmake
  '';

  meta = with lib; {
    description = "A fast high compression read-only file system";
    homepage = "https://github.com/mhx/dwarfs";
    license = licenses.gpl3;
    platforms = platforms.linux;
  };
}
