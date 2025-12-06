#pragma once

/* --- Configurazione Sensore (Ploopy Adept) --- */
// Impostazioni standard per alta risoluzione (basato sul tuo file originale)
#define PLOOPY_TRACKBALL_CPI 1600 
#define PLOOPY_DRAGSCROLL_DPI 100  // DPI più bassi durante lo scroll per precisione
#define PLOOPY_DRAGSCROLL_INVERT_Y // Inverte lo scroll verticale se necessario
#define POINTING_DEVICE_HIRES_SCROLL_ENABLE // Abilita scroll fluido ad alta risoluzione

/* --- Configurazione Navigazione Desktop --- */
// Soglia di movimento: quanto devi muovere la sfera per attivare il comando (100-500)
#define NAV_THRESHOLD 450 

// Cooldown: millisecondi di attesa tra un cambio desktop e l'altro
#define NAV_COOLDOWN 300 

/* --- Configurazione Click --- */
#define TAPPING_TERM 200
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_WHEEL_DELAY 0