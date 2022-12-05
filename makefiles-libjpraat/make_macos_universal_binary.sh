#!/bin/sh

X64_MAKEFILE="makefiles-libjpraat/makefile.defs.macos.x64"
ARM64_MAKEFILE="makefiles-libjpraat/makefile.defs.macos.arm64"
MAKEFILE_DEFS="makefile.defs"
MAKEFILE="makefiles-libjpraat/Makefile-macos"

X64_TARGET="x86_64-apple-macos10.12"
ARM64_TARGET="arm64-apple-macos11"
LIBNAME="jpraat"

TARGET_FOLDER="./target"
X64_LIB="${TARGET_FOLDER}/${X64_TARGET}/objects/lib${LIBNAME}-${X64_TARGET}.jnilib"
ARM64_LIB="${TARGET_FOLDER}/${ARM64_TARGET}/objects/lib${LIBNAME}-${ARM64_TARGET}.jnilib"
UNIVERSAL_TARGET_FOLDER="${TARGET_FOLDER}/universal"
UNIVERSAL_TARGET="${UNIVERSAL_TARGET_FOLDER}/lib${LIBNAME}.jnilib"
INSTALL_FOLDER="./darwin"

MAKE_OPTS="-j12"

# compile
echo "Compile x86_64 target"
ln -sf "${X64_MAKEFILE}" "${MAKEFILE_DEFS}"
make -f "${MAKEFILE}" clean
make -f "${MAKEFILE}" "${MAKE_OPTS}"

echo "Compile arm64 target"
ln -sf "${ARM64_MAKEFILE}" "${MAKEFILE_DEFS}"
make -f "${MAKEFILE}" clean
make -f "${MAKEFILE}" "${MAKE_OPTS}"

# make universal binary
echo "Make universal binary"

mkdir -p "${UNIVERSAL_TARGET_FOLDER}"
lipo -create -output "${UNIVERSAL_TARGET}" "${X64_LIB}" "${ARM64_LIB}"

# install (optional)
if [ "-install" = "$1" ]; then
  echo "Install universal binary to resources folder"
  cp "${UNIVERSAL_TARGET}" "${INSTALL_FOLDER}"
fi
