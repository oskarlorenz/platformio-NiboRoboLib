/*
  NIBO2 library for ARDUINO
  License: BSD-License
  (c) 2013 by Nils Springob, nicai-systems
*/

/*! @file    NIBO_GFX.h
 *  @brief   NIBO2 library for ARDUINO
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2013-09-02
 */


#ifndef __NIBO_GFX_H__
#define __NIBO_GFX_H__

#ifdef ARDUINO
#include <Print.h>
#else
class Print {
  virtual size_t write(uint8_t) {return 0;}
  virtual size_t write(const uint8_t *buffer, size_t size) {return 0;}
};
#endif


enum {
  GFX_JAM1 = 0,
  GFX_JAM2 = 1,
  GFX_COMP = 2,
  GFX_JAM1_INV = 4,
  GFX_JAM2_INV = 5,
  GFX_COMP_INV = 6
};

enum {
  GFX_TYPE_NONE     = 0,
  GFX_TYPE_DEM12064 = 2,
  GFX_TYPE_RG12064  = 3
};  


class GFX_term: public Print {
  public:
    /*!
     * Gibt das Zeichen im Terminal-Modus aus.
     */
    virtual size_t write(uint8_t);

    /*!
     * Gibt den Text im Terminal-Modus aus.
     * @param buffer String im RAM
     * @param size Länge des Textes
     */
    virtual size_t write(const uint8_t *buffer, size_t size);

    /*!
     * Löscht den Bildschirm und setzt den Terminal-Cursor an die Position (0/0).
     */
    void clear();
    
    /*!
     * Löscht die aktuelle Zeile, die Curtsorposition bleibt unverändert.
     */
    void clearLine();

    /*!
     * Setzt den Terminal-Cursor an die Position (0/0).
     */
    void home();    
    
    /*!
     * Setzt den Terminal-Cursor an die angegebene Position.
     * @param col Spalte
     * @param col Zeile
     */
    void cursor(unsigned char col, unsigned char row);

    /*!
     * Verschiebt den Terminal-Cursor relativ zur aktuellen Position.
     * @param col Spalte relativ (+ rechts / - links)
     * @param col Zeile relativ (+ runter / - hoch)
     */
    void cursorRel(signed char col, signed char row);

    /*!
     * Setzt den Terminal-Cursor an die angegebene Spalte. Die Zeile bleibt unverändert.
     * @param col Spalte
     */
    void cursorCol(unsigned char col);   

    /*!
     * Setzt den Terminal-Cursor an die angegebene Zeile. Die Spalte bleibt unverändert.
     * @param col Spalte
     */
    void cursorRow(unsigned char row);
    
    /*!
     * Scrollt den Bildschirm um die angegebene Zeilenanzahl.
     * @param lines Anzahl der Zeilen
     */
    void scroll(unsigned char lines);    
};

class GFX_class: public Print {
  public:
    GFX_term term;
    
    GFX_class();
    
    /*!
     * Initialisiert das Grafik Display. 
     */
    void begin(unsigned char type = GFX_TYPE_RG12064);

    /*!
     * Gibt das Zeichen im Grafik-Modus aus.
     */
    virtual size_t write(uint8_t);

    /*!
     * Gibt den Text im Grafik-Modus aus.
     * @param buffer String im RAM
     * @param size Länge des Textes
     */
    virtual size_t write(const uint8_t *buffer, size_t size);
    
    /*!
     * Liefert aktuelle X Position des Grafikcursors
     */
    unsigned char get_x();
    
    /*!
     * Liefert aktuelle Y Position des Grafikcursors
     */
    unsigned char get_y();
    
    /*!
     * Setzt Grafikcursor auf angegebene Position
     * @param x X-Position des Cursors (0..127)
     * @param y Y-Position des Cursors (0..63)
     */
    void move(unsigned char x, unsigned char y);
    
    /*!
     * Setzt den Zeichenmodus
     * @param mode Zeichenmodus
     */
    void draw_mode(unsigned char mode);
    
    /*!
     * Fulle gesamten Bildschirm mit angegebener Bitfolge
     * @param val Bitmaske
     */
    void fill(unsigned char val);
    
    /*!
     * Liefert Breite in Pixeln für angegebenes Zeichen
     * @param ch Zeichen
     * @return Breite in Pixeln
     */
    unsigned char char_width(char ch);
    
    /*!
     * Liefert Breite in Pixeln für Nullterminierten String
     * @param txt Nullterminierter String
     * @return Breite in Pixeln
     */
    unsigned char text_width(const char *txt);
    
    /*!
     * Liefert Breite in Pixeln für Nullterminierten String im FLASH
     * @param txt Nullterminierter String im FLASH
     * @return Breite in Pixeln
     */
    //unsigned char text_width_P(PGM_P txt);
    
    /*!
     * Gibt angegebenes Zeichen an der aktuellen Grafikposition aus.
     * @param c Zeichen
     */
    void print_char(char c);
    
    /*!
     * Gibt angegebenen Nullterminierten String an der aktuellen Grafikposition aus.
     * @param txt Nullterminierter String
     */
    void print_text(const char *txt);
    
    /*!
     * Gibt angegebenen Nullterminierten String im FLASH an der aktuellen Grafikposition aus.
     * @param txt Nullterminierter String im FLASH
     */
    //void print_text_P(PGM_P txt);
    
    /*!
     * Gibt angegebenes XBM Bild im RAM an der aktuellen Grafikposition aus.
     * @param width Breite
     * @param height Höhe
     * @param data XBM Daten im RAM
     */
    void draw_xbm(unsigned char width, unsigned char height, unsigned char * data);
    
    /*!
     * Gibt angegebenes XBM Bild im Flash an der aktuellen Grafikposition aus.
     * @param width Breite
     * @param height Höhe
     * @param data XBM Daten im Flash
     */
    //void draw_xbm_P(unsigned char width, unsigned char height, PGM_P data);
    
    /*!
     * Setzt den Proportionalitaetsmodus.
     * @param prop 0=fix, 1=Proportional
     */
    void set_proportional(unsigned char prop);
    
    /*!
     * Liefert den aktuellen Proportionalitaetsmodus.
     * @return 0=fix, 1=Proportional
     */
    unsigned char get_proportional(void);
    
    /*!
     * Zeichnet eine horizontale Linie von der aktuellen Position nach rechts
     * @param length Länge der Linie
     */
    void hline(unsigned char length);
    
    /*!
     * Zeichnet eine vertikale Linie von der aktuellen Position nach unten
     * @param length Länge der Linie
     */
    void vline(unsigned char length);
    
    /*!
     * Zeichnet ein Rechteck.
     * @param width Breite
     * @param height Höhe
     */
    void box(unsigned char width, unsigned char height);
    
    /*!
     * Zeichnet eine Linie zur angegebenen Position.
     * @param x X-Position des Zielpunktes (0..127)
     * @param y Y-Position des Zielpunktes (0..63)
     */
    void lineTo(unsigned char x, unsigned char y);
    
    /*!
     * Setzt bzw. löscht den Pixel an der aktuellen Position.
     * @param value 0: löschen, anderer Wert: setzen
     */
    void pixel(unsigned char value);
    
};


extern GFX_class GFX;



#endif


