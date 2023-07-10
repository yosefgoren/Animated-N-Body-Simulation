# Dependencies
* Windows - Tested with windows 11
* [SFML](https://www.sfml-dev.org/download/sfml/2.6.0/) - Tested with version 2.6.0
* C++ Compiler - Tested with clang 16.0.3

# Setup & Run
1. Install SFML or make sure it is installed:
  * Download the zip file containing headers and binaries.
  * Unzip it and move the unzipped folder to be at 'C:\SFML'.
  * Add `C:\SFML\bin` to the `PATH` environment variable.
If you change `C:\SFML` elsewhere make sure to change it in `CMakeLists.txt` also.
2. clone the repo with:
```
git clone https://github.com/yosefgoren/Animated-N-Body-Simulation.git
```
3. Configure then build cmake:
Either with vsocde Extension:
  * Open vscode with repo as root directory.
  * Run cmake select kit command.
  * Run cmake configure command.
  * Build the target `nbody`.
Or with command line:
```
cd Animated-N-Body-Simulation
mkdir build
cmake ..
make
```

4. Run the simulation executable with:
```
./nbody
```
