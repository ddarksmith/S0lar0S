#!/bin/bash
# S0lar0S live-build script -- © WTFPL
# cfg ------------------------------------------------------------------
VERSION="S0lar0S-18"
# root -----------------------------------------------------------------
if [ `whoami` != root ]; then echo "build needs root" && exit 1; fi
# args & help ----------------------------------------------------------
if [ "$1" == "32" ]; then ARCH="i386"
elif [ "$1" == "64" ]; then ARCH="amd64"
elif [ "$1" == "clean" ]; then lb clean && rm -R -f cache && exit 0
else
    # no args or wrong args > help
    echo "Usage: as root"
    echo "build.sh 32    > build S0lar0S i386"
    echo "build.sh 64    > build S0lar0S amd64"
    echo "build.sh clean > clean up cache directories"
    echo "---"
    echo "make sure to clean directory before cross-arch building"
    exit 1
fi
# build ISO ------------------------------------------------------------
echo "INFO: building ${VERSION}-${ARCH}"
if [ "$ARCH" == "i386" ]; then 
    lb config -a ${ARCH} -k "686" --bootloader "syslinux"; lb build; fi
if [ "$ARCH" == "amd64" ]; then
    lb config -a ${ARCH} --bootloader "syslinux,grub-efi"; lb build; fi
# name -----------------------------------------------------------------
echo "INFO: renommer"
if test -f live-image-${ARCH}.hybrid.iso; then
    mkdir -p S0lar0S-${ARCH}
    mv live-image-${ARCH}.hybrid.iso S0lar0S-${ARCH}/${VERSION}-${ARCH}.iso
    mv chroot.packages.install S0lar0S-${ARCH}/${VERSION}-${ARCH}.pkgs
    mv ${VERSION}.log S0lar0S-${ARCH}/${VERSION}-${ARCH}.log
    cd S0lar0S-${ARCH} && md5sum ${VERSION}-${ARCH}.iso > ${VERSION}-${ARCH}.md5
    cd ../
else
    echo "ISO not builded ... check your log file !" && exit 1
fi
# clean ----------------------------------------------------------------
echo "INFO: nettoyage"
lb clean && exit 0
# eof ------------------------------------------------------------------
