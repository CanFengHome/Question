#include "MyString.hpp"

#include <stdio.h>
#include <string.h>

MyString::MyString()
 : m_pBuf(nullptr)
{

}

MyString::MyString(const char* cstr)
{
    reset();
    copy(cstr);
}

MyString::MyString(const MyString& other)
{
    copy(other.m_pBuf);
}

MyString::~MyString()
{
    reset();
}

MyString& MyString::operator=(const MyString& other)
{
    if (this != &other)
    {
        copy(other.m_pBuf);
    }

    return *this;
}

void MyString::copy(const char* cstr)
{
    reset();
    if (cstr != nullptr)
    {
        int cstrLen = strlen(cstr);
        m_pBuf = new char[cstrLen+1];
        strncpy(m_pBuf, cstr, cstrLen);
        m_pBuf[cstrLen] = '\0';
    }
}

void MyString::reset()
{
    if (m_pBuf != nullptr)
    {
        delete []m_pBuf;
        m_pBuf = nullptr;
    }
}

bool MyString::isEmpty() const
{
    return m_pBuf == nullptr || strlen(m_pBuf) == 0;
}

void MyString::print() const
{
    puts(m_pBuf);
}

int MyString::getLength() const
{
    return (m_pBuf == nullptr) ? 0 : strlen(m_pBuf);
}