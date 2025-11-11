{
  pkgs,
  lib,
  config,
  inputs,
  ...
}:

{
  packages = with pkgs; [
    bison
    cmake
    flex
    gcc
    just
    ninja
  ];

  languages.python = {
    enable = true;
    venv = {
      enable = true;
      requirements = ''
        iniconfig==2.3.0
        packaging==25.0
        pluggy==1.6.0
        pygments==2.19.2
        pytest==9.0.0
      '';
    };
  };

  env.LD_LIBRARY_PATH = lib.makeLibraryPath [
    pkgs.flex
  ];
}
