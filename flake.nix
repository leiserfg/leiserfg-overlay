{
  description = "My home-brew packages";
  inputs.nixpkgs.url = "github:nixos/nixpkgs/b8697e57f10292a6165a20f03d2f42920dfaf973";

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
      doggo = pkgs.callPackage ./pkgs/doggo {};
    };

    packages.x86_64-linux = rec {
      inherit
        (pkgs)
        glslviewer
        material-maker
        doggo
        yuzu-early-access
        waydroid-script
        ;
      default = yuzu-early-access;
    };
    formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
  };
}
