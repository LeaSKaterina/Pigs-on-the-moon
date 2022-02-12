# Pigs-on-the-moon

## Stage 2

Added support for new tanks. The bot can walk and kill enemy tanks. Required libraries are connected via conan.

## Conan dependency

nlohmann_json/3.10.5 - static lib\
sfml/2.5.1 - shared lib

## Instruction

```
pip install conan
```

Directory : Pigs-on-the-moon

```
mkdir conanBuild
cd conanBuild
conan install ..
```
As sfml is a shared lib in folder conanBuild creates bin folder. Move this folder to bin folder
with executable file.

## Some words about development

Lib sfml has two versions: debug and release. If you want run project in debug mode 
redact conan profile. In particular I set build_type=Debug in user/.conan/profile/default.\
Or you can use conan install .. -s build_type=Debug.
