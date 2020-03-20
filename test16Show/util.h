#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QString>
#include <QMutex>
#include <QMutexLocker>
#include <QDir>
#include <QDebug>
#include <QDateTime>

#define QML_PROPERTY(type,name) \
    Q_PROPERTY(type name READ name WRITE set##name NOTIFY name##Change); type m_##name; \
    public: type name() const { return m_##name;} \
    public Q_SLOTS: void set##name(type arg) { m_##name = arg;emit name##Change(arg);} \
    Q_SIGNALS:  \
    void name##Change(type arg);\
    private:

class DebugLogFile:public QObject
{
    Q_OBJECT
public:
    void writeLog(QString logfileName,QString fileName,QString lineNum,QString content){


       // qDebug()<<"writelog "<<logfileName;
        QDir dir;
        QString logFilePath = dir.absolutePath() +"/debug log";
        QString desFileName = logFilePath +"/" +logfileName+".txt";

        if (!dir.exists(logFilePath))
        {
            if(!dir.mkpath(logFilePath)){

                qDebug()<<"创建日志文件失败";
                return;
            }
        }
        QString  currentTime = QDateTime::currentDateTime().toString(" yyyy/MM/dd HH:mm:ss");

        QString desContent = currentTime + " :"+fileName+"   "+" "+lineNum +"    "+content;


        QFile file(desFileName);
        if(file.open((QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))){


            if(file.size() > 10*1024*1024){//大于10M删除文件 重新写文件
                file.close();
                file.remove();

                return;
            }
            QTextStream out(&file);
            out << desContent<<endl;

            file.close();
        }else{

            qDebug()<<"打开日志文件失败："<<desFileName<<"/n";
        }

    }

    static DebugLogFile *instance(){

        QMutexLocker lock(&mutex);
        if(logFile != nullptr){
            logFile = new DebugLogFile;
        }
        return logFile;
    }

private:
    static DebugLogFile *logFile;
    static QMutex mutex;
};


#endif // UTIL_H
