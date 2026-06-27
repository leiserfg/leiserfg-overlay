{ lib, rustPlatform, src }:

rustPlatform.buildRustPackage rec {
  pname = "calepin";
  version = "dev";

  inherit src;

  cargoLock.lockFile = "${src}/Cargo.lock";

  # Build from workspace
  cargoBuildFlags = [ "-p" "calepin" ];
  cargoTestFlags = [ "-p" "calepin" ];

  meta = with lib; {
    description = "A Rust CLI for preprocessing Typst documents with executable code chunks";
    homepage = "https://github.com/vincentarelbundock/calepin";
    license = licenses.mit;
    maintainers = [ ];
    mainProgram = "calepin";
  };
}
