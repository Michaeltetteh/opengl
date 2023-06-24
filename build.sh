# if [ -d build ]; then
#     rm -rf build
# fi

# mkdir -p build

cd build

cmake -DGLFW_BUILD_DOCS=OFF -DASSIMP_BUILD_TESTS=OFF ..
cmake --build . --parallel 4

    pushd bin
        ./normal_map
    popd
cd ../
