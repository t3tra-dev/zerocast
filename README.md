[[Japanese/日本語](README.ja.md)]

# zerocast

**"zerocast"** is a _lossy_ compression technology boasting the highest compression ratio in history.

zerocast achieves an "undefined" compression ratio by compressing all data to 0 bytes. Data can be restored within a finite time by using an infinite number of monkeys for decompression.

Well...of course, this is a joke!

# usage

This repository implements the `zerocast` CLI. Usage is as follows:

```sh
# help (aliases: --help, -h)
zerocast help

# compress
zerocast compress <input_path> [output_path]

# decompress
zerocast decompress <input_path> [output_path]

# version (aliases: --version, -v)
zerocast version
```

## build & install

The `zerocast` CLI can be built and installed using the following methods:

```sh
# build
cmake -S . -B build && cmake --build build

# install
sudo cmake --install build
```

## related works

- Infinite Monkey Theorem
- God
- Engineers who didn't back up their data

Users' Creations:

- [otoneko1102/amazing-compression-tech](https://github.com/otoneko1102/amazing-compression-tech)

## license

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
