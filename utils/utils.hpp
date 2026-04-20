//  LyricParser - A C++ library for parsing TTML and exporting to various lyric formats
//  Copyright (C) 2026  ranhengzhang
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 3 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library.  If not, see <https://www.gnu.org/licenses/>.

#ifndef LYRIC_PARSER_UTILS_H
#define LYRIC_PARSER_UTILS_H

#define elif else if

#include <QDomNode>
#include <QString>

class LyricLine;

namespace lyric::utils {
    /**
     * @brief 附加行对象，挂载到行的 <code>lang</code> 下或者 object 的 <code>lang->key</code> 下
     */
    using LyricTrans = std::variant<std::pair<QString, std::shared_ptr<QString>>, LyricLine, QString>;

    enum class SubType {
        Transliteration, // 音译
        Translation // 翻译
    };

    enum class Status {
        Success, // 成功
        InvalidFormat, // 无法解析为 Dom
        InvalidStructure, // Dom 结构错误
        InvalidTimeFormat // 时间格式错误
    };

    QString &easyCompress(QString &text);

    std::tuple<QString, Status> compressTtml(QString ttml);

    QString toHtmlEscaped(const QString &text);

    QString normalizeBrackets(QString &text);

    LyricLine normalizeBrackets(LyricLine &line);

    QString getDeepInnerText(const QDomNode &node);

    QString toLineTrans(QString &dom_text, const SubType line_type);

    bool isSymbol(const QString &text);

    bool compareKeysByLengthThenDefault(const QString &key1, const QString &key2);
}

#endif //LYRIC_PARSER_UTILS_H
