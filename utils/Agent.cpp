//
// Created by LEGION on 2026/4/6.
//

#include "Agent.hpp"

namespace lyric::utils {
    std::map<Agent::AgentType, QString> Agent::_agent_type_name = {
        {AgentType::Person, "person"},
        {AgentType::Group, "group"},
        {AgentType::Other, "other"},
        {AgentType::Character, "character"},
        {AgentType::Organization, "organization"}
    };

    std::map<QString, Agent::AgentType> Agent::_agent_type_enum = {
        {"person", AgentType::Person},
        {"group", AgentType::Group},
        {"other", AgentType::Other},
        {"character", AgentType::Character},
        {"organization", AgentType::Organization}
    };

    std::map<Agent::NameType, QString> Agent::_name_type_name = {
        {NameType::Full, "full"},
        {NameType::Family, "family"},
        {NameType::Given, "given"},
        {NameType::Alias, "alias"},
        {NameType::Other, "other"}
    };

    std::map<QString, Agent::NameType> Agent::_name_type_enum = {
        {"full", NameType::Full},
        {"family", NameType::Family},
        {"given", NameType::Given},
        {"alias", NameType::Alias},
        {"other", NameType::Other}
    };

    Agent::AgentType Agent::getType() const {
        return this->_type;
    }

    QString Agent::getId() const {
        return this->_id;
    }

    const QList<Agent::AgentName> & Agent::getName() const {
        return this->_names;
    }

    std::pair<Agent, Status> Agent::fromTTML(const QDomElement &xml) {
        const auto el = xml.toElement();

        if (not el.hasAttribute("type") or not el.hasAttribute("xml:id")) {
            return {{}, Status::InvalidStructure};
        }

        Agent agent;
        const auto agent_type = el.attribute("type").toLower();
        const auto agent_id = el.attribute("xml:id");

        if (not _agent_type_enum.contains(agent_type)) {
            return {{}, Status::InvalidStructure};
        }

        agent._type = _agent_type_enum[agent_type];
        agent._id = agent_id;

        const auto name_s = el.elementsByTagName("ttm:name");
        for (int i = 0; i < name_s.count(); i++) {
            const auto name_type = name_s.at(i).toElement().attribute("type").toLower();
            const auto name_text = name_s.at(i).toElement().text();
            agent._names.append({_name_type_enum[name_type], name_text});
        }

        return {agent, Status::Success};
    }

    QString Agent::toTTML() {
        QStringList agent_names{};

        for (const auto &[type, text]: this->_names) {
            agent_names.append(QString(R"(<ttm:name type="%1">%2</ttm:name>)").arg(_name_type_name[type]).arg(toHtmlEscaped(text)));
        }

        return QString(R"(<ttm:agent type="%1" xml:id="%2"%3)")
            .arg(_agent_type_name[this->_type])
            .arg(this->_id)
            .arg(agent_names.isEmpty() ? R"(/>)" : QString(R"(>%1</ttm:agent>)").arg(agent_names.join("")));
    }
}
