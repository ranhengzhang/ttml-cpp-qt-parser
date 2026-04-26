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

#ifndef LYRIC_PARSER_AGENT_H
#define LYRIC_PARSER_AGENT_H

#include <QStringList>

#include <map>

#include "utils.hpp"

namespace lyric::utils {
    class Agent {
    public:
        enum class AgentType {
            Person,
            Group,
            Other,
            Character,
            Organization
        };

        enum class NameType {
            Full,
            Family,
            Given,
            Alias,
            Other
        };

        struct AgentName {
            NameType type{};
            QString text{};

            bool operator==(const AgentName &other) const {
                return type == other.type && text == other.text;
            }

            bool operator!=(const AgentName &other) const {
                return !(*this == other);
            }
        };

        [[nodiscard]] AgentType getType() const;

        [[nodiscard]] QString getId() const;

        [[nodiscard]] const QList<AgentName> &getName() const;

        [[nodiscard]] bool isPerson() const { return this->_type == AgentType::Person; }

        [[nodiscard]] bool isGroup() const { return this->_type == AgentType::Group; }

        [[nodiscard]] static std::pair<Agent, Status> fromTTML(const QDomElement &xml);

        [[nodiscard]] QString toTTML();

    private:
        static std::map<AgentType, QString> _agent_type_name;
        static std::map<QString, AgentType> _agent_type_enum;
        static std::map<NameType, QString> _name_type_name;
        static std::map<QString, NameType> _name_type_enum;

        AgentType _type{};
        QString _id{};
        QList<AgentName> _names{};
    };
}

#endif //LYRIC_PARSER_AGENT_H
