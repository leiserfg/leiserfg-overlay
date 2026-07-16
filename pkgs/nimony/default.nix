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

  configurePhase = ":";

  unpackPhase = ''
    cp -r $src builddir
    chmod -R u+w builddir
    cd builddir
  '';

  env.HOME = "/tmp";
  env.XDG_CACHE_HOME = "/tmp/.cache";

  preBuildPhase = ''
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
