{
  description = "My home-brew packages";

  inputs.nixpkgs.url = "github:nixos/nixpkgs/b8697e57f10292a6165a20f03d2f42920dfaf973";
  # inputs.suyu-flake.url = "github:leiserfg/suyu-flake/rebrand";
  inputs.suyu-flake.url = "github:Noodlez1232/suyu-flake";
  inputs.suyu-flake.inputs.nixpkgs.follows = "nixpkgs";

  outputs = {
    self,
    nixpkgs,
    ...
  } @ inputs: let
    pkgs = import nixpkgs {
      system = "x86_64-linux";
      overlays = [self.overlays.default];
    };
  in {
    overlays.default = final: prev: {
      glslviewer = pkgs.callPackage ./pkgs/glslviewer {};
      material-maker = pkgs.callPackage ./pkgs/material-maker {};
      waydroid-script = pkgs.callPackage ./pkgs/waydroid-script {};
      kitty = pkgs.callPackage ./pkgs/kitty {};
      suyu = inputs.suyu-flake.packages.x86_64-linux.suyu;
      sudachi = pkgs.callPackage ./pkgs/sudachi {};
      basedpyright = pkgs.callPackage ./pkgs/basedpyright {};
    };

    packages.x86_64-linux = rec {
      inherit
        (pkgs)
        glslviewer
        material-maker
        yuzu-early-access
        waydroid-script
        suyu
        sudachi
        kitty
        basedpyright
        ;
      default = yuzu-early-access;
    };
    formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
  };
}
