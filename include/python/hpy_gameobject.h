
#pragma once

#include <string>

class GameObject
{
public:
    GameObject(const std::string& name);

    ~GameObject();

    void SetName(const std::string& name);
    const std::string& Name() const;

private:
    uint32_t    m_id;
    std::string m_name;
};