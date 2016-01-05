# simulationRainOfMusic

simulationRainOfMusic is a simulation tool designed for a choeregraphy with robots written using i-score, the interactive intermedia sequencer.

** To build the source code : **

* install openFrameworks (available on http://openframeworks.cc/download)
* clone the repository in the openFrameworks project folder (apps/myApps)
* build JamomaCore (available on https://github.com/Jamoma/JamomaCore)
* build OSSIA/API (available on https://github.com/OSSIA/API) and create a dynamic library :
$ cd API-build/
$ cmake -DBUILD_SHARED_LIBS:Bool=True .
* modify in the 'simulationRainOfMusic.qbs' the line 'cpp.libraryPaths' :
cpp.libraryPaths: ["path-to-API-build/Implementations/Jamoma"]
* add the path to the dynamic library in the variable LD_PATH_VARIABLE
* pfiou, the project simulationRainOfMusic is ready to be built !
   
