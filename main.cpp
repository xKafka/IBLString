#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

template<typename T>
class String
{
    std::vector<T> m_data;

public:
    String() = default;

    explicit String(std::vector<T> &&data)
       : m_data(std::move(data))
    {}
    explicit String(const std::vector<T> &data)
       : m_data(data)
    {}
    template<size_t N>
    String(const T(&data)[N])
    {
        m_data.clear();
        std::copy(data, data + N, std::back_inserter(m_data));
    }

    String &operator=(const String &) = default;

    template<size_t N>
    String &operator=(const T(&data)[N])
    {
        m_data.clear();
        std::copy(data, data + N, std::back_inserter(m_data));

        return *this;
    }

    inline typename std::vector<T>::iterator begin() { return m_data.begin(); }

    inline typename std::vector<T>::iterator end() { return m_data.end(); }

    inline typename std::vector<T>::const_iterator begin() const { return m_data.begin(); }

    inline typename std::vector<T>::const_iterator end() const { return m_data.end(); }

    String &operator+=( const String &other)
    {
        if(!m_data.empty())
            m_data.pop_back();

        m_data.insert(m_data.end(), other.begin(), other.end());

        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const String &from)
    {
        std::for_each(from.begin(), from.end(), [&out](const T &member){ out << member; });

        return out;
    }

    friend std::wostream &operator<<(std::wostream &out, const String &from)
    {
        std::for_each(from.begin(), from.end(), [&out](const T &member){ out << member; });

        return out;
    }

};

template<typename T>
String<T> operator+(const String<T> &left, const String<T> &right)
{
    String<T> result { left };

    return result += right;
}

template<typename T, size_t N>
String<T> operator+(const String<T> &left, const T(&right)[N])
{
    String<T> result { left };

    return result += String<T>{ right };
}

int main() {

    String<wchar_t> str(L"kokot");

    String<wchar_t> str1(L"kokot");

    String<wchar_t> str3 = L"fdf";

    std::wcout << str + str1;

    std::wcout << str + L"kokot";

    std::wcout << str3;

    return 0;
}