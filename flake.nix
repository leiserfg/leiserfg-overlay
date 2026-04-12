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
          ;
        default = glslviewer;
      };
      formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
    };
}
