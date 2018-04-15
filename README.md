
# Build

```bash
export SFML_DIR=path/to/SFML/SFML
make
```

# Run

Before running an executable, prepend to `LD_LIBRARY_PATH` the path to the shared
libraries of SFML, like so:

```bash
export LD_LIBRARY_PATH=${SFML_DIR}/lib:$LD_LIBRARY_PATH
out/t1.out
```
