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
      yuzu-bin = pkgs.libsForQt5.callPackage ./pkgs/yuzu-bin {};
      # wasm2luajit = pkgs.callPackage ./pkgs/wasm2luajit {};

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
    #   SDL2 = pkgs.callPackage ./pkgs/SDL2 {
    #       inherit (pkgs.darwin.apple_sdk.frameworks) AudioUnit Cocoa CoreAudio CoreServices ForceFeedback OpenGL;
    #       udevSupport=true;
    # };

      # SDL2 = (prev.SDL2.overrideAttrs (oa: rec { udevSupport = true; }));
      yuzu-ea = (prev.yuzu-ea.overrideAttrs (old: rec {
            version = "2845";
            pname = "yuzu-ea";

        src = pkgs.fetchFromGitHub {
          owner = "pineappleEA";
          repo = "pineapple-src";
          rev = "EA-${version}";
          sha256 = "sha256-+eH0H/cTCpHz6NUncaza4A1o58D4ozFvMBeQGJoct+E=";
          fetchSubmodules = true;
        };
        }));
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
        # yuzu-bin
        ;
      default = yuzu-ea;
    };
    formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
  };
}
