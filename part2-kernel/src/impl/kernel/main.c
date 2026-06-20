#include "print.h"

void kernel_main() {
    //Limpiar la pantalla de los residuos de GRUB
    print_clear();
    
    //Elegir colores
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    
    //Imprimir el texto 
    print_str("Welcome to 64-bit kernel\n");
    
    print_set_color(PRINT_COLOR_LIGHT_GREEN, PRINT_COLOR_BLACK);
    print_str("\nSistema Operativo creado por el grupo de:\n");
    
    //Nombres del grupo
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("- David Torres\n");
    print_str("- Ivan Gualotuña\n");
    print_str("- Andres Guaminga\n");
    print_str("- Francis Acuña\n");
    
    print_set_color(PRINT_COLOR_LIGHT_CYAN, PRINT_COLOR_BLACK);
    print_str("\n[ OK ] Sistema iniciado correctamente en modo 64 bits.\n");
}