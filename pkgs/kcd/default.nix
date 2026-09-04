{ lib, buildGoModule, src }:

buildGoModule {
  pname = "kcd";
  version = "unstable";

  inherit src;

  vendorHash = "sha256-6zwzWlboTQeZcBiiHU7Jt+vDn2FYCrQ8CzGgCntKRGo=";

  subPackages = [ "cmd/kcd" ];

  env.CGO_ENABLED = "0";

  ldflags = [
    "-s"
    "-w"
    "-X main.version=unstable"
  ];

  meta = with lib; {
    description = "Headless KDE Connect daemon written in Go";
    homepage = "https://github.com/bethropolis/kcd";
    license = licenses.mit;
    maintainers = [ ];
    platforms = platforms.linux;
    mainProgram = "kcd";
  };
}
