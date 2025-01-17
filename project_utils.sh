#!/bin/sh

BUILDDIR="build"
CROSSFILE="cross-stm32-bluepill.txt"

usage() {
  printf "./project_utils.sh <option>\n\n"
  printf "  'configure' : Run 'meson build $@'\n"
  printf "  'build'     : Run 'ninja -C build -v'\n"
}

configure() {
  if [ -d $BUILDDIR ]; then
    meson build --cross-file=$CROSSFILE --reconfigure $@
  else
    meson build --cross-file=$CROSSFILE $@
  fi
}

build() {
  ninja -C $BUILDDIR -v
}

if [ "$1"x = "configure"x ]; then
  shift 1
  configure $@
elif [ "$1"x = "build"x ]; then
  shift 1
  build $@
else
  usage
fi
