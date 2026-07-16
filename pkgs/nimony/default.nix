{
  stdenv,
  lib,
  nim,
  git,
  src,
}:
stdenv.mkDerivation rec {
  pname = "nimony";
  version = "unstable-2024-07-16";

  inherit src;

  nativeBuildInputs = [nim git];

  env.HOME = "/tmp";
  env.XDG_CACHE_HOME = "/tmp/.cache";

  buildPhase = ''
    nim c -r --warnings:off src/hastur build all
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp -r bin/* $out/bin/
    mkdir -p $out/lib
    cp -r lib/* $out/lib/
  '';

  meta = with lib; {
    description = "A new Nim implementation in heavy development";
    homepage = "https://github.com/nim-lang/nimony";
    license = licenses.mit;
    platforms = platforms.unix;
  };
}
