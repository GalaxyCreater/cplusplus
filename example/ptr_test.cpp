#include <string>

class CMyString
{
protected:
    int m_nSize;
    char *m_pData;

public:
    CMyString(const char *pStr);
    virtual ~CMyString();
};
CMyString::CMyString(const char *pstr)
{

    m_nSize = strlen(pstr);
    m_pData = new char[m_nSize + 1];
    strcpy(m_pData, pstr);
}

CMyString::~CMyString()
{

    delete[] m_pData;
}

CMyString GetString()
{

    CMyString str1 = "haha";
    CMyString str2 = "xixi";
    /*
    等价于CMyString str3(str1);
    由于CMyString没有提供拷贝构造函数，编译器会把str1的内容原原本本的复制给str3，这样，str1.m_pData这个指针也
被复制给str3了。在函数退出时，str1首先析构（顺序和编译器有关，这里只是一个假设，其实谁先析构问题都一样），
其析构函数删除了m_pData，此时str3的m_pData就成为一个悬挂指针。当str3析构时，它试图删除m_pData必然造成一个异常。
    */
    CMyString str3 = str1;
    // 和上面一样
    str2 = str1;

    return str3; // 返回时会创建一个CMyString临时对象,临时对象释放时,也会产生指悬挂问题
}