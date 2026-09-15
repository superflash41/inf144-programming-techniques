{
  description = "inf144 env";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};
    in {
      devShells.default = pkgs.mkShell {
        buildInputs = [
          pkgs.gcc15
          pkgs.gnumake
        ];

        shellHook = ''
                    alias g++='g++-15 -std=c++23 -Wall -Wextra -O2'

                    cat > .clangd << EOF
          CompileFlags:
            Add:
              - -std=c++23
              - -Wall
              - -Wextra
              - --gcc-toolchain=${pkgs.gcc15}
            Remove:
              - -xc++
          EOF
        '';
      };
    });
}
