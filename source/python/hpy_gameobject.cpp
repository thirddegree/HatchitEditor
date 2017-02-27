
#include <iostream>
#include <hpy_gameobject.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

GameObject::GameObject(const std::string &name)
    : m_name(name)
{

}

GameObject::~GameObject()
{

}

void GameObject::SetName(const std::string &name)
{
    m_name = name;
}

const std::string& GameObject::Name() const
{
    return m_name;
}
