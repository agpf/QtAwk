#ifndef INCLUDED_QTAWK_H
#define INCLUDED_QTAWK_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QTextCodec>
#include <QFile>
#include <QDebug>
#include <cstddef>
#include "awklib.h"
#include "awkerr.h"

class QtAwk
{
public:
    enum Error{
        ERR_NOMEM    = AWK_ERR_NOMEM,      //out of memory
        ERR_NOPROG   = AWK_ERR_NOPROG,     //no program given
        ERR_INPROG   = AWK_ERR_INPROG,     //cannot open program file
        ERR_INVVAR   = AWK_ERR_INVVAR,     //invalid variable argument
        ERR_BADSTAT  = AWK_ERR_BADSTAT,    //invalid interpreter status
        ERR_PROGFILE = AWK_ERR_PROGFILE,   //program file or string already set
        ERR_SYNTAX   = AWK_ERR_SYNTAX,     //syntax error
        ERR_INFILE   = AWK_ERR_INFILE,     //cannot open input file
        ERR_LIMIT    = AWK_ERR_LIMIT,      //limit exceeded
        ERR_ARG      = AWK_ERR_ARG,        //invalid argument
        ERR_FPE      = AWK_ERR_FPE,        //floating point error
        ERR_OTHER    = AWK_ERR_OTHER,      //other errors
        ERR_RUNTIME  = AWK_ERR_RUNTIME,    //runtime error
        ERR_OUTFILE  = AWK_ERR_OUTFILE,    //output file error
        ERR_PIPE     = AWK_ERR_PIPE,       //pipe error
        ERR_NOVAR    = AWK_ERR_NOVAR,      //variable not found
        ERR_ARRAY    = AWK_ERR_ARRAY,      //variable is an array
        ERR_INVTYPE  = AWK_ERR_INVTYPE,    //invalid variable type
    };

    QtAwk(void){
        _init();
        pi = awk_init(nullptr);
    }
    ~QtAwk(void){
        awk_end(pi);
    }

    ////////////////////////////////////////////////////////////////////////////////
    ///
    /// setProg: set progream
    ///
    /// prog has types below:
    /// 1/ const char *
    /// 2/ const QByteArray
    /// 3/ const QString
    /// 4/ const QStringList   use "\n" to join all strings
    ///
    ////////////////////////////////////////////////////////////////////////////////
    int setProg(const char *prog){
        return awk_setprog(pi, prog);
    }
    int setProg(const QByteArray &prog){
        return awk_setprog(pi, prog.constData());
    }
    int setProg(const QString &prog){
        return awk_setprog(pi, _toBa(prog));
    }
    int setProg(const QStringList &prog){
        return awk_setprog(pi, _toBa(prog.join("\n")));
    }
    int setProgFile(const QString &fn){
        QFile file(fn);
        if(file.open(QFile::ReadOnly)) {
            auto ba = file.readAll();
            return setProg(ba);
        } else {
            return ERR_INPROG;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////
    ///
    /// addArg : add argument
    ///
    /// arg support types below
    /// 1/ const char *
    /// 2/ const QByteArray
    /// 3/ const QString
    ///
    ////////////////////////////////////////////////////////////////////////////////
    int addArg(const char *arg){
        return awk_addarg(pi, arg);
    }
    int addArg(const QByteArray &arg){
        return awk_addarg(pi, arg.constData());
    }
    int addArg(const QString &arg){
        return awk_addarg(pi, _toBa(arg).constData());
    }

    int compile(){
        return awk_compile(pi);
    }
    int exec(){
        return awk_exec(pi);
    }
    QByteArray exec(const QByteArray &in){
        QByteArray out;
        static QByteArray *pout = nullptr;
        static const QByteArray *pin = nullptr;
        static int pin_offset = 0;

        pout = &out;
        pin = &in;
        pin_offset = 0;

        awk_infunc(pi,  []()->int {
            if(pin_offset >= pin->length()) {
                return EOF;
            }
            return pin->constData()[pin_offset++];
        });
        awk_outfunc(pi, [](const char *d, size_t len)->int{
            pout->append(d, static_cast<int>(len)); return 1;
        });

        int ret = awk_exec(pi);

        pin_offset = 0;
        pout = nullptr;
        pin = nullptr;

        if(ret < 0){
            return QByteArray();
        } else {
            return out;
        }
    }
    int run(const char *prog){
        return awk_run(pi, prog);
    }


    int setInput(const QString &inputFn){
        return awk_setinput(pi, _toBa(inputFn));
    }
    int setOutput(const QString &outputFn){
        return awk_setoutput(pi, _toBa(outputFn));
    }

    bool setCodec(const char *name){
        if(name == nullptr){
            tcodec = QTextCodec::codecForLocale();
            return true;
        } else {
            QTextCodec *c = QTextCodec::codecForName(name);
            if(c){
                tcodec = c;
                return true;
            } else {
                return false;
            }
        }
    }

private:
    void _init(){
        tcodec = QTextCodec::codecForName("UTF-8");
    }
    QByteArray _toBa(const QString &s);

    QTextCodec *tcodec;
    AWKINTERP *pi;
};

#endif
