# Port Scanner

A multi-threaded port scanner written in C designed for optimal performance. This tool can scan up to 65,535 ports on a given IP address in under 18 seconds on an Intel i5 processor with 12 threads, using approximately 40% CPU load.

## Features
- **Multi-threaded Scanning**: Utilizes up to `physical thread count * 32` to maximize CPU usage and reduce scan time.
- **IPv4 Support**: Checks only valid IPv4 addresses.
- **Port Range Scanning**: Scans individual ports or a range of ports.
- **Non-blocking Sockets**: Uses non-blocking sockets and `select()` for improved responsiveness.
- **Simple Output**: Displays open ports with a clear message.

## Requirements
- **C Compiler**: GCC or Clang.
- **POSIX-compliant System**: Linux or macOS (Windows support requires Cygwin or WSL).

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/benimoor/portscan.git
   cd portscan
   ```
2. Compile the code:
   ```bash
   make
   ```
3. Run the compiled executable.

## Usage
```bash
./portscan IP [START_PORT] [END_PORT]
```
- `IP`: The target IPv4 address to scan.
- `START_PORT`: The starting port number (default is 1).
- `END_PORT`: The ending port number (default is 65535).

### Example
```bash
./portscan 192.168.1.1 80 100
```
Scans ports 80 to 100 on the IP address 192.168.1.1.

## Code Logic
- The program creates threads based on the number of CPU cores (`physical thread count * 32`).
- Each thread handles a specific portion of the port range.
- Non-blocking sockets and `select()` ensure efficient scanning.
- Open ports are printed with the format `PORT <port_number> OPEN`.

## Performance
- On an Intel i5 processor with 12 physical threads, scanning all 65,535 ports takes approximately **17.3 seconds** with around **40% CPU load**.

## Contributions
Feel free to fork the repository, open issues, and submit pull requests. Contributions to improve the performance and functionality of the scanner are welcome!

## Acknowledgments
- **Libraries Used**: Standard POSIX libraries for socket programming.
- **Inspired By**: Tools like `nmap` and other open-source network scanning utilities.

