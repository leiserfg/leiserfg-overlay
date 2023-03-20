{
  stdenv,
  lib,
  fetchFromGitHub,
}:
stdenv.mkDerivation rec {
  pname = "alpaca.cpp";
  version = "0.0.1";
  src = fetchFromGitHub {
    owner = "antimatter15";
    repo = pname;
    rev = "99f3908";
    sha256 = "sha256-uQFQl10JjIjkHKWwHs5WCXvcJerzk0IkTqDaWMO0UT8=";
  };
  nativeBuildInputs = [];
  buildInputs = [];

  buildPhase = ''
    make chat
  '';

  installPhase = ''
    mkdir -p $out/bin/
    cp ./chat $out/bin/chat
  '';
  meta = with lib; {
    description = "Run a fast ChatGPT-like model locally on your device";
    homepage = "https://github.com/antimatter15/alpaca.cpp";
    license = licenses.gpl3;
    platforms = platforms.linux;
  };
}
