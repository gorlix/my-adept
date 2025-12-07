# Ploopy Adept - Firmware Custom

Un firmware QMK avanzato progettato per il trackball **Ploopy Adept**.
Ottimizzato per power user **Linux (KDE Plasma/Wayland)**, con un focus su navigazione fluida, controllo gestuale e precisione assoluta.

## Funzionalità Principali

### Motore di Movimento Avanzato
- **Accelerazione Quadratica**: Sostituisce l'accelerazione lineare standard con una curva quadratica personalizzata (`speed^2`).
    - *Bassa Velocità*: Tracciamento ultra-preciso 1:1 per editing pixel-perfect.
    - *Alta Velocità*: Boost esponenziale che permette di attraversare schermi 4K con un singolo "flick".
- **Base 1600 CPI**: Logica nativa ad alta risoluzione per la massima reattività.

### Scrolling Fluido ad Alta Risoluzione
- **Accumulatori Float**: I calcoli di scorrimento utilizzano matematica in virgola mobile per una precisione sub-pixel.
- **Sensibilità Scroll**: Calibrata a **0.5x** indipendentemente dai DPI del cursore, garantendo una navigazione web estremamente fluida ("buttery smooth").
- **Blocco Assi Intelligente (Isteresi)**:
    - Rileva automaticamente se stai scorrendo in Verticale o Orizzontale.
    - "Blocca" l'asse per prevenire derive diagonali accidentali.
    - Utilizza memoria di **Isteresi**: una volta bloccato, rimane tale finché non forzi intenzionalmente il cambio direzione.
 
### Controlli Gestuali e Zoom
- **Zoom Fluido / Emulazione Pinch**:
    - Tieni premuto il tasto **Top Left** per entrare in modalità Zoom.
    - Emula `Ctrl + Shift + Scroll` (standard Libinput Pinch Zoom).
    - Funziona nativamente nei browser (Firefox/Chrome) e app di design per uno zoom fluido reale.

### Navigazione Desktop e Media
- **Desktop Switcher**: Tieni premuto **Bot Right** (`NAV`) e lancia la sfera a Sinistra/Destra per cambiare desktop virtuali (standard KDE).
- **Mission Control**: Tieni `NAV` e lancia Su/Giù per la panoramica finestre.
- **Media Mode**: Tieni premuto **Top Right** (`MEDIA`) per controllare Volume (Su/Giù) o Luminosità (Sinistra/Destra).

---

## Layout Tasti

| Posizione | Etichetta | Tap (Click) | Hold (Funzione) | Doppio Tap |
| :--- | :--- | :--- | :--- | :--- |
| **Top Left** | `ZOOM` | Click Centrale | **Mod. Pinch Zoom** | - |
| **Mid Left** | `SCROLL` | Click Centrale | **Mod. Drag Scroll** | **Home** (2x) / **End** (3x) |
| **Bot Left** | `LMB` | Click Sinistro | - | - |
| **Top Right** | `MEDIA` | Indietro (Btn 4) | **Layer Media** | **Layer Playback** |
| **Mid Right** | `RMB` | Click Destro | - | - |
| **Bot Right** | `NAV` | Avanti (Btn 5) | **Navigazione Desktop** | - |

### Layer Playback (Top Right 2x)
Controlli dedicati per la fruizione di video/musica.
- **Sfera**: Cursore Standard.
- **Top Left**: Indietro 10s.
- **Mid Right**: Avanti 10s.
- **Bot Left**: Play/Pausa.
- **Top Right**: Esci dal Layer.

---

## Dettagli Tecnici

- **Poll Rate**: 1ms (1000Hz) per una risposta istantanea.
- **Libreria Matematica**: Utilizza `<math.h>` per curve di accelerazione complesse.
- **Ottimizzazione Wayland**: Tuning specifico per eventi di scroll ad alta risoluzione nei compositor Wayland.

## Compilazione

Questo firmware include logica C complessa. Compilare usando la CLI standard di QMK:

```bash
qmk compile -kb ploopyco/madromys -km gorlix
```

*Nota: Richiede QMK Firmware 0.22+*
