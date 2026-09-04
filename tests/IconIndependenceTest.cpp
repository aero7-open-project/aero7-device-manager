#include "IconHelper.h"

#include <QApplication>
#include <QHash>
#include <QImage>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    const QStringList names = {
        "computer", "kded5", "network-bluetooth", "drive-harddisk",
        "video-display", "media-optical", "input-gaming",
        "input_devices_settings", "input-keyboard", "input-mouse",
        "network-card", "smartphone", "cpu", "drive-harddisk-encrypted",
        "kmix", "drive-removable-media-usb", "dialog-question",
        "dialog-cancel", "view-refresh", "system-software-update",
        "document-properties", "list-add"
    };
    QHash<QString,QImage> baseline;
    QIcon::setThemeName("Aero7-test-theme");
    for(const QString &name:names){const QIcon icon=resolveIcon(name);if(icon.isNull())return 1;for(int size:{16,22,24,32,48,64,128,256})if(icon.pixmap(size,size).isNull())return 2;baseline.insert(name,icon.pixmap(32,32).toImage());}
    for(const QString &theme:{QStringLiteral("breeze"),QStringLiteral("breeze-dark"),QStringLiteral("missing-aero7-theme")}){QIcon::setThemeName(theme);for(const QString &name:names)if(resolveIcon(name).pixmap(32,32).toImage()!=baseline.value(name))return 3;}
    if(aero7ResourceIcon(":/missing/device.svg","unknown-device").isNull())return 4;
    return 0;
}
