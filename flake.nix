{
  description = "My home-brew packages";

  inputs.nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";

  outputs = {
    self,
    nixpkgs,
    ...
  } @ inputs: let
    system = "x86_64-linux";
    pkgs = import nixpkgs {
      system = system;
      overlays = [self.overlays.default];
    };

    suyu-deps = pkgs.kdePackages // {inherit (self.packages.${system}) nx_tzdb compat-list;};
  in {
    overlays.default = final: prev: {
      glslviewer = pkgs.callPackage ./pkgs/glslviewer {
        inherit (pkgs.darwin.apple_sdk.frameworks) Cocoa;
      };
      material-maker = pkgs.callPackage ./pkgs/material-maker {};
      waydroid-script = pkgs.callPackage ./pkgs/waydroid-script {};

      nx_tzdb = pkgs.callPackage ./pkgs/torzu/nx_tzdb.nix {};
      compat-list = pkgs.callPackage ./pkgs/torzu/compat-list.nix {};
      torzu = pkgs.callPackage ./pkgs/torzu/torzu.nix suyu-deps;
      citron = pkgs.callPackage ./pkgs/torzu/citron.nix suyu-deps; # WIP
      pyglossary = pkgs.callPackage ./pkgs/pyglossary {};
    };

    packages.x86_64-linux = rec {
      inherit
        (pkgs)
        glslviewer
        material-maker
        waydroid-script
        torzu
        # citron
        nx_tzdb
        compat-list
        pyglossary
        ;
      # default = yuzu-early-access;
      default = torzu;
    };
    formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
  };
}
