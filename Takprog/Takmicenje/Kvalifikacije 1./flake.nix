{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-22.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import (builtins.fetchGit {
          #takmicenje preporucuje 5.1, ovo je dovoljno blizu
          name = "gcc-5.4";
          url = "https://github.com/NixOS/nixpkgs/";
          ref = "refs/heads/nixpkgs-unstable";
          rev = "473b58f20e491312a03c9c1578c89116e39a1d50";
        }) { };

        myPkg = pkgs.gcc-unwrapped-5;
      in

      {
        devShell = pkgs.mkShell {
          buildInputs = with pkgs; [
            myPkg
            cmake
            cmakeWithGui
            cudaPackages_11_2.cudatoolkit
          ];
        };
      }
    );
}
