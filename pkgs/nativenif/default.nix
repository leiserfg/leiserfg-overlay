{
  stdenv,
  lib,
  nim,
  nimony-src,
  src,
}:
stdenv.mkDerivation {
  pname = "nativenif";
  version = "unstable";

  inherit src;

  nativeBuildInputs = [ nim ];

  configurePhase = ''
    # Link nimony as a sibling directory since the build expects ../nimony
    ln -s ${nimony-src} ../nimony
  '';

  env.HOME = "/tmp";
  env.XDG_CACHE_HOME = "/tmp/.cache";

  buildPhase = ''
    # Compile the three binaries
    nim c -d:release src/arkham/arkham.nim
    nim c -d:release src/nifasm/nifasm.nim
    nim c -d:release src/ithaqua/ithaqua.nim
  '';

  installPhase = ''
    mkdir -p $out/bin
    
    # Install arkham
    cp bin/arkham $out/bin/arkham
    
    # Install nifasm (it gets built in src/nifasm directory)
    cp src/nifasm/nifasm $out/bin/nifasm
    
    # Install ithaqua
    cp bin/ithaqua $out/bin/ithaqua
  '';

  meta = with lib; {
    description = "A native backend for Leng, the mid-level NIF dialect";
    homepage = "https://github.com/nim-lang/nativenif";
    license = licenses.mit;
    platforms = platforms.unix;
  };
}
