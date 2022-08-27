{
  stdenv,
  cmake,
  ninja,
  lib,
  fetchFromGitHub,
  pkg-config,
  nasm,
  SDL2,
  curl,
  pugixml,
  imgui,
  rapidjson,
  boost,
  libzip,
  glslang,
  vulkan-headers,
  vulkan-loader,
  wxGTK31,
  zstd,
}: let
  zarchive = stdenv.mkDerivation rec {
    pname = "ZArchive";
    version = "0.1.1";
    src = fetchFromGitHub {
      owner = "Exzap";
      repo = pname;
      rev = "v${version}";
      sha256 = "sha256-qsUn2aOeMeGJKmxJ2Hf9jDbfwvS3REUes1eNkQFq62I=";
    };
    nativeBuildInputs = [cmake ninja];
    buildInputs = [zstd];
  };
in
  stdenv.mkDerivation rec {
    pname = "Cemu";
    version = "2.0";
    src = fetchFromGitHub {
      owner = "cemu-project";
      repo = pname;
      rev = "v${version}";
      sha256 = "sha256-X6Rju/JENTqtqapGo/a1nAnobdJfyhkxTOn17d6NXJI=";
    };
    nativeBuildInputs = [
      cmake
      nasm
      ninja
      pkg-config
    ];
    patches = [./no-vcpkg.patch];
    buildInputs = [
      SDL2
      curl.dev
      pugixml
      imgui
      rapidjson
      boost
      libzip
      glslang
      vulkan-headers
      vulkan-loader
      wxGTK31
      wxGTK31.gtk
      zarchive
    ];

    cmakeFlags = [
      "-DENABLE_CUBEB=OFF"
    ];

    meta = with lib; {
      description = "A fast high compression read-only file system";
      homepage = "https://github.com/mhx/dwarfs";
      license = licenses.gpl3;
      platforms = platforms.linux;
    };
  }
