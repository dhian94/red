/* 
 * File:   main.cpp
 * Author: Nahdhiana
 * 
 * Nama         : Mohammad Nahdhiana Hasmi
 * NIM          : 132410101056
 * Mata Kuliah  : Pemrograman Grafis
 * Judul        : THE RED CATCHER
 * 
 */

#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<stdarg.h> 
#include<GL/glut.h>
#include<cstdlib>
#include<math.h>
#include <iostream>

bool awal = true;
bool mulai = true;
bool gameOver = false;
bool menang = false;
bool objekDatang = true;
bool bomDatang = true;
bool gerakPeluru = false;
bool pause = false;

float x_player = 0;
int y_player = 0;
int tengah = 325; //posisi tengah sumbu x
int posisiObjekX = 0; //posisiX awal objek
int posisiObjekY = 250; //posisiX awal objek
float tembak = 0;

float posisiBomX = 0;
float posisiBomY = 350;
float awan1x = 0;
float awan2x = 0;
int nilai = 10; //variabel untuk menyimpan nilai/skor yang didapat pemain
const double PI = 3.141592653589793;
int i;
void *font = GLUT_BITMAP_HELVETICA_18;
char arraySkor[2] = {0};

void tulis(int x, int y, char *string) {//method untuk menulis karakter/kata/kalimat dilayar
    glRasterPos2f(x, y); //syntax untuk menentukan posisi penulisan raster di layar
    int len = (int) strlen(string); //menentukan panjang char yg didapat dari parameter utk digunakan dalam perulangan
    for (int i = 0; i < len; i++) { //for mengulang penulisan karakter yg awalnya berupa char*, dengan satu-persatu dicetak
        glutBitmapCharacter(font, string[i]); //mencetak array tiap karakter
    }
}

void Lingkaran(int jari2, int jumlah_titik, int x_tengah, int y_tengah) {//method membuat lingkaran untuk awan, bom, peluru, dan matahari
    glBegin(GL_POLYGON);
    for (i = 0; i <= 360; i++) {
        float sudut = i * (2 * PI / jumlah_titik);
        float x = x_tengah + jari2 * cos(sudut);
        float y = y_tengah + jari2 * sin(sudut);
        glVertex2f(x, y);
    }
}

void player() {//membuat pemain/aktor/player
    //kepala
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 0);
    glVertex2f(370, 5);
    glVertex2f(345, 25);
    glVertex2f(345, 50);
    glVertex2f(350, 55);
    glVertex2f(400, 55);
    glVertex2f(405, 50);
    glVertex2f(405, 25);
    glVertex2f(375, 5);
    glEnd();

    //mata kiri
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(370, 45 + y_player);
    glVertex2f(355, 45 + y_player);
    glVertex2f(355, 25 + y_player);
    glVertex2f(370, 25 + y_player);
    glEnd();

    //mata kanan 
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(380, 45 + y_player);
    glVertex2f(395, 45 + y_player);
    glVertex2f(395, 25 + y_player);
    glVertex2f(380, 25 + y_player);
    glEnd();

    //bola mata kiri
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f(370, 40 + y_player);
    glVertex2f(360, 40 + y_player);
    glVertex2f(360, 25 + y_player);
    glVertex2f(370, 25 + y_player);
    glEnd();

    //bola mata kanan 
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f(380, 40 + y_player);
    glVertex2f(390, 40 + y_player);
    glVertex2f(390, 25 + y_player);
    glVertex2f(380, 25 + y_player);
    glEnd();

    //mulut 
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(360, 20 + y_player);
    glVertex2f(375, 10 + y_player);
    glVertex2f(390, 20 + y_player);
    glEnd();

    //pucuk kepala
    glBegin(GL_QUADS);
    glColor3f(1, 1, 0);
    glVertex2f(380, 55 + y_player);
    glVertex2f(380, 60 + y_player);
    glVertex2f(366, 60 + y_player);
    glVertex2f(366, 55 + y_player);
    glEnd();
    //lingkaran atas
    glColor3f(1, 1, 0);
    Lingkaran(5, 360, 372, 65);
    glEnd();
}

void objekTangkap() {//method untuk membuat gambar objek tembak 
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(222.5, 402.5 + posisiObjekY);
    glVertex2f(210, 412.5 + posisiObjekY);
    glVertex2f(210, 425 + posisiObjekY);
    glVertex2f(212.5, 427.5 + posisiObjekY);
    glVertex2f(237.5, 427.5 + posisiObjekY);
    glVertex2f(240, 425 + posisiObjekY);
    glVertex2f(240, 412.5 + posisiObjekY);
    glVertex2f(225, 402.5 + posisiObjekY);
    glEnd();
    //+ posisiObjekX
}

void bom() {//method untuk membuat objek gambar bom
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS); //membuat sumbu bom
    glVertex2f(252, 325 + posisiBomY);
    glVertex2f(252, 300 + posisiBomY);
    glVertex2f(250, 300 + posisiBomY);
    glVertex2f(250, 325 + posisiBomY);
    glEnd();
    glColor3f(0, 0, 0); //membuat lingkaran bom
    Lingkaran(15, 360, 250, 300 + posisiBomY);
    glEnd();
}

void backgroundLangit() {//membuat background berwarna biru langit
    glBegin(GL_QUADS);
    glColor3f(0, 0.7, 1);
    glVertex2f(0, 250);
    glVertex2f(800, 250);
    glVertex2f(800, 600);
    glVertex2f(0, 600);
    glEnd();
}

void backgroundTanah() {//membuat background berwarna cokelat tanah
    glBegin(GL_QUADS);
    glColor3f(0.37, 0.22, 0.07);
    glVertex2f(0, 0);
    glVertex2f(800, 0);
    glVertex2f(800, 250);
    glVertex2f(0, 250);
    glEnd();
}

void awan1() {//method untuk membuat gambar awan
    glColor3f(1, 1, 1);
    Lingkaran(20, 180, 65 + awan1x, 490);
    Lingkaran(30, 180, 95 + awan1x, 500);
    Lingkaran(20, 180, 125 + awan1x, 500);
    glEnd();
}

void awan2() {//method untuk membuat gambar awan
    glColor3f(1, 1, 1);
    Lingkaran(20, 180, 565 + awan2x, 450);
    Lingkaran(30, 180, 595 + awan2x, 450);
    Lingkaran(20, 180, 625 + awan2x, 450);
    glEnd();
}

void matahari() {//method untuk membuat gambar matahari
    glColor3f(1, 1, 0);
    Lingkaran(25, 360, 400, 550);
    glEnd();
}

void tulisanSkor() {//method untuk membuat tulisan di layar
    sprintf(arraySkor, "%d", nilai);
    glColor3f(0, 0, 0);
    tulis(675, 575, "Score ");
    tulis(730, 575, arraySkor);
    glEnd();
}

void objekRandom() {
    int random = (rand() % 2);
    if (random == 1) {//jika positif
        int random_positif = (rand() % 800);
        posisiObjekX += random_positif;
    } else {//jika negatif
        int random_negatif = (rand() % 800);
        posisiObjekX = -(random_negatif) + tengah;
    }
}

void bomRandom() {
    int random = (rand() % 2);
    if (random == 1) {//jika positif
        int random_positif = (rand() % 800);
        posisiBomX += random_positif;
    } else {//jika negatif
        int random_negatif = (rand() % 800);
        posisiBomX = -(random_negatif) + 100;
    }
}

void fungsiObjek() {
    if (objekDatang) {
        objekRandom();
    }
    if (posisiObjekX >= -90 && posisiObjekX <= 265) {
        glPushMatrix();
        glTranslatef(posisiObjekX, posisiObjekY, 0);
        objekTangkap();
        glPopMatrix();
        objekDatang = false;
    }
    if (posisiObjekY < -230) {
        posisiObjekY = 140;
        objekDatang = true;
        nilai -= 1;
    }
    if (posisiObjekY <= -170 && posisiObjekX >= x_player + 100 && posisiObjekX <= x_player + 200) {
        Beep(1300, 50);
        posisiObjekY = 140;
        objekDatang = true;
        nilai += 4;
    }
}

void fungsiBom() {
    if (bomDatang) {
        bomRandom();
    }
    if (posisiBomX >= -98.5f && posisiBomX <= 230.5f) {
        glPushMatrix();
        glTranslatef(posisiBomX, posisiBomY, 0);
        bom();
        glPopMatrix();
        bomDatang = false;
    }
    if (posisiBomY < -200) {
        posisiBomY = 325;
        bomDatang = true;
    }
    if (posisiBomY <-120 && posisiBomX >= x_player + 102.5f && posisiBomX <= x_player + 185) {
        Beep(1500, 50);
        posisiBomY = 325;
        bomDatang = true;
        nilai -= 3;
    }
}

void fungsiAwan1() {
    if (awan1x < 635) {
        glPushMatrix();
        glTranslatef(awan1x, 0, 0);
        awan1();
        glPopMatrix();
    }
    if (awan1x > 635) {
        awan1x = -125;
    }
}

void fungsiAwan2() {
    if (awan2x < 235) {
        glPushMatrix();
        glTranslatef(awan2x, 0, 0);
        awan2();
        glPopMatrix();
    }
    if (awan2x > 235) {
        awan2x = -325;
    }
}

void tulisKalah() {
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(315, 315);
    glVertex2f(475, 315);
    glVertex2f(475, 350);
    glVertex2f(315, 350);
    glEnd();
    glColor3f(0, 0, 0);
    tulis(340, 325, "GAME OVER!");
    tulis(250, 250, "PRESS Enter To Play Again, ESC To Exit");
    glEnd();
}

void tulisMenang() {
    fungsiAwan1();
    fungsiAwan2();
    matahari();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(315, 315);
    glVertex2f(475, 315);
    glVertex2f(475, 350);
    glVertex2f(315, 350);
    glEnd();
    glColor3f(0, 0, 0);
    tulis(340, 325, "YOU WIN!");
    glEnd();
}

void tulisPause() {
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(315, 315);
    glVertex2f(475, 315);
    glVertex2f(475, 350);
    glVertex2f(315, 350);
    glEnd();
    glColor3f(0, 0, 0);
    tulis(340, 325, " PAUSE! ");
    glEnd();
}

void control(unsigned char key, int x, int y) {//method untuk mengontrol player dengan keyboard
    if ((key == 'd') || (key == 'D')) {
        if (x_player <= 385.0f) {
            x_player += 20.0f;
        }
    }
    if ((key == 'a') || (key == 'A')) {
        if (x_player >= -325.0f) {
            x_player -= 20.0f;
        }
    }
    if (awal || gameOver && key == 13) {//enter
        gameOver = false;
        posisiBomY = 250;
        posisiObjekY = 265;
        nilai = 0;
        mulai = true;
        awal = false;
    }
    if (key == 27) {
        exit(0);
    }
    if (key == 'p' && mulai) {
        pause = true;
    }
    if (key == 'o' && mulai && pause) {
        pause = false;
    }
}

void timer(int id) {
    if (mulai&&!pause) {
        posisiObjekY -= 10;
        posisiBomY -= 10;
    }
    awan1x += 0.75f;
    awan2x += 1;
    if (nilai > 16) {
        posisiObjekY -= 2.0f;
        posisiBomY -= 1.7f;
    }
    if (pause) {
        posisiBomY = posisiBomY;
        posisiObjekY = posisiObjekY;
        x_player = 0;
        if (nilai > 10) {
            posisiBomY = posisiBomY + 1.7f;
            posisiObjekY = posisiObjekY + 2.0f;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(100, timer, 0);
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (awal) {
        mulai = false;
        backgroundLangit();
        backgroundTanah();
        fungsiAwan1();
        fungsiAwan2();
        matahari();
        glColor3f(0, 0, 0);
        tulis(330, 575, "The Red Catcher");
        tulis(250, 350, "Press Enter To Play, ESC To Exit");
        tulis(250, 320, "Controller : ");
        tulis(300, 290, "D to Move Right");
        tulis(300, 260, "A to Move Left");
        tulis(300, 230, "P To Pause");
        tulis(300, 200, "O To Unpause");
        tulis(270, 25, "By Mohammad Nahdhiana H.");
        tulis(315, 0, "132410101056");
        mulai = false;
    }
    if (mulai) {
        backgroundLangit();
        backgroundTanah();
        fungsiAwan1();
        fungsiAwan2();
        matahari();
        fungsiObjek();
        fungsiBom();
        glPushMatrix();
        glTranslatef(x_player, 0, 0);
        player();
        glPopMatrix();
        tulisanSkor();
    }
    if (pause) {
        glBegin(GL_QUADS);
        glColor3f(1, 1, 1);
        glVertex2f(315, 315);
        glVertex2f(475, 315);
        glVertex2f(475, 350);
        glVertex2f(315, 350);
        glEnd();
        glColor3f(0, 0, 0);
        tulis(340, 325, "PAUSE!");
        glEnd();
    }
    if (nilai >= 40) {
        menang == true;
        tulisMenang();
        mulai = false;
        player();
    }
    if (nilai < 0) {
        gameOver = true;
        tulisKalah();
        posisiBomY = 0;
        posisiObjekY = 0;
        awan1x = 0;
        awan2x = 0;
        x_player = 0;
    }
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(300, 50);
    glutInitWindowSize(800, 600);
    glutCreateWindow("THE RED CATCHER");
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(control);
    glutTimerFunc(25, timer, 0);
    gluOrtho2D(0, 800, 0, 600);
    glutMainLoop();
    return 0;
}