#include "ws_utils.h"

WSUtils::WSUtils()
{

}

std::string WSUtils::createJSONResponse(QString input) {
    int contentLength = input.length();

    std::ostringstream oss;
    oss << "HTTP/1.1 200 OK\r\n";
    oss << "Content-Type: application/json\r\n";
    oss << "Content-Length: " << contentLength << "\r\n";
    oss << "\r\n";
    oss << input.toStdString();

    return oss.str();
}
