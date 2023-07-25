{
  description = "My home-brew packages";
  inputs.nixpkgs.url = "nixpkgs/nixos-unstable";
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

      yuzu = pkgs.callPackage ./pkgs/yuzu {branch = "early-access";};
      pylyzer = pkgs.callPackage ./pkgs/pylyzer {
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
      pasystray = prev.pasystray.overrideAttrs (old: rec {
        pname = "pasystray";
        version = "0.8.2";
        src = pkgs.fetchFromGitHub {
          owner = "christophgysin";
          repo = "pasystray";
          rev = version;
          sha256 = "sha256-QaTQ8yUviJaFEQaQm2vYAUngqHliKe8TDYqfWt1Nx/0=";
        };
      });
      /*
      .override {lua = pkgs.luajit;};
      */
      pmenu = pkgs.callPackage ./pkgs/pmenu {};
      ansel = pkgs.callPackage ./pkgs/ansel {};
      alpaca-cpp = pkgs.callPackage ./pkgs/alpaca.cpp {};
      emanote = emanote.packages.x86_64-linux.default;
      inkscape = pkgs.callPackage ./pkgs/inkscape {};
      lib2geom = pkgs.callPackage ./pkgs/lib2geom {};
    };

    packages.x86_64-linux = rec {
      inherit
        (pkgs)
        pmenu
        # armourpaint
        lib2geom
        glslviewer
        nsxiv-extras
        alpaca-cpp
        material-maker
        dwarfs
        awesome
        wasm2luajit
        doggo
        git-branchless
        emanote
        ansel
        llama-rs
        pasystray
        pylyzer
        erg
        yuzu
        inkscape
        ;
      default = pylyzer;
    };
    formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
  };
}
