{
  description = "My home-brew packages";

  inputs.nixpkgs.url = "git+https://github.com/NixOS/nixpkgs?shallow=1&ref=nixos-unstable";
  inputs.llm-agents = {
    url = "git+https://github.com/numtide/llm-agents.nix?shallow=1";
    inputs.nixpkgs.follows = "nixpkgs"; # I don't wanna use the cache
  };

  inputs.calepin = {
    url = "git+https://github.com/vincentarelbundock/calepin?shallow=1";
    flake = false;
  };

  inputs.pytest-language-server = {
    url = "git+https://github.com/bellini666/pytest-language-server?shallow=1";
    flake = false;
  };

  inputs.nimony = {
    url = "git+https://github.com/nim-lang/nimony?shallow=1&submodules=1&rev=034dd8343aed630676a7b06a7bd5416508c2842f";
    flake = false;
  };

  inputs.sokol-tools-bin = {
    url = "git+https://github.com/floooh/sokol-tools-bin?shallow=1&dir=bin/linux";
    flake = false;
  };

  inputs.kcd = {
    url = "git+https://github.com/bethropolis/kcd?shallow=1";
    flake = false;
  };

  inputs.nim2-nimony-lsp = {
    url = "git+https://github.com/leiserfg/nim2-nimony-lsp?shallow=1";
    flake = false;
  };

  # inputs.hyprland = {
  #   url = "git+https://github.com/hyprwm/Hyprland/?shallow=1";
  #   inputs.nixpkgs.follows = "nixpkgs"; # I don't wanna use the cache
  # };

  outputs =
    {
      self,
      nixpkgs,
      llm-agents,
      calepin,
      pytest-language-server,
      nimony,
      sokol-tools-bin,
      kcd,
      nim2-nimony-lsp,
      ...
    }@inputs:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs {
        system = system;
        overlays = [ self.overlays.default ];
      };
    in
    {
      overlays.default = final: prev: {
        # glslviewer = pkgs.callPackage ./pkgs/glslviewer {
        #   inherit (pkgs.darwin.apple_sdk.frameworks) Cocoa;
        # };
        calepin = pkgs.callPackage ./pkgs/calepin { src = calepin; };
        pytest-language-server = pkgs.callPackage ./pkgs/pytest-language-server {
          src = pytest-language-server;
        };
        pi = llm-agents.packages.x86_64-linux.pi;
        # jpegli = pkgs.callPackage ./pkgs/jpgli { };
        # hyprland = inputs.hyprland.packages.x86_64-linux.default;
        eden-emu = pkgs.kdePackages.callPackage ./pkgs/torzu/eden_appimage.nix { };
        nimony = pkgs.callPackage ./pkgs/nimony { src = nimony; };
        sokol-shdc = pkgs.callPackage ./pkgs/sokol-tools { src = sokol-tools-bin; };
        kcd = pkgs.callPackage ./pkgs/kcd { src = kcd; };
        nim2-nimony-lsp = pkgs.callPackage ./pkgs/nim2-nimony-lsp {
          src = nim2-nimony-lsp;
          nimony-src = nimony;
        };
        # wl_shimeji = pkgs.callPackage ./pkgs/wl_shimeji { };
        # wayscriber = pkgs.callPackage ./pkgs/wayscriber { };
        # pixieditor = pkgs.callPackage ./pkgs/pixieditor/package.nix { };
        # kitty = pkgs.callPackage ./pkgs/kitty/package.nix { };
        # open-jai = pkgs.callPackage ./pkgs/open-jai { };
      };

      packages.x86_64-linux = rec {
        inherit (pkgs)
          pi
          # hyprland
          # wayscriber
          eden-emu
          # noctalia_5
          # glslviewer
          calepin
          pytest-language-server
          nimony
          sokol-shdc
          kcd
          nim2-nimony-lsp
          # jpegli
          # wl_shimeji
          # pixieditor
          # kitty
          # open-jai
          ;
        default = nimony;
      };
      formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
    };
}
