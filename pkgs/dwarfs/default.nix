{
  stdenv,
  cmake,
  ninja,
  lib,
  fetchFromGitHub,
  bison,
  flex,
  ronn,
  pkg-config,
  git,

  fmt_8,
  boost,
  jemalloc,
  double-conversion,
  libiberty,
  lz4,
  zstd,
  lzma,
  openssl,
  libunwind,
  libdwarf,
  fuse3,
  glog,
  libarchive,
  libevent,

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
  git
  cmake
  ninja
  bison
  flex
  ronn
  pkg-config
  ];
  buildInputs = [
  fmt_8
  boost
  jemalloc
  double-conversion
  libiberty
  lz4
  lzma
  openssl
  libunwind
  libdwarf
  fuse3
  glog
  zstd
  libevent
  libarchive
  ];

  # patchPhase = ''
  #
  #   # insert some vals that are supposed to come from git
  #    # sed '/\s*execute_process./,+4d' -i cmake/version.cmake
  #    # sed '21 i set(PRJ_GIT_REV  "fake-commit")' -i cmake/version.cmake
  #    # sed '21 i set(PRJ_GIT_BRANCH  "main")' -i cmake/version.cmake
  #    # sed '21 i set(PRJ_GIT_DESC "v${version}")' -i cmake/version.cmake
  #
  #
  # '';
    patches = [./version.patch];
  meta = with lib; {
    description = "A fast high compression read-only file system";
    homepage = "https://github.com/mhx/dwarfs";
    license = licenses.gpl3;
    platforms = platforms.linux;
  };
}
