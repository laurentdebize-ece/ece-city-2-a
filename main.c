#include "compteur.h"
#include "menuPrincipal.h"


int main() {
    //Affichage console en mode pleine ecran
    keybd_event(VK_MENU, 0x38, 0, 0); //Appuie sur ALT
    keybd_event(VK_RETURN, 0x1c, 0, 0); //Appuie ENTREE
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0); // Relache ENTREE
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0); //Relache ALT
    //Fin Affichage console en mode pleine ecran

    menuPrincipal();

    return 0;
}