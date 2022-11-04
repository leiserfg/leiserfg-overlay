{
  description = "My home-brew packages";
  inputs.nixpkgs.url = "nixpkgs/nixos-unstable";
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
      glslviewer = pkgs.callPackage ./pkgs/glslviewer {};
      nsxiv-extras = pkgs.callPackage ./pkgs/nsxiv-extras {};
      material-maker = pkgs.callPackage ./pkgs/material-maker {};
      dwarfs = pkgs.callPackage ./pkgs/dwarfs {};
      # yuzu-early-access = prev.yuzu-early-access;
      wasm2luajit = pkgs.callPackage ./pkgs/wasm2luajit {};
      doggo = pkgs.callPackage ./pkgs/doggo {};
      awesome = prev.awesome.overrideAttrs (old: rec {
        version = "4.4.0.alpha-lj";
        patches = [];
        src = pkgs.fetchFromGitHub {
          owner = "awesomewm";
          repo = "awesome";
          rev = "9ca7bb4";
          sha256 = "sha256-RRpwAIYNLkovXI0y/eXO9uRDqB4qQcXlnYYUCEmx/EA=";
        };
      });

      controllermap = pkgs.callPackage ./pkgs/controllermap {};
      pmenu = pkgs.callPackage ./pkgs/pmenu {};
      godot4 = pkgs.callPackage ./pkgs/godot {};
    };

    packages.x86_64-linux = rec {
      inherit
        (pkgs)
        pmenu
        # armourpaint
        glslviewer
        nsxiv-extras
        material-maker
        dwarfs
        awesome
        wasm2luajit
        godot4
        tdesktop-fresh
        fzf
        controllermap
        doggo
        ;
      default = doggo;
    };
    formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
  };
}
