{
  lib,
  stdenv,
  fetchFromGitHub,
  zig_0_16,
  llvmPackages,
  lld,
  gcc,
  nix-update-script,
}:

stdenv.mkDerivation (finalAttrs: {
  pname = "open-jai";
  version = "0.1.0-unstable-2025-05-17";

  src = fetchFromGitHub {
    owner = "withlang-dev";
    repo = "open-jai";
    rev = "d4e17beecb27cd8c9638e27532cd11922d000f5a";
    hash = "sha256-ZUtajuY+JTxtX1486WzCBSRMB9qrK+kFENBwcsoepe0=";
  };

  nativeBuildInputs = [
    zig_0_16
    llvmPackages.llvm
    gcc
  ];

  buildInputs = [
    llvmPackages.libllvm
    lld
    gcc.cc.lib
  ];

  buildPhase = ''
    cd bootstrap
    zig build -Doptimize=ReleaseFast
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp zig-out/bin/openjai $out/bin/
  '';

  passthru.updateScript = nix-update-script { };

  meta = {
    description = "Open source implementation of a Jai-style systems programming language and compiler";
    homepage = "https://github.com/withlang-dev/open-jai";
    license = lib.licenses.mit;
    maintainers = with lib.maintainers; [ leiserfg ];
    platforms = lib.platforms.linux;
    mainProgram = "openjai";
  };
})
