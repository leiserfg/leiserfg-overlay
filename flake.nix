{
  description = "My home-brew packages";

  inputs.nixpkgs.url = "git+https://github.com/NixOS/nixpkgs?shallow=1&ref=nixos-unstable";
  inputs.vicinae.url = "git+https://github.com/vicinaehq/vicinae?shallow=1";
  inputs.vicinae.inputs.nixpkgs.follows = "nixpkgs";
  inputs.tola = {
    url = "github:kawayww/tola";
    inputs.nixpkgs.follows = "nixpkgs";
  };

  outputs =
    {
      self,
      nixpkgs,
      vicinae,
      tola,
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
        vicinae = vicinae.packages.x86_64-linux.default;
        tola = tola.packages.x86_64-linux.default;
        jpegli = pkgs.callPackage ./pkgs/jpgli { };
        # nx_tzdb = pkgs.callPackage ./pkgs/torzu/nx_tzdb.nix { };
        # compat-list = pkgs.callPackage ./pkgs/torzu/compat-list.nix { };
        # torzu = pkgs.callPackage ./pkgs/torzu/torzu.nix { };

        # eden-emu = pkgs.callPackage ./pkgs/torzu/eden.nix suyu-deps; # WIP
        eden-emu = pkgs.kdePackages.callPackage ./pkgs/torzu/eden_appimage.nix { };
        # pyglossary = pkgs.callPackage ./pkgs/pyglossary { };
        # friction-graphics = pkgs.libsForQt5.callPackage ./pkgs/friction-graphics/friction_appimagen.nix { };
        # friction-graphics = pkgs.callPackage ./pkgs/friction-graphics { };
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
          # kitty
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
          vicinae
          tola
          ;
        default = glslviewer;
      };
      formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.alejandra;
    };
}
