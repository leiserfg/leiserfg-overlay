{
  stdenv,
  lib,
  nim,
  src,
  nimony-src,
}:
stdenv.mkDerivation {
  pname = "nim2-nimony-lsp";
  version = "0.7.1";

  inherit src;

  nativeBuildInputs = [ nim ];

  configurePhase = ":";

  env.HOME = "/tmp";
  env.XDG_CACHE_HOME = "/tmp/.cache";

  sourceRoot = "source/server";

  buildPhase = ''
    nim c -r --warnings:off -d:release --path:${nimony-src}/src/lib src/nimony_lsp.nim
  '';

  installPhase = ''
    mkdir -p $out/bin
    ls ./
    cp bin/nimony_lsp $out/bin/nimony-lsp
  '';

  meta = with lib; {
    description = "Language Server Protocol implementation for Nimony";
    homepage = "https://github.com/leiserfg/nim2-nimony-lsp";
    license = licenses.mit;
    platforms = platforms.unix;
    maintainers = [ ];
  };
}
