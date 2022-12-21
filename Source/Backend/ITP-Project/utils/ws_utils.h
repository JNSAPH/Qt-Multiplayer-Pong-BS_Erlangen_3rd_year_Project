#ifndef WS_UTILS_H
#define WS_UTILS_H

#include <QString>
#include <QObject>

#include <iostream>
#include <sstream>      // std::ostringstream

class WSUtils: public QObject
{
    Q_OBJECT
public:
    WSUtils();
    static std::string createJSONResponse(QString input);
};

#endif // WS_UTILS_H
