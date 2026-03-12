{
  description = "My home-brew packages";

  inputs.nixpkgs.url = "git+https://github.com/NixOS/nixpkgs?shallow=1&ref=nixos-unstable";
  # inputs.vicinae.url = "git+https://github.com/vicinaehq/vicinae?shallow=1";
  # inputs.tola = {
  #   url = "github:kawayww/tola";
  #   inputs.nixpkgs.follows = "nixpkgs";
  # };

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

      # suyu-deps = pkgs.kdePackages // {
      #   inherit (self.packages.${system}) nx_tzdb compat-list;
      # };
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
        # material-maker = pkgs.callPackage ./pkgs/material-maker { };
        # pixieditor = pkgs.callPackage ./pkgs/pixieditor/package.nix { };
        # kitty = pkgs.callPackage ./pkgs/kitty/package.nix {
        #   inherit (pkgs.darwin) autoSignDarwinBinariesHook;
        # };
      };

      packages.x86_64-linux = rec {
        inherit (pkgs)
          pi
          wayscriber
          # friction-graphics
          # material-maker
          eden-emu
          glslviewer
          # torzu
          # nx_tzdb
          # compat-list
          # pyglossary
          jpegli
          # pixieditor
          wl_shimeji
          voxtype
          # tola
          ;
        default = glslviewer;
      };
      formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
    };
}
