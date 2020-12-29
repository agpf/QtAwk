#include "qtawk.h"
#include <QDebug>

void test_base()
{
    QtAwk awk;
    int ret = 0;
    ret = awk.setProg("BEGIN {print \"Output redirected\"}");
    qDebug() << __func__ << "setProg" << ret;

    ret = awk.compile();
    qDebug() << __func__ << "compile" << ret;

    ret = awk.exec();
    qDebug() << __func__ << "exec" << ret;

}

void test_file()
{
    QtAwk awk;
    int ret = 0;
    ret = awk.setProg("{print NR, $0}");
    qDebug() << __func__ << "setProg" << ret;

    ret = awk.compile();
    qDebug() << __func__ << "compile" << ret;

    ret = awk.addArg("infile.txt");
    qDebug() << __func__ << "addArg" << ret;

    ret = awk.exec();
    qDebug() << __func__ << "exec" << ret;

}

int main(void)
{
    test_base();
    test_file();
    return 0;
}
