# Setup
### Windows
```sh
.\setup.bat
```
### Linux
```sh
chmod +x setup.sh
./setup.sh
```
## Configuring CMAKE and compiling
If you are working with an IDE like CLion, try to reload the CMakeLists. 
The IDE should now detect the presets.

### configuring manually
If not or if you are working from the terminal you can manually configure the project:

```sh
# List all available presets:
cmake --list-presets

# configure the preset you want:
cmake --preset debug
```

### compiling manually
```sh
# to compile when working from terminal:
cmake --build --preset debug

# multithreaded build:
cmake --build --preset debug -j 8

# cleanbuild:
cmake --build --preset debug --target clean
```
