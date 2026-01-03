#!/bin/bash
set -e

# execute: sed -i 's/\r//' install_sron.sh

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}=========================================${NC}"
echo -e "${BLUE}   SRON Programming Language Installer   ${NC}"
echo -e "${BLUE}              Version 2.3                ${NC}"
echo -e "${BLUE}=========================================${NC}"
echo ""

#====== Check if running as root
if [ "$EUID" -ne 0 ]; then 
    echo -e "${RED}❌ Error: This installer must be run with sudo privileges${NC}"
    echo "Please run: sudo bash $0"
    exit 1
fi

#====== Detect architecture
ARCH=$(uname -m)
echo -e "${BLUE}🔍 Detected architecture: ${ARCH}${NC}"

if [ "$ARCH" != "x86_64" ]; then
    echo -e "${RED}❌ Error: SRON only supports x86_64 (x64) architecture${NC}"
    echo "Your system architecture is: $ARCH"
    exit 1
fi

echo -e "${GREEN}✓ Architecture compatible${NC}"
echo ""


SRON_VERSION="2.3"
SRON_TAR_FILE_NAME="SRON-v${SRON_VERSION}-linux-x64.tar.gz"
DOWNLOAD_URL="https://github.com/saksham-joshi/SRON/releases/download/SRON-v${SRON_VERSION}/${SRON_TAR_FILE_NAME}"
INSTALL_DIR="/opt/SRON"
TEMP_DIR="/tmp/sron-install-$$"

#===== Check if SRON is already installed
if [ -d "$INSTALL_DIR" ]; then
    echo -e "${YELLOW}⚠️  SRON is already installed at $INSTALL_DIR${NC}"
    read -p "Do you want to reinstall? [y/N]: " reinstall
    if [[ ! "$reinstall" =~ ^[Yy]$ ]]; then
        echo "Installation cancelled."
        exit 0
    fi
    echo -e "${BLUE}🗑️  Removing old installation...${NC}"
    rm -rf "$INSTALL_DIR"
fi

#===== Creating temp directory
mkdir -p "$TEMP_DIR"
cd "$TEMP_DIR"

# Download
echo -e "${BLUE}📥 Downloading SRON v${SRON_VERSION}...${NC}"
if command -v curl &> /dev/null; then
    if curl -L -f -o "${SRON_TAR_FILE_NAME}" "$DOWNLOAD_URL" --progress-bar; then
        echo -e "${GREEN}✓ Download completed${NC}"
    else
        echo -e "${RED}❌ Error: Failed to download SRON. Please connect to the internet and if you are connected, make sure you are logged in!${NC}"
        rm -rf "$TEMP_DIR"
        exit 1
    fi
elif command -v wget &> /dev/null; then
    if wget -O "${SRON_TAR_FILE_NAME}" "$DOWNLOAD_URL" --show-progress -q; then
        echo -e "${GREEN}✓ Download completed${NC}"
    else
        echo -e "${RED}❌ Error: Failed to download SRON. Please connect to the internet and if you are connected, make sure you are logged in!${NC}"
        rm -rf "$TEMP_DIR"
        exit 1
    fi
else
    echo -e "${RED}❌ Error: Neither curl nor wget found${NC}"
    echo "Please install curl or wget and try again"
    rm -rf "$TEMP_DIR"
    exit 1
fi

#====== Extracting the downloaded tarball file
echo ""
echo -e "${BLUE}📦 Extracting files...${NC}"

tar -xzf ${SRON_TAR_FILE_NAME}

echo -e "${GREEN} Verifying files ...${NC}"

for f in sron sronc sron-docs sron-FncList Installer/uninstall_sron.sh; do
    if [ ! -f "$f" ]; then
        echo -e "${RED}❌ Error: cannot locate '$f' in the extracted tarball. Please report this issue on GitHub at 'https://github.com/saksham-joshi/SRON/issues'${NC}"
        rm -rf "$TEMP_DIR"
        exit 1
    fi
done

if [ ! -d meta ]; then
    echo -e "${RED}❌ Error: cannot locate 'meta/' in the tarball. Please report this issue on GitHub at 'https://github.com/saksham-joshi/SRON/issues'${NC}"
    rm -rf "$TEMP_DIR"
    exit 1
fi 

echo -e "${GREEN}✅ File verification done! ${NC}"


#====== Creating installation directory
echo -e "${BLUE}🔧 Installing SRON to $INSTALL_DIR...${NC}"
mkdir -p "$INSTALL_DIR"

#====== Move files to installation directory
mv sronc "$INSTALL_DIR/sronc"
mv sron "$INSTALL_DIR/sron"
mv sron-docs "$INSTALL_DIR/sron-docs"
mv sron-FncList "$INSTALL_DIR/sron-FncList"
mv meta "$INSTALL_DIR"
mv Installer/uninstall_sron.sh "$INSTALL_DIR/uninstall_sron.sh"

#====== Set executable permissions
chmod +x "$INSTALL_DIR/sronc"
chmod +x "$INSTALL_DIR/sron"
chmod +x "$INSTALL_DIR/sron-docs"
chmod +x "$INSTALL_DIR/sron-FncList"
chmod +x "$INSTALL_DIR/uninstall_sron.sh"

echo -e "${GREEN}✓ Files installed successfully${NC}"

#====== Cleanup temp directory
cd /
rm -rf "$TEMP_DIR"

#====== Create symlinks in /usr/local/bin for system-wide access
echo ""
echo -e "${BLUE}🔗 Creating symbolic links in /usr/local/bin...${NC}"

ln -sf "$INSTALL_DIR/sronc" /usr/local/bin/sronc
ln -sf "$INSTALL_DIR/sron" /usr/local/bin/sron
ln -sf "$INSTALL_DIR/sron-docs" /usr/local/bin/sron-docs
ln -sf "$INSTALL_DIR/sron-FncList" /usr/local/bin/sron-FncList

echo -e "${GREEN}✓ Symbolic links created${NC}"

#====== Verify installation
echo ""
echo -e "${BLUE}🧪 Verifying installation...${NC}"

if [ -x "$INSTALL_DIR/sronc" ] && [ -x "$INSTALL_DIR/sron" ]; then
    echo -e "${GREEN}✓ Installation verified${NC}"
else
    echo -e "${RED}❌ Warning: Some executables may not be properly installed${NC}"
    exit 1
fi

#====== Print success message
echo ""
echo -e "${BLUE}Installation details:${NC}"
echo "  • Installation directory: $INSTALL_DIR"
echo "  • Executables:"
echo "      - sronc        (SRON compiler)"
echo "      - sron         (SRON interpreter)"
echo "      - sron-docs    (SRON documentation)"
echo "      - sron-FncList (used by compiler, don't call it!)"
echo ""
echo -e "${BLUE}Directory structure:${NC}"
echo "  $INSTALL_DIR"
echo "  ├── meta/"
echo "  │   ├── Errors/"
echo "  │   └── Exceptions/"
echo "  ├── sronc"
echo "  ├── sron"
echo "  ├── sron-docs"
echo "  └── sron-FncList"
echo ""
echo -e "${GREEN}=========================================${NC}"
echo -e "${GREEN}✅ SRON installed successfully!${NC}"
echo -e "${GREEN}=========================================${NC}"
echo ""
echo -e "${GREEN}You can now use SRON from anywhere!${NC}"
echo -e "${BLUE}Try running:${NC} sronc --version"
echo ""

#======= Display uninstall instructions
echo -e "${YELLOW}To uninstall SRON, run:${NC}"
echo -e "${BLUE} sudo bash $INSTALL_DIR/uninstall_sron.sh ${NC}"
echo ""