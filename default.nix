{
  lib,
  stdenv,
  boost,
  cmake,
  jrl-cmakemodules,
  tinyxml-2,
}:

stdenv.mkDerivation {
  pname = "hpp-util";
  version = "5.0.0";

  src = lib.fileset.toSource {
    root = ./.;
    fileset = lib.fileset.unions [
      ./CMakeLists.txt
      ./doc
      ./include
      ./package.xml
      ./src
      ./tests
    ];
  };

  prePatch = ''
    substituteInPlace tests/run_debug.sh.in \
      --replace-fail /bin/bash ${stdenv.shell}
  '';

  strictDeps = true;

  nativeBuildInputs = [ cmake ];
  propagatedBuildInputs = [
    boost
    jrl-cmakemodules
    tinyxml-2
  ];

  doCheck = true;

  meta = {
    description = "Debugging tools for the HPP project";
    homepage = "https://github.com/humanoid-path-planner/hpp-util";
    license = lib.licenses.bsd2;
    maintainers = [ lib.maintainers.nim65s ];
  };
}
