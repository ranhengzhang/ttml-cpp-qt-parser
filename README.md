# C++ Qt TTML Parser

## 概要

C++ Qt TTML Parser 是一个用于解析 TTML 歌词格式并导出为多种其他格式的 C++ 库。它以 TTML 作为核心输入格式，支持导出为 LRC、QRC、YRC、KRC、ASS、SPL、LYS 等主流歌词格式，提供了统一的 API 接口，方便将 TTML 歌词转换为其他格式。

## 使用说明

### 环境要求

![](https://skills.syvixor.com/api/icons?perline=15&i=cpp,qtwidgets,cmake)

- C++23 或更高版本
- Qt 6.x
- CMake 3.20+

### 集成方式

#### 方式一：作为子目录使用

```cmake
add_subdirectory(path/to/lyric)
target_link_libraries(your_target PRIVATE LyricParser::lyric)
```

#### 方式二：通过 find_package 使用（安装后）

```cmake
find_package(LyricParser REQUIRED)
target_link_libraries(your_target PRIVATE LyricParser::lyric)
```

### 安装

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
cmake --install build --prefix /your/install/path
```

### 基本用法

```cpp
#include "LyricObject.hpp"
#include <QString>

// 从 TTML 解析歌词
QString ttmlContent = "...";  // 你的 TTML 内容
auto [lyric, status] = LyricObject::fromTTML(ttmlContent);

if (status == LyricObject::Status::Success) {
    // 导出为其他格式
    QString lrc = lyric.toLRC("");
    QString ass = lyric.toASS();
    QString qrc = std::get<0>(lyric.toQRC("zh", ""));
}
```

### 支持的格式

| 格式 | 输入 | 输出 |
|------|------|------|
| TTML | ✅ | ✅ |
| LRC | - | ✅ |
| QRC | - | ✅ |
| YRC | - | ✅ |
| KRC | - | ✅ |
| ASS | - | ✅ |
| SPL | - | ✅ |
| LYS | - | ✅ |

## 许可声明

本库采用 GNU 宽通用公共许可证第 3 版（LGPL-3.0-or-later）授权。

```
LyricParser - A C++ library for parsing and converting various lyric formats
Copyright (C) 2026  ranhengzhang

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library.  If not, see <https://www.gnu.org/licenses/>.
```

完整的许可证文本请参见 [LICENSE](LICENSE) 文件。

## 致谢

![](https://skills.syvixor.com/api/icons?perline=15&i=qtwidgets,clion,trae,deepseek,windows)
