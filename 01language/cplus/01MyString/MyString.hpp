#ifndef MYSTRING_HPP_
#define MYSTRING_HPP_

class MyString
{
public:
    MyString();
    MyString(const char* cstr);
    MyString(const MyString& other);
    ~MyString();
    MyString& operator=(const MyString& other);

    bool isEmpty() const;
    void print() const;
    int getLength() const;
private:
    void copy(const char* cstr);
    void reset();

private:
    char* m_pBuf = nullptr;
};

#endif