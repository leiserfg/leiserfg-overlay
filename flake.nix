{
    description = "My home brew packages";
    inputs.nixpkgs.url = "nixpkgs/nixos-22.05";

    outputs = { self, nixpkgs }: {
        let  pkgs = import nixpkgs {
            system = "x86_64-linux";
            overlays = [ self.overlays.default ];
        };

        in {
            overlays.default = final: prev: {
                packages.x86_64-linux = rec {
                    inherit (pkgs)

                };
            };
        };
    };
}
