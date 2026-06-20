#include "print.h"

void kernel_main() {
    // 1. Limpiar la pantalla de los residuos de GRUB
    print_clear();
    
    // 2. Elegir colores (ej: texto amarillo sobre fondo negro)
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    
    // 3. Imprimir el texto requerido por la rúbrica
    print_str("Welcome to 64-bit kernel\n");
    
    print_set_color(PRINT_COLOR_LIGHT_GREEN, PRINT_COLOR_BLACK);
    print_str("\nSistema Operativo creado por el grupo de:\n");
    
    // Puedes añadir los nombres del resto de tus amigos aquí abajo
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("- David Torres\n");
    print_str("- Integrante 2\n");
    print_str("- Integrante 3\n");
    print_str("- Integrante 4\n");
    
    print_set_color(PRINT_COLOR_LIGHT_CYAN, PRINT_COLOR_BLACK);
    print_str("\n[ OK ] Sistema iniciado correctamente en modo 64 bits.\n");
}