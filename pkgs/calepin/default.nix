{
  lib,
  rustPlatform,
  src,
  typst,
}:

rustPlatform.buildRustPackage rec {
  pname = "calepin";
  version = "dev";

  inherit src;

  cargoLock.lockFile = "${src}/Cargo.lock";

  doCheck = false;

  # Build from workspace
  cargoBuildFlags = [
    "-p"
    "calepin"
  ];
  cargoTestFlags = [
    "-p"
    "calepin"
  ];

  doCheck = false;

  nativeBuildInputs = [ typst ];

  meta = with lib; {
    description = "A Rust CLI for preprocessing Typst documents with executable code chunks";
    homepage = "https://github.com/vincentarelbundock/calepin";
    license = licenses.mit;
    maintainers = [ ];
    mainProgram = "calepin";
  };
}
