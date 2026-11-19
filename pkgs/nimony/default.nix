{
  stdenv,
  lib,
  nim,
  src,
}:
stdenv.mkDerivation {
  pname = "nimony";
  version = "0.6.0";

  inherit src;

  nativeBuildInputs = [ nim ];

  configurePhase = ":";

  env.HOME = "/tmp";
  env.XDG_CACHE_HOME = "/tmp/.cache";

  postPatch = ''
    substituteInPlace src/nimony/deps.nim \
      --replace-fail 'result = root / "stdcache" / bin / uhashBase36(b.extract())' \
        'result = getCacheDir("nimony") / "stdlib" / uhashBase36(root) / bin / uhashBase36(b.extract())'
  '';

  buildPhase = ''
    cp ${./parser.nim} src/nifler/nimparser/parser.nim

    nim c -r  -d:release src/hastur/hastur build all
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp -r bin/* $out/bin/
    mkdir -p $out/lib
    cp -r lib/* $out/lib/
  '';

  meta = with lib; {
    description = "A new Nim implementation in heavy development";
    homepage = "https://github.com/nim-lang/nimony";
    license = licenses.mit;
    platforms = platforms.unix;
  };
}
