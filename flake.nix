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
      wasm2luajit = pkgs.callPackage ./pkgs/wasm2luajit {};
      darktable = (prev.darktable.overrideAttrs (old: rec {
        version = "4.0.0";
        src = pkgs.fetchurl {
          url = "https://github.com/darktable-org/darktable/releases/download/release-${version}/darktable-${version}.tar.xz";
          sha256 = "0bfcag6bj5vcmg4z4xjirs43iafcx89al6jl41i5mrhpjzszh5hl";
        };
      })).override {lua=pkgs.lua5_4;};
    };
    packages.x86_64-linux = rec {
      inherit
        (pkgs)
        # armourpaint
        glslviewer
        nsxiv-extras
        material-maker
        dwarfs
        darktable
        wasm2luajit
        ;
      default = dwarfs;
    };
    formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
  };
}
