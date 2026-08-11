#pragma once

#include <QString>
#include <QVector>

struct DeviceCatalogEntry {
    QString key;
    QString name;
    QString description;
    QString iconName;
};

class DeviceCatalog {
public:
    static const QVector<DeviceCatalogEntry> &entries();
    static const DeviceCatalogEntry *find(const QString &key);
};
