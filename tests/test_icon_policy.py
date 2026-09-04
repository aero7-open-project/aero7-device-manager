#!/usr/bin/env python3
from pathlib import Path

root = Path(__file__).resolve().parents[1]
errors = []
for path in (root / "src").rglob("*"):
    if path.suffix in {".cpp", ".h", ".qml", ".ui"}:
        for number, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
            if "QIcon::fromTheme" in line:
                errors.append(f"{path.relative_to(root)}:{number}: system-theme icon is forbidden")
for number, line in enumerate((root / "aero7-device-manager.desktop").read_text().splitlines(), 1):
    if line.startswith("Icon=") and line != "Icon=aero7-device-manager":
        errors.append(f"aero7-device-manager.desktop:{number}: launcher icon is not namespaced")
if errors:
    raise SystemExit("\n".join(errors))
