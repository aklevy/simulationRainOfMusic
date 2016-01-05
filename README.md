# simulationRainOfMusic

simulationRainOfMusic is a simulation tool designed for a choeregraphy with robots written using i-score, the interactive intermedia sequencer.  
The aim of this tool is to help the artists of the project RainOfMusic to create a choeregraphy using drones and quadruped robots Metabots (https://github.com/Rhoban/Metabot).


**To build the project simulationRainOfMusic :**

* Install openFrameworks (available on http://openframeworks.cc/download)

* Clone the repository in the openFrameworks project folder:
    $ cd of_folder/apps/myApps  
    $ git clone https://github.com/iscore-metabots/simulationRainOfMusic

* Build JamomaCore (available on https://github.com/Jamoma/JamomaCore)

* Build OSSIA/API (available on https://github.com/OSSIA/API) and create a dynamic library:

    $ cd API-build/  
    $ cmake -DBUILD_SHARED_LIBS:Bool=True .

* Modify in the file 'simulationRainOfMusic.qbs' the line 'cpp.libraryPaths':

    cpp.libraryPaths: ["path-to-API-build/Implementations/Jamoma"]

* Add the path to the dynamic library in the variable LD_PATH_VARIABLE

* Pfiou, the project simulationRainOfMusic is ready to be built !
   
