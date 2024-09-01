{
  lib,
  # stdenv,
  fetchFromGitHub,
  python312Packages,
  fetchPypi,
  libzim,
}: let
  py-libzim = python312Packages.buildPythonPackage rec {
    pname = "libzim";
    version = "3.4.0";
    nativeBuildInputs = [python312Packages.cython];
    buildInputs = [libzim];
    src = fetchPypi {
      inherit pname version;
      hash = "sha256-w2PenQNA5lfI7IQIihmeGJruriAq2B/84wKChRZCAq8=";
    };
  };
in
  python312Packages.buildPythonApplication rec {
    pname = "pyglossary";
    version = "4.7.0";

    src = fetchPypi {
      inherit version pname;
      # name = "${pname}";
      hash = "sha256-U7/VFe5euwzj5SKWR4TVVucEpQR4HwfdMw6Aqo4RPK4=";
    };

    dependencies = with python312Packages; [
      lxml
      beautifulsoup4
      pyicu
      pyyaml
      marisa-trie
      python-lzo
      html5lib
      # py-libzim
    ];
    postPatch = ''
      sed -i s/cmdclass/_cmd/ setup.py
    '';

    # nativeCheckInputs = with python312Packages; [
    #   mock
    #   pytest7CheckHook
    #   pytest-mock
    # ];

    # disabledTests = lib.optionals stdenv.isDarwin [
    #   "test_settings_defaults"
    #   "test_from_file"
    #   "test_from_env"
    #   "test_settings_from_args"
    #   "test_get_all_executables_exclude_paths"
    #   "test_with_blank_cache"
    #   "test_with_filled_cache"
    #   "test_when_etag_changed"
    #   "test_for_generic_shell"
    #   "test_on_first_run"
    #   "test_on_run_after_other_commands"
    #   "test_when_cant_configure_automatically"
    #   "test_when_already_configured"
    #   "test_when_successfully_configured"
    # ];

    meta = {
      homepage = "https://github.com/nvbn/thefuck";
      description = "Magnificent app which corrects your previous console command";
      license = lib.licenses.mit;
      maintainers = [];
    };
  }
