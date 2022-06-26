# opengl
learning graphics programming

## Prerequisite
* cmake
* conan package manager [installation guide](https://docs.conan.io/en/latest/installation.html)


## Run
* Create build directory
```
   $ mkdir build && pushd build
```
* Install dependencies
```
   $ conan install .. --build=missing

```
* Compile
```
   $ cmake ..
   $ make && ./bin/OPENGL
   $ popd
```