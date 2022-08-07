{ lib, fetchurl, symlinkJoin,  j, stdenv }:
let
javx = (
        j.override (old: rec {
            avxSupport = true;
            })
       ).overrideAttrs (old: rec {
           installPhase = ''
           runHook preInstall
           mkdir -p "$out/share/j/"
           cp -r $JLIB/{addons,system} "$out"
           cp -r $JLIB/bin "$out"
           runHook postInstall
           '';
           });
       j_version =  builtins.head (lib.splitString "-" javx.version);
       jaddon = ({ name, version, sha256}: stdenv.mkDerivation {
            pname = "j-addon-${name}";
            version = version;
            src = fetchurl {
                url = "http://www.jsoftware.com/jal/j${j_version}/addons/${name}_${version}_linux.tar.gz";
                sha256 = sha256;
            };
                configurePhase = "";
                buildPhase = "";
                preInstall = "";
                postInstall = "";
                installPhase = ''
                runHook preInstall

                target=$out/addons/$(basename $PWD)
                mkdir -p $target
                cp -r ./ $target

                runHook postInstall
                '';
           });
in
symlinkJoin {
    name = "j-with-addons";
    version = javx.version;
    paths = [
        javx
    ] ++ builtins.map jaddon [
        { name = "graphics_plot";
          sha256 = "sha256-+OuGmsov+m3WL9d4INV1Xm5Cg33R/5m7M9vU/VUjEmc=";
          version = "1.0.195";
        }
    ];
}
