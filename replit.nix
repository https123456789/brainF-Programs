{ pkgs ? import <nixpkgs> {} }: {
    deps = [
        pkgs.haskellPackages.yabi
		pkgs.clang_12
		pkgs.python39Full
		pkgs.python39Packages.pip
    ];
}