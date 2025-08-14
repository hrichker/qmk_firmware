# MCU / board
MCU       = RP2040
BOARD     = KB2040
BOOTLOADER = rp2040

# Core firmware options
DUPLEX_MATRIX_ENABLE = yes
# Enable only features you actually need
BOOTMAGIC_ENABLE = no
MOUSEKEY_ENABLE  = no
EXTRAKEY_ENABLE  = yes
CONSOLE_ENABLE   = no
COMMAND_ENABLE   = no
NKRO_ENABLE      = no
