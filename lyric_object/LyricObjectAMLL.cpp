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

#include "LyricObject.hpp"

QString LyricObject::toAMLL()
{
    QStringList meta_data_list{};

    for (auto &[key, value]: this->_meta_data_s) {
        meta_data_list.push_back(QString(R"(<amll:meta key="%1" value="%2"/>)")
        .arg(lyric::utils::toHtmlEscaped(key))
        .arg(lyric::utils::toHtmlEscaped(value)));
    }

    for (auto &song_writer: this->_song_writer_s) {
        meta_data_list.push_back(QString(R"(<amll:meta key="songWriter" value="%1"/>)")
        .arg(lyric::utils::toHtmlEscaped(song_writer)));
    }

    QStringList line_text_list{};

    for (auto &line: this->_line_s) {
        line_text_list.push_back(line.toAMLL());
    }

    return QString(R"(<tt xmlns="http://www.w3.org/ns/ttml" xmlns:ttm="http://www.w3.org/ns/ttml#metadata" xmlns:amll="http://www.example.com/ns/amll" xmlns:itunes="http://music.apple.com/lyric-ttml-internal">%1%2</tt>)")
    .arg(QString(R"(<head><metadata><ttm:agent type="person" xml:id="v1"/>%1%2</metadata></head>)")
        .arg(this->_have_duet ? R"(<ttm:agent type="other" xml:id="v2"/>)" : "")
        .arg(meta_data_list.join("")))
    .arg(QString(R"(<body dur="%1"><div begin="%2" end="%1">%3</div></body>)")
        .arg(this->getDur().toString(1))
        .arg(this->getStart().toString(1))
        .arg(line_text_list.join("")));
}
