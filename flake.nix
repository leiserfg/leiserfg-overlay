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
      # armourpaint = pkgs.callPackage ./pkgs/armourpaint {};   It's failing to build now
      glslviewer = pkgs.callPackage ./pkgs/glslviewer {};
      nsxiv-extras = pkgs.callPackage ./pkgs/nsxiv-extras {};
      material-maker = pkgs.callPackage ./pkgs/material-maker {};
      dwarfs = pkgs.callPackage ./pkgs/dwarfs {};
      yuzu = pkgs.libsForQt5.callPackage ./pkgs/yuzu {};
      # wasm2luajit = pkgs.callPackage ./pkgs/wasm2luajit {};
      xmake = pkgs.callPackage ./pkgs/xmake {};
      sdl-jstest = (prev.sdl-jstest.override (old: rec {
        SDL2 = (prev.SDL2.override { udevSupport = true; });
        }
      ));

      # awesome = (prev.awesome.overrideAttrs (old: rec {
      #   version = "4.4.0.alpha-lj";
      #   patchse = [];
      #   src = pkgs.fetchFromGitHub { 
      #       owner = "awesomewm";
      #       repo = "awesome";
      #       rev = "9ca7bb4";
      #       sha256 = "sha256-RRpwAIYNLkovXI0y/eXO9uRDqB4qQcXlnYYUCEmx/EA="; 
      #   };
      # }));

      fzf = pkgs.callPackage ./pkgs/fzf {};
      yuzu-ea = pkgs.callPackage ./pkgs/yuzu { branch = "early-access"; };
    };


    packages.x86_64-linux = rec {
      inherit
        (pkgs)
        # armourpaint
        glslviewer
        nsxiv-extras
        material-maker
        dwarfs
        # awesome
       # wasm2luajit
        fzf
        yuzu-ea
        sdl-jstest
        xmake
        ;
      default = yuzu-ea;
    };
    formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
  };
}
