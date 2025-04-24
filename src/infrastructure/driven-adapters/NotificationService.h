#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include <Arduino.h>
#include "domain/model/Pond.h"

class NotificationService {
public:
    static void sendNotification(const Pond& pond);
};

#endif
