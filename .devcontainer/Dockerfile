FROM mcr.microsoft.com/devcontainers/base:ubuntu-22.04

# Install required system dependencies
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    python3 \
    python3-pip \
    python3-venv \
    git \
    wget \
    curl \
    build-essential \
    ca-certificates \
    libusb-1.0-0 \
    udev \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*

# Create vscode user if not exists
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Install PlatformIO Core
RUN pip3 install -U platformio

# Add udev rules for USB devices (ESP32, nRF52, etc.)
RUN echo 'SUBSYSTEM=="usb", MODE="0666"' > /etc/udev/rules.d/99-platformio.rules

# Set up workspace
USER $USERNAME
WORKDIR /workspace

# Install PlatformIO platforms and tools (pre-install common platforms)
RUN pio platform install espressif32 && \
    pio platform install nordicnrf52

# Verify installation
RUN pio system info
