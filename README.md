# simulationRainOfMusic

simulationRainOfMusic is a simulation tool designed for a choeregraphy with robots written using i-score, the interactive intermedia sequencer.

**To build the source code :**

* Install openFrameworks (available on http://openframeworks.cc/download)

* Clone the repository in the openFrameworks project folder (apps/myApps)

* Build JamomaCore (available on https://github.com/Jamoma/JamomaCore)

* Build OSSIA/API (available on https://github.com/OSSIA/API) and create a dynamic library :

$ cd API-build/

$ cmake -DBUILD_SHARED_LIBS:Bool=True .

* Modify in the 'simulationRainOfMusic.qbs' the line 'cpp.libraryPaths' :
cpp.libraryPaths: ["path-to-API-build/Implementations/Jamoma"]

* Add the path to the dynamic library in the variable LD_PATH_VARIABLE

* Pfiou, the project simulationRainOfMusic is ready to be built !
   
