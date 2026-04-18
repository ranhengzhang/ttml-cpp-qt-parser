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

#ifndef LYRIC_PARSER_LYRICSYL_H
#define LYRIC_PARSER_LYRICSYL_H

#include <QDomDocument>

#include "LyricTime.hpp"
#include "utils.hpp"

class LyricSyl {
    friend bool operator==(const LyricSyl &lhs, const LyricSyl &rhs) {
        return lhs._text == rhs._text
               && lhs._begin == rhs._begin
               && lhs._end == rhs._end
               && lhs._orig.lock() == rhs._orig.lock()
               && lhs._is_text == rhs._is_text;
    }

public:
    using Status = lyric::utils::Status;

    [[nodiscard]] static std::pair<LyricSyl, Status> fromTTML(const QDomNode &span);

    [[nodiscard]] QString toTTML(bool xmlns = false);

    [[nodiscard]] QString toASS() const;

    [[nodiscard]] QString toSPL() const;

    [[nodiscard]] QString toQRC() const;

    [[nodiscard]] QString toYRC() const;

    [[nodiscard]] QString toKRC(const LyricTime &line_begin) const;

    void setOrig(const std::shared_ptr<LyricSyl>& orig_shared);

    [[nodiscard]] std::shared_ptr<LyricSyl> getOrig() const;

    [[nodiscard]] static LyricSyl fromText(const QString &text);

    [[nodiscard]] LyricTime getDuration() const;

    [[nodiscard]] QString getText() const;

    void setText(const QString &text);

    [[nodiscard]] bool getIsText() const;

    [[nodiscard]] bool isText() const;

    void setIsText(bool is_text);

    [[nodiscard]] LyricTime getBegin() const;

    void setBegin(const LyricTime &begin);

    [[nodiscard]] LyricTime getEnd() const;

    void setEnd(const LyricTime &end);

    [[nodiscard]] bool getIsExplicit() const;

    void removeRuby();

private:
    QString _text{};
    LyricTime _begin{};
    LyricTime _end{};
    std::weak_ptr<LyricSyl> _orig{};
    bool _is_text{};
    bool _is_explicit{};
    std::vector<std::shared_ptr<LyricSyl>> _ruby_s{};
    bool _is_phrase_start{false};
};


#endif //LYRIC_PARSER_LYRICSYL_H
