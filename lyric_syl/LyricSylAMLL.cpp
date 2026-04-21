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

#include "LyricSyl.hpp"

QString LyricSyl::toAMLL() {
    return this->isText() ? lyric::utils::toHtmlEscaped(this->_text) :
    QString(R"(<span begin="%1" end="%2"%3>%4</span>)")
    .arg(this->_begin.toString(1))
    .arg(this->_end.toString(1))
    .arg(this->_is_explicit ? R"( amll:obscene="true")" : "")
    .arg(lyric::utils::toHtmlEscaped(this->_text));
}
