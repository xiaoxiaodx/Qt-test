#include "activex.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if (!QAxFactory::isServer()) {
        ActiveX w;
        w.show();
        return app.exec();
    }
    return app.exec();
}

//! [1]
QAXFACTORY_BEGIN("{EC08F8FC-2754-47AB-8EFE-56A54057F34E}", /* type library ID */ "{A095BA0C-224F-4933-A458-2DD7F6B85D8F}") /* application ID */
    QAXCLASS(ActiveX)
QAXFACTORY_END()
//! [1]
