{
  lib,
  rustPlatform,
  fetchFromGitHub,
  nix-update-script,

  git,
  cmake,
  clang,
  pkg-config,
  makeWrapper,
  libclang,

  alsa-lib,
  openssl,
  libnotify,
  pciutils,

  shaderc,
  vulkan-headers,
  vulkan-loader,

  # one of `[ null false "vulkan" ]`
  acceleration ? "vulkan",
}:

assert builtins.elem acceleration [
  null
  false
  "vulkan"
];

let
  vulkanEnabled = acceleration == "vulkan";
in
rustPlatform.buildRustPackage (finalAttrs: {
  pname = "voxtype";
  version = "0.5.6";

  src = fetchFromGitHub {
    owner = "peteonrails";
    repo = "voxtype";
    tag = "v${finalAttrs.version}";
    hash = "sha256-taPmGWRQGIXxWCl4+1KL609LDBDj6HpxIxFrRr5M86E=";
  };

  buildFeatures = lib.optionals vulkanEnabled [ "gpu-vulkan" ];

  cargoHash = "sha256-p6VLVya8yw+a/ZVM4WP4Th8cScVDX1o89A9v+0+5vIQ=";

  nativeBuildInputs = [
    git # Required by whisper.cpp cmake
    cmake
    clang
    pkg-config
    makeWrapper
  ]
  ++ lib.optionals vulkanEnabled [
    shaderc
  ];

  buildInputs = [
    alsa-lib
    openssl
  ]
  ++ lib.optionals vulkanEnabled [
    vulkan-headers
    vulkan-loader
  ];

  LIBCLANG_PATH = "${libclang.lib}/lib";

  postInstall = ''
    wrapProgram $out/bin/voxtype \
      --prefix PATH : ${
        lib.makeBinPath [
          libnotify # Desktop notifications
          pciutils # GPU detection (lspci)
        ]
      }
  '';

  passthru.update-script = nix-update-script { };

  meta = {
    description =
      "Voice-to-text with push-to-talk for Wayland compositors"
      + lib.optionalString vulkanEnabled ", using Vulkan for generic GPU acceleration";
    homepage = "https://voxtype.io";
    downloadPage = "https://voxtype.io/download/";
    changelog = "https://github.com/peteonrails/voxtype/releases/tag/v${finalAttrs.version}";
    license = lib.licenses.mit;
    maintainers = with lib.maintainers; [ DuskyElf ];
    platforms = lib.platforms.linux;
    mainProgram = "voxtype";
  };
})
