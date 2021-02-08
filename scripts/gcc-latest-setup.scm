(use-modules (gnu packages))

(specifications->manifest
  '("bash"
    "python"
    "python-pip"
    "cmake"
    "ninja"
    "ccache"
    "gcc-toolchain"))
