{
  stdenv,
  lib,
  fetchFromGitHub,
  wayland-protocols,
  wayland,
  which,
  wayland-scanner,

  pkg-config,
  libarchive,
  uthash,
  python3,
}:
stdenv.mkDerivation rec {
  pname = "wl_shimeji";
  version = "0.0.2";
  src = fetchFromGitHub {
    owner = "CluelessCatBurger";
    repo = pname;
    rev = version;
    sha256 = "sha256-1r/dJ4cZ87MQiE+kxpHaBesOkWvyJyvMWOPn2XKDVWA=";
    fetchSubmodules = true;
  };
  nativeBuildInputs = [
    (python3.withPackages (ps: [ ps.pillow ]))
    pkg-config
    which
  ];
  buildInputs = [
    wayland-protocols
    wayland-scanner
    wayland
    # libwayland-client
    libarchive
    uthash
  ];
  makeFlags = [ "PREFIX=$(out)" ];
  postInstall = ''
    # No idea why patchShebangs is not doing it
    sed -i "1s|/usr.*|$(which python)|"  $out/bin/shimejictl
    # sed -i "s|ExecStart=.*|ExecStart=|$out/bin/shimeji-overlayd|"  $out/share/systemd/user/wl_shimeji.service
  '';
  meta = with lib; {
    description = "Run a fast ChatGPT-like model locally on your device";
    homepage = "https://github.com/antimatter15/alpaca.cpp";
    license = licenses.gpl3;
    platforms = platforms.linux;
  };
}
