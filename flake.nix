{
  description = "My home-brew packages";

  inputs.nixpkgs.url = "git+https://github.com/NixOS/nixpkgs?shallow=1&ref=nixos-unstable";
  inputs.llm-agents = {
    url = "github:numtide/llm-agents.nix";
    inputs.nixpkgs.follows = "nixpkgs"; # I don't wanna use the cache
  };
  outputs =
    {
      self,
      nixpkgs,
      llm-agents,
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
        jpegli = pkgs.callPackage ./pkgs/jpgli { };

        eden-emu = pkgs.kdePackages.callPackage ./pkgs/torzu/eden_appimage.nix { };
        wl_shimeji = pkgs.callPackage ./pkgs/wl_shimeji { };
        wayscriber = pkgs.callPackage ./pkgs/wayscriber { };
        pixieditor = pkgs.callPackage ./pkgs/pixieditor/package.nix { };
        kitty = pkgs.callPackage ./pkgs/kitty/package.nix { };

        llama-cpp-vulkan = prev.llama-cpp-vulkan.overrideAttrs (
          final: prev: {
            version = "b9085";
            src = pkgs.fetchFromGitHub {
              owner = "Indras-Mirror";
              repo = "llama.cpp-mtp";
              rev = "e2170c42ebb0fb7719e0ecc268826cd08f492e2b";
              hash = "sha256-bQQ4noE761NzBpxJMzoJD+ejMZUdX/gfmxcf2UaMipw=";
              leaveDotGit = true;
              postFetch = ''
                git -C "$out" rev-parse --short HEAD > $out/COMMIT
                find "$out" -name .git -print0 | xargs -0 rm -rf
              '';
            };
            npmDepsHash = "sha256-k62LIbyY2DXvs7XXbX0lNPiYxuYzeJUyQtS4eA+68f8=";
          }
        );
      };

      packages.x86_64-linux = rec {
        inherit (pkgs)
          pi
          wayscriber
          eden-emu
          glslviewer
          jpegli
          wl_shimeji
          voxtype
          pixieditor
          kitty
          llama-cpp-vulkan
          ;
        default = glslviewer;
      };
      formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
    };
}
