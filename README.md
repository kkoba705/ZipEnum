C++ で python の enumerate, zip 表記を使う。

解説記事　https://qiita.com/kkoba775/items/1849eaecf47789be4921

# install

Windows (Visual Studio 2022) なら、適当な作業用ディレクトリから Developer Command Prompt for VS2022 で
```
> git clone https://github.com/kkoba705/ZipEnum.git
> cd ZipEnum
> mkdir build
> cd build
> cmake -DCMAKE_INSTALL_PREFIX=c:/dev/ZipEnum ..
> cmake --build . --target install
```
として ```c:\dev\ZipEnum``` にインストールできる。
環境変数 ```CMAKE_PREFIX_PATH``` もしくは ```ZipEnum_DIR``` に ```c:\dev``` を登録する。

Ubuntu なら ```$ cmake -DCMAKE_INSTALL_PREFIX=$HOME/dev/ZipEnum ..``` に変更。
```~/.bashrc``` の最後に```export CMAKE_PREFIX_PATH=$HOME/dev``` もしくは
```export ZipEnum_DIR=$HOME/dev/ZipEnum``` を追加する。

# 使用例

作業用の適当なディレクトリを用意して、以下の内容で ```sample.cpp``` と ```CMakeLists.txt``` を作成する。
```sample.cpp
#include <iostream>
#include <vector>
#include <string>

#include <ZipEnum.hpp>
using zip_enum::zip, zip_enum::enumerate;

int main() {

    std::vector<std::string> A = {"a", "b", "z"};

    for (auto [i, s] : enumerate(A)) {
        std::cout << "[" << i << "] " << s << std::endl;
    }

    return 0;
}
```
```CMakeLists.txt
cmake_minimum_required(VERSION 3.21)
set(exename "sample")
project(${exename} CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(ZipEnum REQUIRED)

add_executable(${exename} ${exename}.cpp)
target_link_libraries(${exename} ZipEnum::ZipEnum)
```
Prompt（Terminal）から
```
> mkdir build
> cd build
> cmake ..
> cmake --build . --config Release 
```
でコンパイルできる。

