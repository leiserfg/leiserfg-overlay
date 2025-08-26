{
  appimageTools,
  makeWrapper,
  fetchurl,
  lib,
}:

let
  pname = "eden-emulator";
  version = "0.0.3-rc3";
  sha256 = "sha256-zCiHJv4tykgOjG1remsTyMI4xFbev7we5TtUsq8mZXQ=";

  src = fetchurl {
    url = "https://github.com/eden-emulator/Releases/releases/download/v${version}/Eden-Linux-v${version}-steamdeck.AppImage";
    inherit sha256;
  };

in
appimageTools.wrapType2 {

  inherit pname version src;

  profile = ''
    export LC_ALL=C.UTF-8
  '';

  nativeBuildInputs = [ makeWrapper ];

  extraPkgs = pkgs: [
  ];

  meta = with lib; {
    description = "";
    license = licenses.mit;
    platforms = [ "x86_64-linux" ];
    maintainers = [ ];
  };
}
