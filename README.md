# Pigs-on-the-moon

## Main Developers

- [Eugene Rotkovich](https://github.com/ZhekLu)
- [Katsiaryna Stsefanenka](https://github.com/LeaSKaterina)
- [Dzianis Prokharau](https://github.com/denisprohorov)

## Dependencies

### Conan required

+ nlohmann_json/3.10.5 - static
+ sfml/2.5.1 - shared
+ ogg/1.3.5

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

<!-- 400 rows in line((( table -->
|                                                                                Linux                                                                                 |                                          Windows                                           |
|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------:|:------------------------------------------------------------------------------------------:|
|[settings]<br/>arch=x86_64<br/>arch_build=x86_64<br/>build_type=Debug<br/>compiler=gcc<br/>compiler.libcxx=libstdc++11<br/>compiler.version=9<br/>os=Linux<br/>os_build=Linux | [settings]<br/>os=Windows<br/>os_build=Windows<br/>arch=x86_64<br/>arch_build=x86_64<br/>compiler=Visual Studio<br/> compiler.version=16<br/> build_type=Debug |

## Stage 4

### What can our bot do?

:white_check_mark: improved GUI architecture.\
Gui try implement mvc pattern. The window is designed to easily add blocks of information.

:white_check_mark: improved multithreading.\
add mutex

:white_check_mark: added drawing new cells.

### A few words about the launch
We have not encountered the problem of using auto_ptr, but we do not exclude the possibility of this event. Good luck :neutral_face:

