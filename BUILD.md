# Linux

```bash
mkdir build
cd build
cmake ..
make
```

You directly use the `CMakeLists.txt` file with Intellij CLion.

# Codeblocks

Either use the included `.cbp`, or :

```shell
mkdir build
cd build
cmake .. -G "CodeBlocks - MinGW Makefiles"
```

And open the generated `.cbp`.


If using the included `.cpb`, be careful not to commit absolute paths.
