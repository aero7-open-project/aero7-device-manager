#include "DeviceCatalog.h"

const QVector<DeviceCatalogEntry> &DeviceCatalog::entries()
{
    static const QVector<DeviceCatalogEntry> catalog{
        {"batteries", "Batteries", "View batteries and power-source hardware.", "kded5"},
        {"bluetooth-radios", "Bluetooth Radios", "View Bluetooth radio hardware and drivers.", "network-bluetooth"},
        {"disk-drives", "Disk Drives", "View physical disk devices and drivers.", "drive-harddisk"},
        {"display-adapters", "Display Adapters", "View graphics adapters and kernel drivers.", "video-display"},
        {"optical-drives", "DVD/CD-ROM Drives", "View optical drives and media hardware.", "media-optical"},
        {"game-controllers", "Game Controllers", "View game controllers and input drivers.", "input-gaming"},
        {"human-interface-devices", "Human Interface Devices", "View HID hardware and drivers.", "input_devices_settings"},
        {"ide-controllers", "IDE ATA/ATAPI Controllers", "View IDE and ATA storage controllers.", "drive-harddisk"},
        {"keyboards", "Keyboards", "View keyboard hardware and input drivers.", "input-keyboard"},
        {"pointing-devices", "Mice and Other Pointing Devices", "View mice, touchpads, and pointing devices.", "input-mouse"},
        {"monitors", "Monitors", "View connected displays and monitor information.", "video-display"},
        {"network-adapters", "Network Adapters", "View wired, wireless, and virtual network adapters.", "network-card"},
        {"portable-devices", "Portable Devices", "View connected portable devices.", "smartphone"},
        {"processors", "Processors", "View installed processors and CPU devices.", "cpu"},
        {"security-devices", "Security Devices", "View TPM and other security hardware.", "drive-harddisk-encrypted"},
        {"sound-video-game", "Sound, Video and Game Controllers", "View audio and multimedia controllers.", "kmix"},
        {"storage-controllers", "Storage Controllers", "View storage controllers and kernel drivers.", "drive-harddisk"},
        {"system-devices", "System Devices", "View platform, ACPI, RTC, and system hardware.", "computer"},
        {"usb-controllers", "Universal Serial Bus Controllers", "View USB host controllers.", "drive-removable-media-usb"},
        {"usb-devices", "Universal Serial Bus Devices", "View attached USB devices.", "drive-removable-media-usb"},
        {"unknown-devices", "Unknown Devices", "Find hardware that could not be identified.", "dialog-question"},
        {"disabled-devices", "Disabled Devices", "View hardware disabled through driver configuration.", "dialog-cancel"},
    };
    return catalog;
}

const DeviceCatalogEntry *DeviceCatalog::find(const QString &key)
{
    for (const DeviceCatalogEntry &entry : entries()) {
        if (entry.key == key) return &entry;
    }
    return nullptr;
}
