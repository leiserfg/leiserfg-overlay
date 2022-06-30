{
  description = "My home-brew packages";
  inputs.nixpkgs.url = "nixpkgs/nixos-22.05";

  outputs = {
    self,
    nixpkgs,
  }: let
    pkgs = import nixpkgs {
      system = "x86_64-linux";
      overlays = [self.overlays.default];
    };
  in {
    overlays.default = final: prev: {
      # armourpaint = pkgs.callPackage ./pkgs/armourpaint {};   It's failing to build now
      glslviewer = pkgs.callPackage ./pkgs/glslviewer {};
      nsxiv-extras = pkgs.callPackage ./pkgs/nsxiv-extras {};
      material-maker = pkgs.callPackage ./pkgs/material-maker {};
      dwarfs = pkgs.callPackage ./pkgs/dwarfs {};
      wasm2luajit  = pkgs.callPackage ./pkgs/wasm2luajit {};
    };
    packages.x86_64-linux = rec {
      inherit
        (pkgs)
        # armourpaint
        glslviewer
        nsxiv-extras
        material-maker
        dwarfs
        wasm2luajit ;
        default = dwarfs;
    };
    formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
  };
}
