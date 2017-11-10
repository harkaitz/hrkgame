# hrkgame

A simple TicTacToe game for the terminal written in C++. It uses the alpha-beta
algorithm. I wrote this to learn C++ language and CMake.

### Prerequisites

A C++ compiler and CMake.

### Installing

This project comes with a wrapper `./configure` around CMake. You can use it or not.
The default prefix is $HOME/.local, you can change it.

```
./configure [--host=i686-w64-mingw32] [--prefix=/usr/local]
make -C build-last
make -C build-last install
```

## Running.

You can make the computer fight itself. You can see all options
with `hrkgamex -h`.

```
> hrkgamex -g tictactoe -x aa
```

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md)

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* Harkaitz Agirre Ezama

## License

Read [LICENSE](LICENSE) file for details

