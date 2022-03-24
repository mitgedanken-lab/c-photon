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
    -Iinclude/
)

lib=(
    -Llib/
    -lfract
)

fail_op() {
    echo "Run with -d to build dynamically, or -s to build statically."
    exit
}

fail_os() {
    echo "OS is not supported yet..."
    exit
}

mac_dlib() {
    $cc ${flags[*]} ${inc[*]} ${lib[*]} -dynamiclib $src -o $name.dylib &&\
    install_name_tool -id @executable_path/$name.dylib $name.dylib 
}

linux_dlib() {
    $cc -shared ${flags[*]} ${inc[*]} ${lib[*]} -lm -fPIC $src -o $name.so 
}

build() {
    mkdir lib/
    pushd fract/ && ./build.sh -s && popd && mv fract/libfract.a lib/libfract.a
}

cleand() {
    if [ -d $1 ]; then
        rm -r $1 && echo "deleted '$1'"
    fi
}

cleanf() {
    if [ -f $1 ]; then
        rm $1 && echo "deleted '$1'"  
    fi
}

clean() {
    cleand lib
    cleanf $name.so
    cleanf $name.dylib
    cleanf $name.a
}

dlib() {
    if echo "$OSTYPE" | grep -q "darwin"; then
        mac_dlib
    elif echo "$OSTYPE" | grep -q "linux"; then
        linux_dlib
    else
        fails_os
    fi
}

slib() {
    $cc ${flags[*]} ${inc[*]} -c $src && ar -crv $name.a *.o && rm *.o
}

case "$1" in
    "-d")
        build && dlib;;
    "-s")
        slib;;
    "-build")
        build;;
    "-clean")
        clean;;
    *)
        fail_op;;
esac
