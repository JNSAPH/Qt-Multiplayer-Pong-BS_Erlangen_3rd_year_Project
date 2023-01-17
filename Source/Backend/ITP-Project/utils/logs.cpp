#include "logs.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

LogUtils& LogUtils::getInstance()
{
    static LogUtils instance;
    return instance;
}

void LogUtils::appendData(const QStringList& data) {
    if(m_data.size()>m_maxRows)
    {
        qDebug()<<"Data size exceeded maximum rows, data not appended";
        return;
    }
    m_data.append(data);
}

void LogUtils::saveToCSV(const QString& fileName) {
    QFile file(fileName);
    QString buffer;
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing: " << file.errorString();
        return;
    }

    for (const auto& row : m_data) {
        buffer.append(row.join(",") + "\n");
        if(buffer.size()>m_maxBufferSize)
        {
            file.write(buffer.toUtf8());
            buffer.clear();
        }
    }
    file.write(buffer.toUtf8());
    file.close();
    m_data.clear();
}

void LogUtils::setMaxRows(unsigned int maxRows)
{
    m_maxRows=maxRows;
}
void LogUtils::setMaxBufferSize(unsigned int maxBufferSize)
{
    m_maxBufferSize=maxBufferSize;
}

LogUtils::LogUtils()
{
    m_maxRows=UINT_MAX;
    m_maxBufferSize=UINT_MAX;
}
