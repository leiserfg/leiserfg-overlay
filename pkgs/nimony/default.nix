{
  stdenv,
  lib,
  fetchFromGitHub,
  nim,
}:
stdenv.mkDerivation rec {
  pname = "nimony";
  version = "unstable-2024-07-16";

  src = fetchFromGitHub {
    owner = "nim-lang";
    repo = "nimony";
    rev = "969dbfdda799dd1d5a122dfedd278313bb20f608";
    hash = "sha256-oAnNDgMSVvdMyFbx+bBxR4zLfbiVmtdvQuSTttzCBd8=";
  };

  nativeBuildInputs = [nim];

  buildPhase = ''
    nim c -r src/hastur build all
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
