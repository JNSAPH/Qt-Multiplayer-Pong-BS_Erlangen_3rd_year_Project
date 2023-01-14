#ifndef WSOCKETCONTROLLER_H
#define WSOCKETCONTROLLER_H

// wSocketController.h

#include <QObject>
#include "../utils/websocketclient.h"

class wSocketController
{
private:
    static wSocketController* instance;
    wSocketController() {}
    wSocketController(const wSocketController&);
    wSocketController& operator=(const wSocketController&);

public:
    static wSocketController* getInstance()
    {
        if (!instance)
            instance = new wSocketController();
        return instance;
    }
    void connectToServer();
    // other member functions
};

#endif // WSOCKETCONTROLLER_H
