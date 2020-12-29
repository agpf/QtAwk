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


void test_buffer()
{
    QByteArray ba(
                "hello world 1\n"
                "hello world 2\n"
                "hello world 3\n"
                "hello world 4\n"
                "hello world 5\n"
                "hello world 6\n"
    );
    QtAwk awk;
    int ret = 0;
    ret = awk.setProg("{print NR, $0}");
    qDebug() << __func__ << "setProg" << ret;

    ret = awk.compile();
    qDebug() << __func__ << "compile" << ret;

    QByteArray out =  awk.exec(ba);
    qDebug() << __func__ << "exec" << out.constData();

}

int main(void)
{
    test_base();
    test_file();
    test_buffer();
    return 0;
}
