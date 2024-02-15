# Diskhoundd

Diskhoundd is a Linux daemon designed to monitor disk space usage and provide alerts when the disk space falls below a certain threshold. It can be configured via a configuration file and can watch multiple mount paths for disk space utilization.

## Installation 🛠️

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/diskhoundd.git
   ```

2. Compile the source code:

   ```bash
   cd diskhoundd
   make
   ```

3. Install the binary and configuration file:

   ```bash
   sudo make install
   ```

4. Enable diskhoundd daemon:

   ```bash
   sudo systemctl enable diskhoundd.service 
   sudo systemctl start diskhoundd.service 
   ```

## Manual installation 🚀

To run Diskhoundd, use the following command:

```bash
diskhoundd -c /path/to/diskhoundd.cfg /path/to/mount/point1 /path/to/mount/point2 ...
```

### Configuration File Options ⚙️

The configuration file (default name: `diskhoundd.cfg`) can specify the following options:

- `log_file_path`: Path to the log file (default: `/var/log/diskhoundd.log`)
- `icon_path`: Path to the icon file for alerts (default: `./assets/diskhound-small.png`)
- `critical_disk_perc`: Critical disk percentage threshold (default: `20`)

### Example Configuration File

```ini
log_file_path = /var/log/diskhoundd.log
icon_path = ./assets/diskhound-small.png
critical_disk_perc = 20
```

### Systemd Unit 🐧

Diskhoundd can be run as a systemd service using the provided `diskhoundd.service` file.

1. Copy `diskhoundd.service` to systemd service directory:

   ```bash
   sudo cp diskhoundd.service /etc/systemd/system/
   ```

2. Reload systemd to load the new service:

   ```bash
   sudo systemctl daemon-reload
   ```

3. Enable and start the service:

   ```bash
   sudo systemctl enable diskhoundd
   sudo systemctl start diskhoundd
   ```
