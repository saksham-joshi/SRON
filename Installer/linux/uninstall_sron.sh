#!/bin/bash

# Commands to run this script
#  > chmod +x uninstall_sron.sh
#  > sudo bash uninstall_sron.sh


RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m'


echo -e "\n${BLUE}${BOLD}─────────────────────────────────────────────${NC}"
echo -e "${CYAN}${BOLD}        SRON Uninstallation Started          ${NC}"
echo -e "${BLUE}${BOLD}─────────────────────────────────────────────${NC}\n"

echo -e "${YELLOW}⚙️  Preparing to uninstall SRON...${NC}"

# Remove SRON directory
if sudo rm -rf /opt/SRON 2>/dev/null; then
    echo -e "${GREEN}✅ Successfully removed: /opt/SRON${NC}"
else
    echo -e "${RED}❌ Failed to remove: /opt/SRON${NC}"
fi

# Remove binaries
BINARIES=(
    "/usr/local/bin/sronc"
    "/usr/local/bin/sron"
    "/usr/local/bin/sron-docs"
    "/usr/local/bin/sron-FncList"
)

for BIN in "${BINARIES[@]}"; do
    if sudo rm -f "$BIN" 2>/dev/null; then
        echo -e "${GREEN}✅ Removed: ${BIN}${NC}"
    else
        echo -e "${YELLOW}⚠️  Not found: ${BIN}${NC}"
    fi
done

echo -e "\n${GREEN}${BOLD}✨ SRON has been successfully uninstalled.${NC}"
echo -e "${BLUE}Thank you for using SRON! 👋${NC}\n"
