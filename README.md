<div align="center">

  # Aero7 Device Manager
  <i>Hardware management for Aero7</i>

  <p>
    A familiar device-management interface built with Qt 6 and real Linux
    hardware backends through sysfs and procfs.
  </p>

</div>

## Aero7 search integration

The Aero7 fork exposes its real hardware sections to the Start menu without
adding separate application shortcuts:

```sh
aero7-device-manager --list-settings-json
aero7-device-manager --open network-adapters
```

The first command returns the searchable section catalog. The second opens
Device Manager, performs its normal hardware scan, and selects the requested
section when that hardware exists.
> [!NOTE]
> Device Manager is a candidate component of **Aero7 Beta 2, which has NOT
> been publicly released**. Remaining bug fixes and stability tests are ongoing.
> The application
> embeds its approved AeroThemePlasma icon assets, so its Device Manager tree,
> toolbar, dialogs, launcher, and window identity remain consistent when the
> system icon theme changes.

| | | |
|:-------------------------:|:-------------------------:|:-------------------------:|
| <img src="./screenshots/main.png" alt="A list of device categories with some of them expanded."> | <img src="./screenshots/properties.png" alt="A device properties window open, showing information about an AMD GPU"> | <img src="./screenshots/driver.png" alt="The Driver tab of the Properties window, shwoing the version and date of said GPU driver"> |
| <img src="./screenshots/olddriver.png" alt="The same Driver tab of the Properties window, but this time showing an older unmaintained driver's date and version."> | <img src="./screenshots/details.png" alt="The Details tab, shwoing a dropdown with a large text area."> | <img src="./screenshots/resources.png" alt="The Resources tab, shwoing a information about a deviecs resources like IRQ and similar."> |


## Installation and updates

Aero7 Device Manager is installed and updated through the signed
[Aero7 package repository](https://github.com/memegeko/aero7-repo):

```bash
sudo pacman -S aero7-device-manager
```

The package replaces the earlier `linux-devmgmt` identity while preserving it
as a compatibility provider for upgrades.

## Runtime dependencies

On Arch, you need these installed separately. The Nix flake handles all of them automatically.

| Tool | Purpose |
|------|---------|
| `pkexec` | Privilege escalation for enable/disable/uninstall |
| `modinfo` | Driver details |
| `bluetoothctl` | Bluetooth device disconnect |
| `dkms` | *(optional)* DKMS driver management |
| `pacman` | *(optional)* Package date lookup |

## Features

- Full two-level device tree (by type) backed by real sysfs/procfs data
- Per-device Properties dialog with General, Driver, Details, and Resources tabs
- Enable / disable devices via kernel module blacklisting
- Uninstall DKMS drivers
- Update Driver wizard
- Driver Details viewer (`modinfo` output)
- Scan for hardware changes
- Battery levels for AirPods (per pod and case), read on request

## Project relationship

This repository is the maintained Aero7 fork of
[linux-devmgmt](https://github.com/actuallyaridan/linux-devmgmt). Aero7 keeps
the real Linux device backends and upstream license while maintaining its own
application identity, packaging, desktop integration, and visual resources.
