{
  stdenv,
  lib,
  nim,
  mimalloc,
  src,
}:
stdenv.mkDerivation {
  pname = "nimony";
  version = "unstable-2024-07-16";

  inherit src;

  nativeBuildInputs = [ nim ];

  configurePhase = ":";

  env.HOME = "/tmp";
  env.XDG_CACHE_HOME = "/tmp/.cache";

  patchPhase = ''
    # Use mimalloc from nixpkgs instead of git submodule
    rm -rf vendor/mimalloc
    ln -s ${mimalloc.src} vendor/mimalloc
    # Disable git submodule update since we're using nixpkgs version
    sed -i 's/exec "git submodule update --init"/# git submodule disabled in nix build/' src/hastur.nim
    # Fix nimcache_static to use XDG_CACHE_HOME instead of a read-only location
    sed -i 's|result = parentDir(stdlibDir()) / "nimcache_static"|result = (getEnv("XDG_CACHE_HOME", getEnv("HOME") / ".cache")) / "nimony" / "cache_static"|' src/nimony/deps.nim
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
