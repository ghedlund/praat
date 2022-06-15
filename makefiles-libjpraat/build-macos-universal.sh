#!/bin/sh

## Build macos universal binary for x86_64 and arm64

JPRAAT_MAKEFILE=Makefile-libjpraat
MAC_MAKEFILE=makefiles-libjpraat/Makefile-mac
MAKEFILE_DEFS=makefile.defs

TARGET_FOLDER=./target
X64_MAKEFILE=makefiles-libjpraat/makefile.defs.macos.x64
X64_TARGET=libjpraat-x86_64-apple-macos10.12.dylib

ARM64_MAKEFILE=makefiles-libjpraat/makefile.defs.macos.arm64
ARM64_TARGET=libjpraat-arm64-apple-macos11.dylib

UNIVERSAL_TARGET=libjpraat.dylib

if [ ! -d "${TARGET_FOLDER}" ]; then
  mkdir ${TARGET_FOLDER}
fi

if [ -f "${JPRAAT_MAKEFILE}" ]; then
  make -f ${JPRAAT_MAKEFILE} clean
  rm ${JPRAAT_MAKEFILE}
fi

## x86_64
if [ ! -f "${TARGET_FOLDER}/${X64_TARGET}" ]; then
  echo "Target: ${X64_TARGET}"
  echo "${MAKEFILE_DEFS}: ${X64_MAKEFILE}"

  ln -s ${MAC_MAKEFILE} ${JPRAAT_MAKEFILE}
  ln -sf ${X64_MAKEFILE} ${MAKEFILE_DEFS}
  make -f ${JPRAAT_MAKEFILE} -j12

  if [ ! -f "${X64_TARGET}" ]; then
    echo "Failed to create ${X64_TARGET}, aborting"
    exit 1
  fi
  mv ${X64_TARGET} ${TARGET_FOLDER}/
fi

## arm64
if [ ! -f "${TARGET_FOLDER}/${ARM64_TARGET}" ]; then
  echo "Target: ${ARM64_TARGET}"
  echo "${MAKEFILE_DEFS}: ${ARM64_MAKEFILE}"

  ln -sf ${ARM64_MAKEFILE} ${MAKEFILE_DEFS}
  make -f ${JPRAAT_MAKEFILE} clean
  make -f ${JPRAAT_MAKEFILE} -j12

  if [ ! -f "${ARM64_TARGET}" ]; then
    echo "Failed to create ${ARM64_TARGET}, aborting"
    exit 1
  fi
  mv ${ARM64_TARGET} ${TARGET_FOLDER}/
fi

## lipo
if [ ! -f "${TARGET_FOLDER}/${UNIVERSAL_TARGET}" ]; then
  echo "Creating universal binary ${TARGET_FOLDER}/${UNIVERSAL_TARGET}"
  lipo -create -output ${TARGET_FOLDER}/${UNIVERSAL_TARGET} ${TARGET_FOLDER}/${X64_TARGET} ${TARGET_FOLDER}/${ARM64_TARGET}
else
  echo "Nothing to do, exiting"
fi
