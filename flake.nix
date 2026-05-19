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
        # jpegli = pkgs.callPackage ./pkgs/jpgli { };

        eden-emu = pkgs.kdePackages.callPackage ./pkgs/torzu/eden_appimage.nix { };
        wl_shimeji = pkgs.callPackage ./pkgs/wl_shimeji { };
        wayscriber = pkgs.callPackage ./pkgs/wayscriber { };
        pixieditor = pkgs.callPackage ./pkgs/pixieditor/package.nix { };
        kitty = pkgs.callPackage ./pkgs/kitty/package.nix { };
        open-jai = pkgs.callPackage ./pkgs/open-jai { };

        llama-cpp-vulkan = prev.llama-cpp-vulkan.overrideAttrs (
          final: prev: {
            version = "9222";
            src = pkgs.fetchFromGitHub {
              owner = "ggml-org";
              repo = "llama.cpp";
              tag = "b${final.version}";
              hash = "sha256-Ws0a2qkgTFoeUuzg6tKbY6PfDP+0/9D9DTx21fLoFak=";
              leaveDotGit = true;
              postFetch = ''
                git -C "$out" rev-parse --short HEAD > $out/COMMIT
                find "$out" -name .git -print0 | xargs -0 rm -rf
              '';
            };
            cmakeFlags = [
              (pkgs.lib.cmakeBool "GGML_CPU_ALL_VARIANTS" true)
              (pkgs.lib.cmakeBool "GGML_BACKEND_DL" true)
            ]
            ++ prev.cmakeFlags;
            npmDepsHash = "sha256-Po5SWJv3vmcBR7y62G9/CfvI3Lk/MYdjFMTTy2dsgoY=";
            npmRoot = "tools/ui";
          }
        );
      };

      packages.x86_64-linux = rec {
        inherit (pkgs)
          pi
          wayscriber
          eden-emu
          glslviewer
          # jpegli
          wl_shimeji
          voxtype
          pixieditor
          kitty
          llama-cpp-vulkan
          open-jai
          ;
        default = glslviewer;
      };
      formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
    };
}
