{
  lib,
  stdenv,
  fetchFromGitHub,
  vulkan-loader,
  vulkan-headers,
  cmake,
  ninja,
  shaderc,
}: let
  rev = "d46ed5e";
in
  stdenv.mkDerivation rec {
    pname = "stable-diffusion.cpp";
    version = "0.0.1-${rev}";

    src = fetchFromGitHub {
      owner = "leejet";
      repo = pname;
      rev = rev;
      hash = "sha256-5i2HjkdaQEmlUWeHucQyrS8zNS+xyB7Zj+1oA/xsv2k=";

      fetchSubmodules = true;
    };

    buildInputs = [
      vulkan-loader
      vulkan-headers
      shaderc
    ];
    nativeBuildInputs = [
      cmake
      ninja
    ];
    cmakeFlags = [
      "-DSD_VULKAN=ON"
    ];

    meta = with lib; {
      homepage = "https://github.com/leejet/stable-diffusion.cpp";
      description = "Inference of Stable Diffusion and Flux in pure C/C++";
      license = licenses.mit;
      platforms = platforms.darwin ++ platforms.linux;
      # mainProgram = "kitty";
    };
  }
