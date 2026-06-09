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

  outputs =
    {
      self,
      nixpkgs,
      llm-agents,
      noctalia,
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
        pi = llm-agents.packages.x86_64-linux.pi;
        noctalia_5 = noctalia.packages.x86_64-linux.default;
        # jpegli = pkgs.callPackage ./pkgs/jpgli { };

        eden-emu = pkgs.kdePackages.callPackage ./pkgs/torzu/eden_appimage.nix { };
        wl_shimeji = pkgs.callPackage ./pkgs/wl_shimeji { };
        wayscriber = pkgs.callPackage ./pkgs/wayscriber { };
        pixieditor = pkgs.callPackage ./pkgs/pixieditor/package.nix { };
        kitty = pkgs.callPackage ./pkgs/kitty/package.nix { };
        # open-jai = pkgs.callPackage ./pkgs/open-jai { };
      };

      packages.x86_64-linux = rec {
        inherit (pkgs)
          pi
          wayscriber
          eden-emu
          noctalia_5
          glslviewer
          # jpegli
          wl_shimeji
          voxtype
          pixieditor
          kitty
          # open-jai
          ;
        default = glslviewer;
      };
      formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
    };
}
