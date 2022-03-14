//
// Created by kalasoft on 3/13/22.
//

#ifndef KALASOFT_GLAPPLICATION_H
#define KALASOFT_GLAPPLICATION_H


#include <KSApplication.h>

class GLApplication : public KSApplication{

public:
    GLApplication() = delete;
    GLApplication(android_app *pApp):KSApplication(pApp){};

protected:
    void onCreate() override;

};


#endif //KALASOFT_GLAPPLICATION_H
