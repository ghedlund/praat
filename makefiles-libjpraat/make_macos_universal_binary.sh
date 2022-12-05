#!/bin/sh

X64_MAKEFILE="makefiles-libjpraat/makefile.defs.macos.x64"
ARM64_MAKEFILE="makefiles-libjpraat/makefile.defs.macos.arm64"
MAKEFILE_DEFS="makefile.defs"
MAKEFILE="makefiles-libjpraat/Makefile-mac"

X64_TARGET="x86_64-apple-macos10.12"
ARM64_TARGET="arm64-apple-macos11"
LIBNAME="jpraat"

TARGET_FOLDER="./darwin"
X64_LIB="lib${LIBNAME}-${X64_TARGET}.dylib"
ARM64_LIB="lib${LIBNAME}-${ARM64_TARGET}.dylib"
UNIVERSAL_TARGET="${TARGET_FOLDER}/lib${LIBNAME}.dylib"

MAKE_OPTS="-j12"

PRAAT_VERSION=$(grep PRAAT_VERSION_STR sys/praat_version.h | awk -F ' ' '{print $3}')
JAR="libjpraat-${PRAAT_VERSION}.jar"

echo "********************************"
echo "Building ${UNIVERSAL_TARGET}"
echo "Version: ${PRAAT_VERSION}"
echo "********************************"
echo ""

# compile
echo "Compile x86_64 target..."
ln -sf "${X64_MAKEFILE}" "${MAKEFILE_DEFS}"
make -f "${MAKEFILE}" clean
make -f "${MAKEFILE}" "${MAKE_OPTS}"

echo "Compile arm64 target..."
ln -sf "${ARM64_MAKEFILE}" "${MAKEFILE_DEFS}"
make -f "${MAKEFILE}" clean
make -f "${MAKEFILE}" "${MAKE_OPTS}"

# make universal binary
echo "Make universal binary"
mkdir -p "${TARGET_FOLDER}"
lipo -create -output "${UNIVERSAL_TARGET}" "${X64_LIB}" "${ARM64_LIB}"

# create jar
jar cvf "${JAR}" "${TARGET_FOLDER}"
