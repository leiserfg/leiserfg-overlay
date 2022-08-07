{ lib, fetchurl, symlinkJoin,  j, stdenv }:
let
       j_version =  builtins.head (lib.splitString "-" j.version);

       javx = ( j.override (old: rec {
            avxSupport = true;
            })
       ).overrideAttrs (old: rec {
           passAsFile = ["jaddons"];
           installPhase = ''
           runHook preInstall
           mkdir -p "$out/share/j/"
           cp -r $JLIB/{addons,system} "$out"
           cp -r $JLIB/bin "$out"
           '';
        });

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

        { name = "graphics_afm";
          sha256 = "sha256-JXtoYPU0nNCODpZjr+vcze4hX+zUdYzmYwerZRBBs14=";
          version = "1.0.15";
        }

        { name = "graphics_color";
          sha256 = "sha256-PWQpdWHFZI/cUm6ncmoaTSKT2oPw+zCTYmkyWMsj8og=";
          version = "1.0.19";
        }

        { name = "graphics_bmp";
          sha256 = "sha256-5oSthbDtiUpTqoO5Ei/zAOaDF9W8LytYSECWrk3TXKs=";
          version = "1.0.14";
        }

        { name = "graphics_png";
          sha256 = "sha256-sHBLK7MRo/r4JvV4YHH9+RPId/WHclZC/uA14+DvpK0=";
          version = "1.0.28";
        }

        { name = "arc_zlib";
          sha256 = "sha256-lO4NAdgGHrA4AwvnuruQnXDe4EundRRjAA51hpUdWw0=";
          version = "1.0.10";
        }

        { name = "general_misc";
          version = "2.5.3";
          sha256 = "sha256-McMpt1G3CUTT9Xp+lhlSYO2N6gQBzpi5SZDXEIP8KDo=";
        }
        { name = "math_misc";
          version = "1.2.6";
          sha256 = "sha256-ZykdC/vlKZB/kDvG9VxxmrG6+h3jNbwuWDSAoMk5yWg=";
        }

    ];
    postBuild = ''
    #  We can't just link because  jconsole looks for the path of the binary 
    rm $out/bin/jconsole
    cp -L $(readlink -f ${javx}/bin/jconsole) $out/bin/jconsole
    '';
}
