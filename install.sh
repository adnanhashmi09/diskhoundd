#!/bin/bash

# Compile the source code
make
echo "🔧 Compilation completed."

# Get absolute path to the icon file
icon_path_abs="$(realpath assets/diskhoundd-small.png)"

# Update icon_path in configuration file if it exists
if grep -q '^icon_path' diskhoundd.cfg; then
    sed -i "s|^icon_path.*|icon_path = $icon_path_abs|" diskhoundd.cfg
    echo "🖼️ Icon path updated in diskhoundd.cfg."
fi

# Install the binary
install -m 755 ./build/diskhoundd /usr/bin/diskhoundd
echo "💾 diskhoundd binary installed."

# Install the systemd service file
install -m 644 diskhoundd.service /etc/systemd/system/diskhoundd.service
echo "🛠️ Registering diskhoundd as a systemd service."

install -m 644 session-local.conf /etc/dbus-1/session-local.conf
echo "🚌 Registering dbus configuration."

# Create directory for configuration file if it doesn't exist
mkdir -p /etc/diskhoundd

# Install the default configuration file if it doesn't exist
if [ ! -f /etc/diskhoundd/diskhoundd.cfg ]; then
    echo "📄 diskhoundd.cfg file doesn't exist."
    install -m 644 diskhoundd.cfg /etc/diskhoundd/diskhoundd.cfg
    echo "📝 /etc/diskhoundd/diskhoundd.cfg file created."
else
    echo "📄 diskhoundd.cfg file already exists."
fi

# Reload systemd to load the new service
echo "🔄 Reloading systemd daemon."
systemctl daemon-reload

# Enable and start the service
echo "🚀 Enabling diskhoundd service."
systemctl enable diskhoundd
echo "🏃 Starting diskhoundd service."
systemctl start diskhoundd

echo "✅ Diskhoundd installed successfully!"
