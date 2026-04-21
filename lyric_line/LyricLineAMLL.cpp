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

#include "LyricLine.hpp"
#include "lyricsyl.hpp"

QString LyricLine::toAMLL() const {
    QStringList syl_list{};

    for (const auto &syl : this->_syl_s) syl_list.push_back(syl->toAMLL());
    if (this->_is_bg) {
        if (syl_list.count()) {
            if (syl_list.first().contains('>'))
                syl_list.first().insert(syl_list.first().indexOf('>') + 1, '(');
            else
                syl_list.first().push_front('(');

            if (syl_list.last().contains('<'))
                syl_list.last().insert(syl_list.last().lastIndexOf('<'), ')');
            else
                syl_list.last().push_back(')');
        }
    }

    QStringList sub_line_list{};

    for (const auto &[lang, translation] : this->_translation) {
        const auto ptr = translation.get();
        QString context;
        if (const auto text = std::get_if<QString>(ptr)) {
            context = *text;
        } elif (const auto pair = std::get_if<std::pair<QString, std::shared_ptr<QString>>>(ptr)) {
            context = pair->first;
        } elif (const auto line = std::get_if<LyricLine>(ptr)) {
            context = line->toTXT();
        }
        sub_line_list.append(QString(R"(<span ttm:role="x-translation" xml:lang="%1">%2</span>)")
            .arg(lang)
            .arg(context));
    }

    for (const auto &[lang, transliteration] : this->_transliteration) {
        const auto ptr = transliteration.get();
        QString context;
        if (const auto text = std::get_if<QString>(ptr)) {
            context = *text;
        } elif (const auto pair = std::get_if<std::pair<QString, std::shared_ptr<QString>>>(ptr)) {
            context = pair->first;
        } elif (const auto line = std::get_if<LyricLine>(ptr)) {
            context = line->toTXT();
        }
        sub_line_list.append(QString(R"(<span ttm:role="x-roman" xml:lang="%1">%2</span>)")
            .arg(lang)
            .arg(context));
    }

    return QString(R"(<%1%2 begin="%3" end="%4">%5</%1>)")
    .arg(this->_is_bg ? "span" : "p")
    .arg(this->_is_bg ? R"( ttm:role="x-bg")" : QString(R"( ttm:agent="v%1" itunes:key="%2")").arg(this->_is_duet ? 2 : 1).arg(this->_key))
    .arg(this->_begin.toString(1))
    .arg(this->_end.toString(1))
    .arg(syl_list.join("") + sub_line_list.join(""));
}
