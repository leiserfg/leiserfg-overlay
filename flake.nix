{
  description = "My home-brew packages";

  inputs.nixpkgs.url = "git+https://github.com/NixOS/nixpkgs?shallow=1&ref=nixos-unstable";
  inputs.llm-agents = {
    url = "git+https://github.com/numtide/llm-agents.nix?shallow=1";
    inputs.nixpkgs.follows = "nixpkgs"; # I don't wanna use the cache
  };

  inputs.noctalia = {
    url = "git+https://github.com/noctalia-dev/noctalia?shallow=1";
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
    url = "git+https://github.com/nim-lang/nimony?shallow=1";
    flake = false;
  };

  inputs.hyprland = {
    url = "github:hyprwm/Hyprland/v0.56.0";
    inputs.nixpkgs.follows = "nixpkgs"; # I don't wanna use the cache
  };

  outputs =
    {
      self,
      nixpkgs,
      llm-agents,
      noctalia,
      calepin,
      pytest-language-server,
      nimony,
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
        glslviewer = pkgs.callPackage ./pkgs/glslviewer {
          inherit (pkgs.darwin.apple_sdk.frameworks) Cocoa;
        };
        calepin = pkgs.callPackage ./pkgs/calepin { src = calepin; };
        pytest-language-server = pkgs.callPackage ./pkgs/pytest-language-server {
          src = pytest-language-server;
        };
        pi = llm-agents.packages.x86_64-linux.pi;
        noctalia_5 = noctalia.packages.x86_64-linux.default;
        # jpegli = pkgs.callPackage ./pkgs/jpgli { };
        hyprland = inputs.hyprland.packages.x86_64-linux.default;
        eden-emu = pkgs.kdePackages.callPackage ./pkgs/torzu/eden_appimage.nix { };
        nimony = pkgs.callPackage ./pkgs/nimony { src = nimony; };
        # wl_shimeji = pkgs.callPackage ./pkgs/wl_shimeji { };
        # wayscriber = pkgs.callPackage ./pkgs/wayscriber { };
        # pixieditor = pkgs.callPackage ./pkgs/pixieditor/package.nix { };
        # kitty = pkgs.callPackage ./pkgs/kitty/package.nix { };
        # open-jai = pkgs.callPackage ./pkgs/open-jai { };
      };

      packages.x86_64-linux = rec {
        inherit (pkgs)
          pi
          hyprland
          # wayscriber
          eden-emu
          noctalia_5
          glslviewer
          calepin
          pytest-language-server
          nimony
          # jpegli
          # wl_shimeji
          # pixieditor
          # kitty
          # open-jai
          ;
        default = glslviewer;
      };
      formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
    };
}
