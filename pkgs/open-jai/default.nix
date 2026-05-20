{
  lib,
  stdenv,
  fetchFromGitHub,
  zig_0_16,
  llvmPackages,
  lld,
  gcc,
  autoPatchelfHook,
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
    autoPatchelfHook
  ]
  ++ lib.optional stdenv.isLinux [ ];

  buildInputs = [
    llvmPackages.libllvm
    lld
    gcc.cc.lib
  ];

  buildPhase = ''
    sed 's|/bin/bash|${stdenv.shell}|g' -i Makefile
    make build
  '';

  installPhase = ''
    mkdir -p $out/bin
    mv out/bootstrap/bin/openjai $out/bin/.openjai-unwrapped
    mkdir -p $out/lib
    mv out/bootstrap/lib/openjai_runtime.o $out/lib/openjai_runtime.o

    cat > $out/bin/openjai << EOF
#!/bin/sh
exec $out/bin/.openjai-unwrapped "\$@" --runtime $out/lib/openjai_runtime.o
EOF
    chmod +x $out/bin/openjai
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
