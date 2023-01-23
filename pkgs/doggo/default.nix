{
  lib,
  buildGoModule,
  fetchFromGitHub,
}:
buildGoModule rec {
  pname = "doggo";
  version = "0.5.5";

  src = fetchFromGitHub {
    owner = "mr-karan";
    repo = pname;
    rev = "v${version}";
    sha256 = "sha256-qc6RYz2bVaY/IBGIXUYO6wyh7iUDAJ1ASCK0dFwZo6s=";
  };

  vendorSha256 = "sha256-UhSdYpK54c4+BAP/d/zU91LIBE05joOLHoV1XkNMYNw=";

  ldflags = [
    "-s"
    "-w"
    "-X main.buildVersion=${version}"
  ];

  postPatch = ''
    # Remove api so it does not get built
    rm -r ./cmd/api
  '';

  meta = with lib; {
    homepage = "https://github.com/mr-karan/doggo";
    description = "Command-line DNS Client for Humans. Written in Golang";
    license = licenses.gpl3;
    platforms = platforms.unix;
  };
}
