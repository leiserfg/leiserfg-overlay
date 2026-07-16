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

  preBuildPhase = ''
    cp -r $src builddir
    cd builddir
    git init
    git config user.email "nobody@example.com"
    git config user.name "Nobody"
    git add .
    git commit -m "Initial commit"
  '';

  buildPhase = ''
    nim c -r --warnings:off src/hastur build all
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp -r builddir/bin/* $out/bin/
    mkdir -p $out/lib
    cp -r builddir/lib/* $out/lib/
  '';

  meta = with lib; {
    description = "A new Nim implementation in heavy development";
    homepage = "https://github.com/nim-lang/nimony";
    license = licenses.mit;
    platforms = platforms.unix;
  };
}
