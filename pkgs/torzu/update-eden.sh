#!/usr/bin/env bash
set -euo pipefail

# Update script for eden-emulator AppImage
# This script fetches the latest nightly build from Eden and updates the package definition

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
NIX_FILE="$SCRIPT_DIR/eden_appimage.nix"

echo "Fetching latest Eden emulator nightly build..."

# Fetch the latest release from the Forgejo API
RELEASE_DATA=$(curl -s "https://git.eden-emu.dev/api/v1/repos/eden-ci/nightly/releases?limit=1" 2>/dev/null | jq '.[0]' 2>/dev/null)

if [ -z "$RELEASE_DATA" ] || [ "$RELEASE_DATA" = "null" ]; then
    echo "Error: Could not fetch latest release from https://git.eden-emu.dev/api/v1/repos/eden-ci/nightly/releases"
    exit 1
fi

# Extract tag name (format: v{timestamp}.{commit})
TAG_NAME=$(echo "$RELEASE_DATA" | jq -r '.tag_name')
echo "Latest release: $TAG_NAME"

# Extract commit hash from tag (last part after the dot)
COMMIT=$(echo "$TAG_NAME" | grep -oP '[a-f0-9]+$')

# Construct the download URL for Steam Deck PGO build
DOWNLOAD_URL="https://nightly.eden-emu.dev/${TAG_NAME}/Eden-Linux-${COMMIT}-steamdeck-clang-pgo.AppImage"

echo "Download URL: $DOWNLOAD_URL"

# Prefetch the AppImage to the Nix store
echo "Prefetching AppImage to Nix store..."
PREFETCH_OUTPUT=$(nix-prefetch-url --type sha256 "$DOWNLOAD_URL" 2>&1)
PREFETCH_EXIT=$?
if [ $PREFETCH_EXIT -ne 0 ]; then
    echo "Error: Failed to prefetch AppImage from $DOWNLOAD_URL"
    echo "Output: $PREFETCH_OUTPUT"
    exit 1
fi

# Extract just the hash (last line of output, which is the base64 hash without prefix)
NEW_SHA256=$(echo "$PREFETCH_OUTPUT" | tail -n 1 | tr -d ' ')

# Validate hash looks reasonable (should be base64)
if ! echo "$NEW_SHA256" | grep -qE '^[A-Za-z0-9+/=]+$'; then
    echo "Error: Invalid hash format: $NEW_SHA256"
    exit 1
fi

echo "New SHA256: sha256-$NEW_SHA256"
echo "File is now in the Nix store!"

# Update the nix file
echo "Updating $NIX_FILE..."

# Escape special characters in DOWNLOAD_URL for sed
ESCAPED_URL=$(printf '%s\n' "$DOWNLOAD_URL" | sed -e 's/[\/&]/\\&/g')

# Replace the URL - use a more specific pattern to avoid unintended replacements
sed -i "s|url = \"https://nightly\.eden-emu\.dev/v[^/]*/[^\"]*\"|url = \"$ESCAPED_URL\"|" "$NIX_FILE"

# Replace the SHA256 hash - match the complete line with proper anchoring
sed -i "s/sha256 = \"sha256-[^\"]*\";/sha256 = \"sha256-$NEW_SHA256\";/" "$NIX_FILE"

# Verify the changes were made
if ! grep -q "sha256 = \"sha256-$NEW_SHA256\"" "$NIX_FILE"; then
    echo "Error: Failed to update hash in $NIX_FILE"
    exit 1
fi

if ! grep -q "$DOWNLOAD_URL" "$NIX_FILE"; then
    echo "Error: Failed to update URL in $NIX_FILE"
    exit 1
fi

echo "✓ Update complete!"
echo ""
echo "Changes made:"
echo "  URL: $DOWNLOAD_URL"
echo "  SHA256: sha256-$NEW_SHA256"
echo ""
echo "File is already cached in the Nix store, so builds will be fast!"
echo ""
echo "Please verify the changes and test the package:"
echo "  nix build '.#eden-emu' --dry-run"
