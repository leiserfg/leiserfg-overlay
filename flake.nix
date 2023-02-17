{
  description = "My home-brew packages";
  inputs.nixpkgs.url = "nixpkgs/nixos-22.11";
  inputs.git-branchless.url = "github:arxanas/git-branchless";
  inputs.emanote.url = "github:EmaApps/emanote";

  outputs = {
    self,
    nixpkgs,
    git-branchless,
    emanote,
    ...
  } @ inputs: let
    pkgs = import nixpkgs {
      system = "x86_64-linux";
      overlays = [self.overlays.default git-branchless.overlay];
    };
  in {
    overlays.default = final: prev: {
      glslviewer = pkgs.callPackage ./pkgs/glslviewer {};
      nsxiv-extras = pkgs.callPackage ./pkgs/nsxiv-extras {};
      material-maker = pkgs.callPackage ./pkgs/material-maker {};
      dwarfs = pkgs.callPackage ./pkgs/dwarfs {};
      wasm2luajit = pkgs.callPackage ./pkgs/wasm2luajit {};
      doggo = pkgs.callPackage ./pkgs/doggo {};
      awesome =
        (prev.awesome.overrideAttrs (old: rec {
          version = "4.4.0.alpha-lj";
          patches = [];
          src = pkgs.fetchFromGitHub {
            owner = "awesomewm";
            repo = "awesome";
            rev = "9ca7bb4";
            sha256 = "sha256-RRpwAIYNLkovXI0y/eXO9uRDqB4qQcXlnYYUCEmx/EA=";
          };
        }))
        .override {lua = pkgs.luajit;};
      pmenu = pkgs.callPackage ./pkgs/pmenu {};
      godot4 = pkgs.callPackage ./pkgs/godot {};
      ansel = pkgs.callPackage ./pkgs/ansel {};
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
        godot4
        doggo
        git-branchless
        emanote
        ansel
        ;
      default = awesome;
    };
    formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
  };
}
