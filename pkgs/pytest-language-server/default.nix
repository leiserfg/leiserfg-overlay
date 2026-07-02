{ lib
, rustPlatform
, src
, ...
}:

rustPlatform.buildRustPackage {
  pname = "pytest-language-server";
  version = "0.23.0";

  inherit src;

  cargoLock = {
    lockFile = "${src}/Cargo.lock";
  };

  doCheck = false;

  meta = with lib; {
    description = "A blazingly fast Language Server Protocol implementation for pytest";
    homepage = "https://github.com/bellini666/pytest-language-server";
    license = licenses.mit;
    maintainers = [ ];
    mainProgram = "pytest-language-server";
  };
}
