#ifndef INCLUDED_QTAWK_H
#define INCLUDED_QTAWK_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QTextCodec>

#include "awklib.h"
#include "awkerr.h"

class QtAwk
{
public:
    QtAwk(void){
        _init();
        pi = awk_init(nullptr);
    }
    ~QtAwk(void){
        awk_end(pi);
    }

    int setProg(const char *prog){
        return awk_setprog(pi, prog);
    }
    int addArg(const char *arg){
        return awk_addarg(pi, arg);
    }
    int compile(){
        return awk_compile(pi);
    }
    int exec(){
        return awk_exec(pi);
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
