#ifndef LOGUTILS_H
#define LOGUTILS_H

#include <QString>
#include <QStringList>
#include <QList>

class LogUtils
{
public:
    static LogUtils& getInstance();
    void appendData(const QStringList& data);
    void saveToCSV(const QString& fileName);
    void setMaxRows(unsigned int maxRows);
    void setMaxBufferSize(unsigned int maxBufferSize);

private:
    LogUtils();
    QList<QStringList> m_data;
    unsigned int m_maxRows;
    unsigned int m_maxBufferSize;
};

#endif // LOGUTILS_H
