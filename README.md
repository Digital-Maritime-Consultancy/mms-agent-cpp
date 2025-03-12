# mms-agent-cpp

This is a C++ implementation of MMS Agent.
This project is configured as a CMake project with vcpkg and its [manifest](https://vcpkg.readthedocs.io/en/latest/specifications/manifests/) (`vcpkg.json`)

## Getting Started
Clone the repo with the `--recurse-submodules` flag
```bash
git clone --recurse-submodules https://github.com/Digital-Maritime-Consultancy/mms-agent-cpp.git
```  

Update the version of vcpkg in ./vcpkg folder if necessary
```bash
git pull origin master
```

Run `./vcpkg/bootstrap-vcpkg.sh` or `.\vcpkg\bootstrap-vcpkg.bat`

Fetch the dependencies (see [vcpkg.json](vcpkg.json)):  
(_This is optional, CMake should run `vcpkg install` anyway_)
```bash
./vcpkg/vcpkg --feature-flags=manifests install
```

Build the project using your IDE/build tool of choice or manually:

```bash
cmake -B build -S .
```
```bash
cmake --build build
```

## Execute app

```
./build/app/MmsTestApp
```

## Check the list of dependencies installed

```
./vcpkg/vcpkg list --x-install-root=./build/vcpkg_installed 
```

## For CLion users
To avoid long file indexing, you might want to exclude the `vcpkg` directory:
1. Right click on `vcpkg` in the Project window
2. Mark Directory as -> _Library Files_ or _Excluded_ (I recommend choosing the latter)

## Troubleshooting

If you're getting
```
Could not find a package configuration file provided by "fmt" with any of
  the following names:
 
  ...
```
or similar, try deleting cmake's build directory and rebuilding the project
