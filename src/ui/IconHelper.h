#pragma once

#include <QDebug>
#include <QFile>
#include <QIcon>
#include <QSize>
#include <QString>
#include <initializer_list>

namespace Aero7DeviceIcons {

inline QString normalized(QString value) { value = value.toLower(); value.replace('_', '-'); return value; }

inline QIcon exact(const QString &name)
{
    QIcon icon;
    for (const int size : {8, 16, 22, 24, 32, 36, 48, 64, 72, 96, 128, 192, 256}) {
        const QString path = QStringLiteral(":/aero7/pack/%1/%2.png").arg(size).arg(name);
        if (QFile::exists(path)) icon.addFile(path, QSize(size, size));
    }
    return icon;
}

inline QString mapped(const QString &raw)
{
    const QString name = normalized(raw);
    if (name.contains("previous") || name.contains("back") || name.contains("left")) return QStringLiteral("go-previous");
    if (name.contains("next") || name.contains("forward") || name.contains("right")) return QStringLiteral("go-next");
    if (name.contains("refresh") || name.contains("update") || name.contains("scan")) return QStringLiteral("view-refresh");
    if (name.contains("properties") || name.contains("configure")) return QStringLiteral("document-properties");
    if (name.contains("delete") || name.contains("remove") || name.contains("uninstall") || name.contains("disable")) return QStringLiteral("edit-delete");
    if (name.contains("add")) return QStringLiteral("list-add");
    if (name.contains("help")) return QStringLiteral("help-contents");
    if (name.contains("unknown") || name.contains("question") || name.contains("warning")) return QStringLiteral("dialog-question");
    if (name.contains("tree") || name.contains("list")) return QStringLiteral("view-list-tree");
    if (name.contains("battery") || name.contains("kded")) return QStringLiteral("battery-full");
    if (name.contains("bluetooth")) return QStringLiteral("bluetooth");
    if (name.contains("optical") || name.contains("cdrom") || name.contains("dvd")) return QStringLiteral("drive-optical");
    if (name.contains("disk") || name.contains("storage") || name.contains("harddisk") || name.contains("ide")) return QStringLiteral("drive-harddisk");
    if (name.contains("display") || name.contains("monitor") || name.contains("video")) return QStringLiteral("display");
    if (name.contains("network") || name.contains("ethernet")) return QStringLiteral("network-wired");
    if (name.contains("cpu") || name.contains("processor")) return QStringLiteral("cpu");
    if (name.contains("sound") || name.contains("audio") || name.contains("kmix")) return QStringLiteral("audio-card");
    if (name.contains("usb") || name.contains("removable")) return QStringLiteral("usb-creator");
    if (name.contains("keyboard")) return QStringLiteral("keyboard");
    if (name.contains("mouse") || name.contains("pointing")) return QStringLiteral("mouse");
    if (name.contains("phone") || name.contains("portable") || name.contains("ipad") || name.contains("ipod")) return QStringLiteral("smartphone");
    if (name.contains("printer")) return QStringLiteral("gnome-dev-printer");
    if (name.contains("camera")) return QStringLiteral("camera");
    if (name.contains("security") || name.contains("firmware")) return QStringLiteral("security-high");
    return QStringLiteral("computer");
}

inline QIcon resolve(const QString &raw)
{
    QIcon icon = exact(normalized(raw));
    if (icon.isNull()) icon = exact(mapped(raw));
    if (icon.isNull()) icon = exact(QStringLiteral("computer"));
    if (icon.isNull()) qWarning().noquote() << "[Aero7 Icons] Missing pack icon:" << raw;
    return icon;
}

} // namespace Aero7DeviceIcons

inline QIcon resolveIcon(const QString &name) { return Aero7DeviceIcons::resolve(name); }
inline QIcon tryIconName(const QString &name) { return Aero7DeviceIcons::resolve(name); }
inline QIcon themeIcon(std::initializer_list<const char *> names)
{
    for (const char *candidate : names) {
        const QIcon icon = Aero7DeviceIcons::exact(Aero7DeviceIcons::normalized(QString::fromLatin1(candidate)));
        if (!icon.isNull()) return icon;
    }
    return Aero7DeviceIcons::resolve(names.size() ? QString::fromLatin1(*names.begin()) : QStringLiteral("computer"));
}
inline QIcon aero7ResourceIcon(const QString &path, const QString &fallback)
{
    const QIcon icon(path);
    if (!icon.isNull()) return icon;
    qWarning().noquote() << "[Aero7 Icons] Missing resource:" << path;
    return Aero7DeviceIcons::resolve(fallback);
}
