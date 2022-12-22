#ifndef WS_UTILS_H
#define WS_UTILS_H

#include <QString>
#include <QObject>

#include <iostream>
#include <sstream> // std::ostringstream

class WSUtils : public QObject
{
    Q_OBJECT
public:
    WSUtils();
    static std::string createJSONResponse(std::string p_content);
    static std::string createHTMLResponse(std::string p_content);
    static bool isAllowedMethod(const QString &method);

private:
    static QStringList m_allowedMethods;
};

#endif // WS_UTILS_H
