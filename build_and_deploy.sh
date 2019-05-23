#!/bin/bash

VER=$1
GROUP=ca.hedlund
ARTIFACT=libjpraat
REPO=phon.ca-release
REPO_URL=https://phon.ca/artifacts/libs-release-local/

MAKEFILE_DEFS=makefile.defs

WIN32X64_FOLDER=win32-x86-64
WIN32AMD64_FOLDER=win32-amd64
MAKEFILE_DEFS_WIN32X64=makefiles/makefile.defs.mingw64.lib

WIN32_TARGET=jpraat.dll
WIN32X64_JAR=libjpraat-win32-x86-64.jar
WIN32AMD64_JAR=libjpraat-win32-amd64.jar

LINUXX64_JAR=libjpraat-linux-x86-64.jar
LINUXAMD64_JAR=libjpraat-linux-amd64.jar
MAKEFILE_DEFS_LINUXX64=makefiles/makefile.defs.linux.silent.lib
LINUX_TARGET=libjpraat.so
LINUXX64_FOLDER=linux-x86-64
LINUXAMD64_FOLDER=linux-amd64

function cleanup {
	if [ -f $MAKEFILE_DEFS ]; then
		make clean
		rm $MAKEFILE_DEFS
	fi
}

cleanup
ln -s $MAKEFILE_DEFS_WIN32X64 makefile.defs
make library

if [ -f $WIN32X64_FOLDER ]; then
	rm -rf $WIN32X64_FOLDER
fi
mkdir $WIN32X64_FOLDER

if [ -f $WIN32AMD64_FOLDER ]; then
	rm -rf $WIN32AMD64_FOLDER
fi
mkdir $WIN32AMD64_FOLDER

if [ -f $WIN32_TARGET ]; then
	cp $WIN32_TARGET $WIN32X64_FOLDER
	jar cvf $WIN32X64_JAR $WIN32X64_FOLDER
	mvn deploy:deploy-file -DrepositoryId=$REPO -Durl=$REPO_URL -DgroupId=$GROUP -DartifactId=$ARTIFACT -Dversion=$VER -Dpackaging=jar -Dclassifier=win32-x86-64 -Dfile=$WIN32X64_JAR	
	
	cp $WIN32_TARGET $WIN32AMD64_FOLDER
	jar cvf $WIN32AMD64_JAR $WIN32AMD64_FOLDER
	mvn deploy:deploy-file -DrepositoryId=$REPO -Durl=$REPO_URL -DgroupId=$GROUP -DartifactId=$ARTIFACT -Dversion=$VER -Dpackaging=jar -Dclassifier=win32-amd64 -Dfile=$WIN32AMD64_JAR
else
	echo "Target for win32-x86-64 not built"
	exit 1
fi

cleanup
ln -s $MAKEFILE_DEFS_LINUXX64 makefile.defs
make library

if [ -f $LINUXX64_FOLDER ]; then
	rm -rf $LINUXX64_FOLDER
fi
mkdir $LINUXX64_FOLDER

if [ -f $LINUXAMD64_FOLDER ]; then
	rm -rf $LINUXAMD64_FOLDER
fi
mkdir $LINUXAMD64_FOLDER

if [ -f $LINUX_TARGET ]; then
	cp $LINUX_TARGET $LINUXX64_FOLDER
	jar cvf $LINUXX64_JAR $LINUXX64_FOLDER
	mvn deploy:deploy-file -DrepositoryId=$REPO -Durl=$REPO_URL -DgroupId=$GROUP -DartifactId=$ARTIFACT -Dversion=$VER -Dpackaging=jar -Dclassifier=linux-x86-64 -Dfile=$LINUXX64_JAR
	
	cp $LINUX_TARGET $LINUXAMD64_FOLDER
	jar cvf $LINUXAMD64_JAR $LINUXAMD64_FOLDER
	mvn deploy:deploy-file -DrepositoryId=$REPO -Durl=$REPO_URL -DgroupId=$GROUP -DartifactId=$ARTIFACT -Dversion=$VER -Dpackaging=jar -Dclassifier=linux-amd64 -Dfile=$LINUXAMD64_JAR
else
	echo "Target for linux-x86-64 not built"
	exit 1
fi

