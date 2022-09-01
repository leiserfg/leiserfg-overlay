{
  description = "My home-brew packages";
  inputs.nixpkgs.url = "nixpkgs/nixos-unstable";
  inputs.nix-gaming.url = github:fufexan/nix-gaming;
  outputs = {
    self,
    nixpkgs,
    nix-gaming,
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
      yuzu-ea = prev.yuzu-ea;
      wasm2luajit = pkgs.callPackage ./pkgs/wasm2luajit {};
      xmake = pkgs.callPackage ./pkgs/xmake {};
      doggo = pkgs.callPackage ./pkgs/doggo {};
      sdl-jstest = prev.sdl-jstest.override (
        old: rec {
          SDL2 = prev.SDL2.override {udevSupport = true;};
        }
      );

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

      fzf = pkgs.callPackage ./pkgs/fzf {};
      controllermap = pkgs.callPackage ./pkgs/controllermap {};
      antimicrox =
        (
          prev.antimicrox.override (old: rec {
            SDL2 = prev.SDL2.override {udevSupport = true;};
          })
        )
        .overrideAttrs (old: rec {
          version = "3.2.5";

          src = pkgs.fetchFromGitHub {
            owner = "AntiMicroX";
            repo = old.pname;
            rev = version;
            sha256 = "sha256-Lc23VvIZguE6nRHeGDW3pL4exKtJtF8XmFkN2SxUL0g=";
          };
        });
      # cemu-emu = pkgs.callPackage ./pkgs/cemu-wip {};

      # javx = (
      #   prev.j.override (old: rec {
      #       avxSupport = true;
      #   })
      # ).overrideAttrs (old: rec {
      #       installPhase = ''
      #           runHook preInstall
      #           mkdir -p "$out/share/j/"
      #           cp -r $JLIB/{addons,system} "$out"
      #           cp -r $JLIB/bin "$out"
      #           runHook postInstall
      #         '';
      # });
      javx = pkgs.callPackage ./pkgs/j-with-addons {};
      godot = pkgs.callPackage ./pkgs/godot {};
      # zoxide = pkgs.zoxide;
      # wineStagingFull = pkgs.wineWowPackages.stagingFull;
      # wineStaging = pkgs.wineWowPackages.staging;
      darktable4 = pkgs.darktable;
    };

    packages.x86_64-linux = rec {
      inherit
        (pkgs)
        cemu-emu
        antimicrox
        # armourpaint
        
        zoxide
        darktable4
        glslviewer
        nsxiv-extras
        material-maker
        dwarfs
        awesome
        wasm2luajit
        godot
        fzf
        yuzu-ea
        sdl-jstest
        xmake
        javx
        controllermap
        doggo
        # wineStaging
        
        zint
        ;
      default = yuzu-ea;
    };
    formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
  };
}
