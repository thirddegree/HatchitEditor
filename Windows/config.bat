cd _build
mkdir bin\Debug
mkdir bin\Release

REM Place all third party libs into the Debug and Release bin folders

copy /Y ..\..\Hatchit\Windows\_build\dependencies\SDL2\bin\Debug\SDL2.dll bin\Debug
copy /Y ..\..\Hatchit\Windows\_build\dependencies\assimp\bin\Debug\assimp.dll bin\Debug
copy /Y ..\..\Hatchit\Windows\_build\dependencies\glew\bin\Debug\glew32.dll bin\Debug
copy /Y ..\..\Hatchit\Windows\_build\dependencies\tinyxml2\bin\Debug\tinyxml2.dll bin\Debug
copy /Y ..\..\Hatchit\Windows\_build\dependencies\Python\bin\Debug\python3.dll bin\Debug
copy /Y ..\..\Hatchit\Windows\_build\dependencies\Python\bin\Debug\python34_d.dll bin\Debug

copy /Y ..\..\Hatchit\Windows\_build\dependencies\SDL2\bin\Release\SDL2.dll bin\Release
copy /Y ..\..\Hatchit\Windows\_build\dependencies\assimp\bin\Release\assimp.dll bin\Release
copy /Y ..\..\Hatchit\Windows\_build\dependencies\glew\bin\Release\glew32.dll bin\Release
copy /Y ..\..\Hatchit\Windows\_build\dependencies\tinyxml2\bin\Release\tinyxml2.dll bin\Release
copy /Y ..\..\Hatchit\Windows\_build\dependencies\Python\bin\Release\python3.dll bin\Release
copy /Y ..\..\Hatchit\Windows\_build\dependencies\Python\bin\Release\python34.dll bin\Release

mkdir VS2013
cd VS2013
mkdir moc
cmake ../../ -G "Visual Studio 12 2013 Win64"