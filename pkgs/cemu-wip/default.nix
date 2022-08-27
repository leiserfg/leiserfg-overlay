{
  clangStdenv,
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
  wxGTK31-gtk3,
  zstd,
  fmt,
  glm,
  xorg,
}: let
  zarchive = clangStdenv.mkDerivation rec {
    pname = "ZArchive";
    version = "0.1.1";
    src = fetchFromGitHub {
      owner = "Exzap";
      repo = pname;
      rev = "v${version}";
      sha256 = "sha256-qsUn2aOeMeGJKmxJ2Hf9jDbfwvS3REUes1eNkQFq62I=";
    };
    patchPhase = ''
    substituteInPlace ./CMakeLists.txt --replace libzstd_static libzstd_shared
    '';
    nativeBuildInputs = [cmake ninja];
    buildInputs = [zstd];
  };

  cubeb = clangStdenv.mkDerivation rec {
    pname = "cubeb";
    version = "0.2-cmake";
    src = fetchFromGitHub {
      owner = "mozilla";
      repo = pname;
      rev = "dc511c6";
      sha256 = "sha256-pkWEnD5RqWkkyq/6umQ3Oztkxx1wszqa7mEJqvZ7kAo=";
    };

    nativeBuildInputs = [cmake ninja];
    cmakeFlags = [
      "-DUSE_SANITIZERS=OFF"
      "-DBUILD_TESTS=OFF"
      "-DBUILD_TOOLS=OFF"
      "-DBUILD_SHARED_LIBS=ON"
    ];
    # buildInputs = [];
  };
in
  clangStdenv.mkDerivation rec {
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
            fmt
            glm
            curl.dev
            pugixml
            imgui
            rapidjson
            cubeb
            boost
            libzip
            glslang
            vulkan-headers
            vulkan-loader
            wxGTK31-gtk3
            zarchive
            xorg.libXrender
    ];

    meta = with lib; {
      description = "A fast high compression read-only file system";
      homepage = "https://github.com/mhx/dwarfs";
      license = licenses.gpl3;
      platforms = platforms.linux;
    };
  }
