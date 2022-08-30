#!/bin/bash

src=src/*.c
cc=gcc
name=libphoton

flags=(
    -std=c99
    -Wall
    -Wextra
    -O2
)

inc=(
    -I.
    -Iinclude
)

lib=(
    -Llib
    -lfract
)

exe() {
    echo "$@" && $@
}

build() {
    [ ! -d lib ] && mkdir lib
    pushd fract/ && ./build.sh static && popd && mv fract/libfract.a lib/libfract.a
}

shared() {
    if echo "$OSTYPE" | grep -q "darwin"; then
        exe $cc ${flags[*]} ${inc[*]} ${lib[*]} -dynamiclib $src -o $name.dylib
    elif echo "$OSTYPE" | grep -q "linux"; then
        exe $cc -shared ${flags[*]} ${inc[*]} ${lib[*]} -lm -fPIC $src -o $name.so
    else
        echo "This OS is not supported yet..." && exit
    fi
}

static() {
    exe $cc ${flags[*]} ${inc[*]} -c $src && ar -cr $name.a *.o && rm *.o
}

cleand() {
    [ -d $1 ] && rm -r $1 && echo "deleted $1"
}

cleanf() {
    [ -f $1 ] && rm $1 && echo "deleted $1"
}

clean() {
    cleand lib
    cleanf $name.so
    cleanf $name.dylib
    cleanf $name.a
    return 0
}

install() {
    [ "$EUID" -ne 0 ] && echo "Run with sudo to install." && exit

    build && shared && static
    cp photon.h /usr/local/include/

    [ -f $name.a ] && mv $name.a /usr/local/lib/
    [ -f $name.so ] && mv $name.so /usr/local/lib/
    [ -f $name.dylib ] && mv $name.dylib /usr/local/lib/

    echo "Successfully installed $name."
    return 0
}

uninstall() {
    [ "$EUID" -ne 0 ] && echo "Run with sudo to uninstall." && exit

    cleanf /usr/local/include/photon.h
    cleanf /usr/local/lib/$name.a
    cleanf /usr/local/lib/$name.so
    cleanf /usr/local/lib/$name.dylib

    echo "Successfully uninstalled $name."
    return 0
}

case "$1" in
    "shared")
        build && shared;;
    "static")
        static;;
    "build")
        build;;
    "install")
        install;;
    "uninstall")
        uninstall;;
    "clean")
        clean;;
    *)
        echo "Run with 'shared' ot 'static' to build."
        echo "Use 'install' to build and install in /usr/local."
        echo "Use 'clean' to remove local builds.";;
esac
