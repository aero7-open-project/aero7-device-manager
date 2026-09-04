#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QIcon>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include "DeviceCatalog.h"
#include "MainWindow.h"
#include "ui/IconHelper.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("Aero7 Device Manager");
    app.setApplicationVersion("2.2.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Aero7 Device Manager with real Linux hardware backends");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption catalogOption("list-settings-json",
        "Print the searchable Device Manager section catalog as JSON.");
    QCommandLineOption openOption("open", "Open a Device Manager section.", "section");
    parser.addOption(catalogOption);
    parser.addOption(openOption);
    parser.process(app);

    if (parser.isSet(catalogOption)) {
        QJsonArray catalog;
        for (const DeviceCatalogEntry &entry : DeviceCatalog::entries()) {
            catalog.append(QJsonObject{{"key", entry.key}, {"name", entry.name},
                {"description", entry.description}, {"icon", entry.iconName},
                {"section", "Device Manager"}});
        }
        QTextStream(stdout) << QJsonDocument(catalog).toJson(QJsonDocument::Compact) << '\n';
        return 0;
    }

    QString initialCategory;
    if (parser.isSet(openOption)) {
        const DeviceCatalogEntry *entry = DeviceCatalog::find(parser.value(openOption));
        if (!entry) {
            QTextStream(stderr) << "Unknown Device Manager section: "
                                << parser.value(openOption) << '\n';
            return 2;
        }
        initialCategory = entry->name;
    }
    app.setWindowIcon(aero7ResourceIcon(
        QStringLiteral(":/aero7/icons/app/aero7-device-manager.png"),
        QStringLiteral("device-manager")));
    MainWindow w(initialCategory);
    w.show();
    return app.exec();
}
