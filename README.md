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
+ behaviortree.cpp/3.5.6

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

Conan profiles example from our team:


|                                                                                Linux                                                                                 |                                          Windows                                           |
|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------:|:------------------------------------------------------------------------------------------:|
|[settings]<br/>arch=x86_64<br/>arch_build=x86_64<br/>build_type=Debug<br/>compiler=gcc<br/>compiler.libcxx=libstdc++11<br/>compiler.version=9<br/>os=Linux<br/>os_build=Linux | [settings]<br/>os=Windows<br/>os_build=Windows<br/>arch=x86_64<br/>arch_build=x86_64<br/>compiler=Visual Studio<br/> compiler.version=16<br/> build_type=Debug |

## Final

### What can our bot do?

:white_check_mark: We have a graphical view that is currently off. We use sfml.\
:white_check_mark: Our bot connects to the game and plays it to the end.
He makes decisions based on behavior tree.

## Usage

Just run Pigs_on_the_moon application in the build\bin folder.\
Use key -n (name) -pa (password) -g (game name) -t (number turns) -pl (players number) -o (is observer 0/1)
```
Pigs_on_the_moon.exe -t 31 -n bot
```
or
```
Pigs_on_the_moon.exe -n bot -g finalBattle -t 45 -pl 3
```
##### Please build release version

### A few words about build

We have not encountered the problem of using auto_ptr, but we do not exclude the possibility of this event. Good luck :
neutral_face:

