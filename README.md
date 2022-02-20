# Pigs-on-the-moon

## Main Developers

- [Eugene Rotkovich](https://github.com/ZhekLu)
- [Katsiaryna Stsefanenka](https://github.com/LeaSKaterina)
- [Dzianis Prokharau](https://github.com/denisprohorov)

## Dependencies

### Conan required

+ nlohmann_json/3.10.5 - static
+ sfml/2.5.1 - shared

## Instruction

### Command Line / Terminal required

If conan not installed

```
pip install conan
```

Directory : Pigs-on-the-moon

```
mkdir conanBuild
cd conanBuild
conan install ..

cd ..
mkdir cmake-build
cmake ..
cmake -build

cd bin
Pigs_on_the_moon
```

Conan profiles example:

<!-- Help me please. What a long line!!! -->

|                                                                                Linux                                                                                 |                                          Windows                                           |
|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------:|:------------------------------------------------------------------------------------------:|
|[settings]<br/>arch=x86_64<br/>arch_build=x86_64<br/>build_type=Debug<br/>compiler=gcc<br/>compiler.libcxx=libstdc++11<br/>compiler.version=9<br/>os=Linux<br/>os_build=Linux | [settings]<br/>os=Windows<br/>os_build=Windows<br/>arch=x86_64<br/>arch_build=x86_64<br/>compiler=Visual Studio<br/> compiler.version=16<br/> build_type=Debug |

## Stage 3

#### What can our bot do?

When the application starts, 3 identical bots enter the game and play there. They use breadth-first search to navigate.
Bot can kill enemy tanks and analyze neutrality rule.\
All configuration is contained in main.cpp.


