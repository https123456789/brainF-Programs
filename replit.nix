{ pkgs ? import <nixpkgs> {} }: {
    deps = [
        pkgs.haskellPackages.yabi
		pkgs.clang_12
    ];
}