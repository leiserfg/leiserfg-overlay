{
  description = "My home-brew packages";

  # inputs.nixpkgs.url = "github:nixos/nixpkgs/b8697e57f10292a6165a20f03d2f42920dfaf973";
  inputs.nixpkgs.url = "github:nixos/nixpkgs/nixos-24.05";
  # inputs.suyu-flake.url = "github:leiserfg/suyu-flake/rebrand";
  # inputs.suyu-flake.url = "github:Noodlez1232/suyu-flake";
  # inputs.suyu-flake.inputs.nixpkgs.follows = "nixpkgs";

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
      # sudachi = pkgs.callPackage ./pkgs/torzu/sudachi.nix suyu-deps;
    };

    packages.x86_64-linux = rec {
      inherit
        (pkgs)
        glslviewer
        material-maker
        waydroid-script
        torzu
        nx_tzdb
        compat-list
        ;
      # default = yuzu-early-access;
      default = torzu;
    };
    formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
  };
}
