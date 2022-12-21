#include "ws_utils.h"

WSUtils::WSUtils()
{
}

QStringList WSUtils::m_allowedMethods = {"GET", "POST", "PUT", "DELETE"};

std::string WSUtils::createJSONResponse(std::string input) {
    int contentLength = input.length();

    std::ostringstream oss;
    oss << "HTTP/1.1 200 OK\r\n";
    oss << "Content-Type: application/json\r\n";
    oss << "Content-Length: " << contentLength << "\r\n";
    oss << "\r\n";
    oss << input;

    return oss.str();
}

bool WSUtils::isAllowedMethod(const QString &method) {
    return m_allowedMethods.contains(method, Qt::CaseInsensitive);
}
