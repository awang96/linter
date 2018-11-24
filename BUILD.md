# Linux

```bash
mkdir build
cd build
cmake ..
make
```

You can directly import the project into [CLion][clion] using the `CMakeLists.txt` file.

# Codeblocks

Either use the included `.cbp`, or :

```shell
mkdir build
cd build
cmake .. -G "CodeBlocks - MinGW Makefiles"
```

And open the generated `.cbp`.


If using the included `.cpb`, be careful not to commit absolute paths, 
Codeblocks has that nasty habit of doing that.


[clion]: https://www.jetbrains.com/clion/
