# HatchitEditor

[![Join the chat at https://gitter.im/thirddegree/HatchitEditor](https://badges.gitter.im/thirddegree/HatchitEditor.svg)](https://gitter.im/thirddegree/HatchitEditor?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

An Open Source 3D Game Editor written in C++ with Qt

---

##Contributing

This project is open to any community developed
pull-requests and we encourage all skill levels to contribute. 

<b>NOTE:</b> All code submitted to HatchitEditor will subject to license under GPLv3

##Build Instructions

All build instructions are subject to change

###Linux

All Linux development has currently been done on Ubuntu 16.04 XENIAL

Install the following dependencies:
* Qt 5.7 SDK (installed in home `~/Qt`)
    * <b>Prefix path must be located</b> `~/Qt/5.7/gcc_64`
* All dependencies of [Hatchit](https://www.github.com/thirddegree/Hatchit.git)

Then follow these simple directions:
* Clone down the repo with `git clone --recursive http://github.com/thirddegree/HatchitEditor.git`
* Make a build dir (e.g. mkdir build)
* cd into build/ and run cmake ..
* Now just run make to build HatchitEditor
* <b>Optional</b>
    * `sudo make install` to install to `/usr/local/bin`
        * <b>NOTE: Qt 5.7 libraries must be in path</b>
        

###Windows

This is a bit more of a pain. All dependencies are either submodules in the Third Party
directory <b>or</b> submodules of <b>Hatchit</b> and will need to be built before you build the editor.

All testing and development has been done on Windows 10 with Visual Studio 2015

Install the following dependencies:
* Install CMake (<b>must be in system path</b>)
* Qt 5.7 SDK
    * Add Qt binaries to <b>system path</b> `C:\Qt\5.7\msvc2015_64\bin`

##### Pre-Build
We recommend using some sort of cmd replacement in Windows such as cmder or some sort of bash shell

* Make sure that you can run `msbuild.exe` from your shell. If it's not there try running the `vcvarsall.bat` file located at `C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat` for Visual Studio 2015
* Clone down the repo with `git clone --recursive http://github.com/thirddegree/Hatchit`


##### Third Party
Next up is building all the dependencies. This should only have to be done once for your machine. After this you won't have to worry about `vcvarsall.bat` but you will need CMake.

* Run the `setup.bat` file. This should configure AND BUILD all your dependencies

##### HatchitEditor
This is the easy part!

* `cd` into `build`
* Open the <b>HatchitEditor.sln</b> solution file or execute it with `MSBuild.exe` to build all targets