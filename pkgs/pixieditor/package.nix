{
  lib,
  replaceVars,

  dotnetCorePackages,
  buildDotnetModule,
  buildDotnetGlobalTool,

  fetchFromGitHub,
  # fetchzip,

  ffmpeg-headless,

  vulkan-loader,
  libGL,
  xorg,
  openssl,

  makeDesktopItem,
  copyDesktopItems,
}:
let
  protogen = buildDotnetGlobalTool {
    pname = "protogen";
    nugetName = "protobuf-net.Protogen";
    version = "3.2.42";
    nugetSha256 = "sha256-ADAkEfgzA7Po/pkV6wp7f7oyB8yvnJfOs7UriUDTgdc=";
  };
  # wasi-sdk-bin = fetchzip {
  #   url = "https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-25/wasi-sdk-25.0-x86_64-linux.tar.gz";
  #   hash = "sha256-tKuGRXljb6mDZjG20NsmrL01A04uCWOCYn1njfLw53Y=";
  # };
in
buildDotnetModule (finalAttrs: {
  pname = "pixieditor";
  version = "2.0.1.2";

  src = fetchFromGitHub {
    owner = "PixiEditor";
    repo = "PixiEditor";
    tag = finalAttrs.version;
    hash = "sha256-o23fUqwca+rmQUuktC9H8gwyeds/7tp2tcyD0axboAA=";
    fetchSubmodules = true;
  };

  patches = [
    ./patches/0000-fix-protogen.patch
    ./patches/0001-fix-nix-bin-path.patch
    ./patches/0002-set-build-id.patch
    (replaceVars ./patches/0003-use-sys-ffmpeg.patch {
      binaryPath = "${ffmpeg-headless}/bin";
    })
  ];
  postPatch = ''
    # ./patches/0001-fix-nix-bin-path.patch
    substituteInPlace ./src/PixiEditor/Models/ExceptionHandling/CrashReport.cs \
      --replace-fail '@NIX_BIN_PATH@' '${placeholder "out"}/bin/pixieditor';
  '';

  nativeBuildInputs = [
    protogen
    copyDesktopItems
  ];

  dotnet-sdk = dotnetCorePackages.sdk_8_0;
  dotnet-runtime = dotnetCorePackages.runtime_8_0;

  nugetDeps = ./deps.json;

  buildType = "ReleaseNoUpdate";
  projectFile = [
    "src/PixiEditor.Desktop/PixiEditor.Desktop.csproj"
    "src/PixiEditor.Linux/PixiEditor.Linux.csproj"
    "src/PixiEditor/PixiEditor.csproj"
  ];
  executables = [ "PixiEditor.Desktop" ];
  runtimeIdentifier = "linux-x64";

  runtimeDeps = [
    vulkan-loader
    libGL
    xorg.libX11
    xorg.libICE
    xorg.libSM
    xorg.libXi
    xorg.libXcursor
    xorg.libXext
    xorg.libXrandr
    openssl
  ];

  # WASI_SDK_PATH = "${wasi-sdk-bin}";

  desktopItems = [
    (makeDesktopItem {
      name = "pixieditor";
      type = "Application";
      desktopName = "PixiEditor";
      genericName = "2D Editor";
      comment = finalAttrs.meta.description;
      icon = "pixieditor";
      exec = "pixieditor %f";
      tryExec = "pixieditor";
      startupWMClass = "pixieditor";
      terminal = false;
      categories = [
        "Graphics"
        "2DGraphics"
        "RasterGraphics"
        "VectorGraphics"
      ];
      keywords = [
        "editor"
        "image"
        "2d"
        "graphics"
        "design"
        "vector"
        "raster"
      ];
      mimeTypes = [
        "application/x-pixieditor"
      ];
      extraConfig.SingleMainWindow = "true";
    })
  ];

  postInstall = ''
    # install mime type info
    install -Dm644 ${./resources/mimeinfo.xml} $out/share/mime/packages/pixieditor.xml

    mkdir -p $out/share/icons/hicolor/scalable/apps
    install -Dm644 ${./resources/pixieditor.svg} $out/share/icons/hicolor/scalable/apps/pixieditor.svg
  '';

  postFixup = ''
    # rename main executable to pixieditor
    mv $out/bin/PixiEditor.Desktop $out/bin/pixieditor
  '';

  meta = {
    description = "Universal editor for all your 2D needs";
    longDescription = ''
      PixiEditor is a universal 2D platform that aims to provide you with tools and features for all your 2D needs.
      Create beautiful sprites for your games, animations, edit images, create logos. All packed in an eye-friendly dark theme
    '';
    homepage = "https://pixieditor.com";
    changelog = "https://github.com/PixiEditor/PixiEditor/releases/tag/${finalAttrs.version}";
    mainProgram = "pixieditor";
    license = lib.licenses.lgpl3Only;
    maintainers = with lib.maintainers; [
      griffi-gh
    ];
    platforms = lib.platforms.linux;
  };
})
