{
  lib,
  buildGoModule,
  fetchFromGitHub,
}:
buildGoModule rec {
  pname = "doggo";
  version = "0.5.4";

  src = fetchFromGitHub {
    owner = "mr-karan";
    repo = pname;
    rev = "v${version}";
    sha256 = "sha256-6jNs8vigrwKk47Voe42J9QYMTP7KnNAtJ5vFZTUW680=";
  };

  vendorSha256 = "sha256-pyzu89HDFrMQqYJZC2vdqzOc6PiAbqhaTgYakmN0qj8=";

  # buildInputs = [ncurses];

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
