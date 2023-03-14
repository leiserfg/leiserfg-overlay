{
  description = "My home-brew packages";
  inputs.nixpkgs.url = "nixpkgs/nixos-22.11";
  inputs.git-branchless.url = "github:arxanas/git-branchless";
  inputs.emanote.url = "github:EmaApps/emanote";
  inputs.fenix = {
    url = "github:nix-community/fenix";
    inputs.nixpkgs.follows = "nixpkgs";
  };

  outputs = {
    self,
    nixpkgs,
    git-branchless,
    emanote,
    fenix,
    ...
  } @ inputs: let
    pkgs = import nixpkgs {
      system = "x86_64-linux";
      overlays = [self.overlays.default git-branchless.overlay fenix.overlays.default];
    };
  in {
    overlays.default = final: prev: {
      glslviewer = pkgs.callPackage ./pkgs/glslviewer {};
      nsxiv-extras = pkgs.callPackage ./pkgs/nsxiv-extras {};
      material-maker = pkgs.callPackage ./pkgs/material-maker {};
      dwarfs = pkgs.callPackage ./pkgs/dwarfs {};
      wasm2luajit = pkgs.callPackage ./pkgs/wasm2luajit {};
      doggo = pkgs.callPackage ./pkgs/doggo {};
      llama-rs = pkgs.callPackage ./pkgs/llama-rs {
        rustPlatform = pkgs.makeRustPlatform {
          cargo = fenix.packages.x86_64-linux.minimal.toolchain;
          rustc = fenix.packages.x86_64-linux.minimal.toolchain;
        };
      };
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
      /*
      .override {lua = pkgs.luajit;};
      */
      pmenu = pkgs.callPackage ./pkgs/pmenu {};
      ansel = pkgs.callPackage ./pkgs/ansel {};
      vokoscreen-ng = pkgs.libsForQt5.callPackage ./pkgs/vokoscreen-ng (with pkgs; {
        inherit (gst_all_1) gstreamer gst-plugins-base gst-plugins-good gst-plugins-bad gst-plugins-ugly;
      });

      emanote = emanote.packages.x86_64-linux.default;
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
        doggo
        git-branchless
        emanote
        ansel
        vokoscreen-ng
        /* llama-rs */
        ;
      default = awesome;
    };
    formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
  };
}
