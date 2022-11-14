if [ -d build ]; then
   rm -rf build
fi

mkdir -p build
cd build

cmake -DGLFW_BUILD_DOCS=OFF -DASSIMP_BUILD_TESTS=OFF ..

make
pushd bin
    ./OPENGL
popd

cd ../
