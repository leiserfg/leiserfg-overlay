{
  nodejs,
  stdenv,
  fetchzip,
}:
stdenv.mkDerivation rec {
  name = "basedpyright";
  version = "1.6.0";
  src = fetchzip {
    url = "https://github.com/DetachHead/basedpyright/releases/download/v${version}/basedpyright-${version}.tar.gz";
    hash = "sha256-nuQgtjZSjPeVS1LESN+1Q7cqTX2MjW/cuh3Azvt58Lg=";
  };
  buildNativeInpute = [nodejs];
  preInstall = ''
    mkdir -p $out/{shared,bin}/
    mv  basedpyright/ $out/shared/basedpyright
    chmod +x  $out/shared/basedpyright/*.js
    ln -s $out/shared/basedpyright/langserver.index.js $out/bin/basedpyright-langserver
    ln -s $out/shared/basedpyright/index.js $out/bin/basedpyright

    # replace shebang
    substituteInPlace $out/shared/basedpyright/index.js \
        --replace '/usr/bin/env node' ${nodejs}/bin/node

    substituteInPlace $out/shared/basedpyright/langserver.index.js \
        --replace '/usr/bin/env node' ${nodejs}/bin/node
  '';
}
