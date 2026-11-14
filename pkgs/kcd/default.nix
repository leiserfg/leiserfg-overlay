{
  lib,
  buildGoModule,
  fetchFromGitHub,
}:

buildGoModule {
  pname = "kcd";
  version = "unstable";

  src = fetchFromGitHub {
    owner = "bethropolis";
    repo = "kcd";
    rev = "bc6c0947812a2280a81282d39b6273b658d5ff00";
    hash = "sha256-5eyeCu2KAO6vCdnbuAlxzr/NH4yBfPuw3agbesCsa0Y=";
  };

  vendorHash = "sha256-8/cubNx2fsRntDX18HMAtlWXLneN8QSmejshsOUh7tQ=";

  subPackages = [ "cmd/kcd" ];

  env.CGO_ENABLED = "0";

  ldflags = [
    "-s"
    "-w"
    "-X main.version=unstable"
  ];
  doCheck = false;
  meta = with lib; {
    description = "Headless KDE Connect daemon written in Go";
    homepage = "https://github.com/bethropolis/kcd";
    license = licenses.mit;
    maintainers = [ ];
    platforms = platforms.linux;
    mainProgram = "kcd";
  };
}
