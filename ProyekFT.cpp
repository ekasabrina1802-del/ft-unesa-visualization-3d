#include <GL/freeglut.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h> 
#include <string.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
// ==========================================
// GLOBAL VARIABLES
// ==========================================
float cameraZ = 15.0f;
float xPos = 0.0f;
float zPos = 20.0f;
float yPos = 2.0f;
float angleX = 0.0f;
float angleY = 0.0f;
float lx = 0.0f, lz = -1.0f;
float ly = 0.0f;
bool keyStates[256] = { false };        
bool specialKeyStates[256] = { false }; 
// --- WARNA ---
float roofTileColor[3] = { 0.8f, 0.4f, 0.1f }; // Merah Bata (Genteng)
float quartzColor[3] = { 0.95f, 0.95f, 0.95f };// Putih Bersih (Dinding Utama)
float creamColor[3] = { 0.9f, 0.85f, 0.8f };   // Cream
float greyColor[3] = { 0.3f, 0.3f, 0.35f };    // Warna Abu Besi Tua
float steelGrey[3] = { 0.5f, 0.5f, 0.55f };    // Abu Besi (Wire/Kawat)
float stoneColor[3] = { 0.4f, 0.4f, 0.4f };    // Abu Batu (Pondasi/Tangga)
float concreteColor[3] = { 0.7f, 0.7f, 0.7f }; // Abu Beton (Alas/Trotoar)
float seaBlueColor[3] = { 0.0f, 0.5f, 0.8f };  // Biru Laut (Kaca Gedung Besar)
float iceBlueColor[3] = { 0.85f, 0.9f, 1.0f }; // Biru Es Pucat (Jendela Kecil)
float darkGlassColor[3] = { 0.1f, 0.15f, 0.2f }; // jendela Gelap
float doorGlassColor[3] = { 0.6f, 0.8f, 0.9f };// Biru Pintu
float brownColor[3] = { 0.6f, 0.4f, 0.2f };    // Coklat Kayu
float moccaColor[3] = { 0.75f, 0.60f, 0.50f }; // Mocca (Frame/Pilar A1)
float sageGreen[3] = { 0.55f, 0.65f, 0.55f };  // Hijau Sage (Pintu A1)
float silverDark[3] = { 0.60f, 0.60f, 0.65f }; // Silver Gelap (Kanopi/Atap Datar)
float iceWhiteColor[3] = { 0.90f, 0.90f, 0.95f }; // Silver Terang (Tulisan)
float coolWhite[3] = { 0.85f, 0.85f, 0.9f };   // Putih Tulang Kebiruan (Ornamen/Atap)
float pureWhite[3] = { 1.0f, 1.0f, 1.0f };     // Putih Terang
float pitchBlack[3] = { 0.0f, 0.0f, 0.0f };    // Hitam Pekat (Paling Gelap)
float softBlack[3] = { 0.1f, 0.1f, 0.1f };     // Hitam Abu (Agak Terang dikit)
float goldColor[3] = { 1.0f, 0.85f, 0.0f };    // Emas 
float orangeColor[3] = { 1.0f, 0.5f, 0.0f };   // Orange 
float colRoofZinc[3] = { 0.88f, 0.88f, 0.90f };  // Hijau Menara
float TowerGreen[3] = { 0.30f, 0.70f, 0.35f };// Coklat tua untuk tiang kayu/besi
float DarkGreen[3] = { 0.05f, 0.45f, 0.15f }; // Hijau Tua
float LightGreen[3] = { 0.4f, 0.7f, 0.4f }; // Hijau Muda
float forestGreen[3] = { 0.13f, 0.55f, 0.13f };
float darkForestGreen[3] = { 0.05f, 0.40f, 0.15f };
float musalaWallColor[3] = { 0.95f, 0.95f, 0.85f }; // Creamish White
float musalaPillarColor[3] = { 0.8f, 0.75f, 0.65f }; // Light Brown/Sandstone
float musalaRoofMain[3] = { 0.7f, 0.3f, 0.1f };    // Darker Terracotta
float musalaRoofAccent[3] = { 0.3f, 0.6f, 0.3f };  // Green Accent
float musalaDoorFrame[3] = { 0.4f, 0.2f, 0.1f };   // Dark Brown for frames
float musalaWindowGlass[3] = { 0.6f, 0.8f, 0.9f }; // Light Blue Glass
float musalaSpeakerSilver[3] = { 0.7f, 0.7f, 0.75f }; // Silver for speaker
float safetyYellow[3] = { 1.0f, 0.85f, 0.0f };
float woodTrimColor[3] = { 0.4f, 0.25f, 0.15f };
float windowGlassColor[3] = { 0.55f, 0.75f, 0.85f };
float stairConcreteColor[3] = { 0.8f, 0.8f, 0.8f };
float brownRoofColor[3] = { 0.7f, 0.35f, 0.1f };
float maroonColor[3] = { 0.5f, 0.0f, 0.0f };
float woodTreadColor[3] = { 0.8f, 0.55f, 0.3f }; // Warna Kayu untuk pijakan & pegangan
// --- VARIABEL LIGHTING & ZOOM ---
float fov = 45.0f; // Field of View (Zoom)
GLfloat lightPosition[] = { 100.0f, 200.0f, 50.0f, 1.0f }; // Di atas kanan
GLfloat ambientLight[] = { 0.3f, 0.3f, 0.4f, 1.0f };      // Cahaya lingkungan (Malam/Biru Gelap)
GLfloat diffuseLight[] = { 0.9f, 0.9f, 0.8f, 1.0f };      // Cahaya utama (Kekuningan)
GLfloat lightPos[] = { 0.0f, 150.0f, 0.0f, 1.0f };
// ==========================================
// HELPER FUNCTIONS
// ==========================================
void drawCoordinates() {
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity(); gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity(); glDisable(GL_DEPTH_TEST);
    char text[99];
    sprintf_s(text, sizeof(text), "POSISI: X=%.1f  Y=%.1f  Z=%.1f", xPos, yPos, zPos);
    glColor3f(1.0f, 1.0f, 0.0f);
    glRasterPos2i(10, 570);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
    glEnable(GL_DEPTH_TEST);  glPopMatrix(); glMatrixMode(GL_PROJECTION); glPopMatrix(); glMatrixMode(GL_MODELVIEW);
}

void drawBlock(float width, float height, float depth) {
    glPushMatrix(); glScalef(width, height, depth); glutSolidCube(1.0); glPopMatrix();
}

void drawBola(float x, float y, float z, float radius) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidSphere(radius, 30, 30);
    glPopMatrix();
}

void drawLimas() {
    glPushMatrix(); glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);  glRotatef(45.0f, 0.0f, 0.0f, 1.0f); glutWireCone(2.2f, 4.0f, 4, 10); glPopMatrix();
}

void drawDiamond() {
    glPushMatrix(); glTranslatef(0.0f, 11.2f, -10.0f); glRotatef(45.0f, 0.0f, 0.0f, 1.0f); glScalef(1.5f, 1.5f, 0.4f);
    glColor3f(0.75f, 0.75f, 0.80f); glutSolidCube(1.0); glPopMatrix();
}

void drawJajarGenjang(float w, float h, float d, float drop) {
    float W = w / 2.0f, H = h / 2.0f, D = d / 2.0f; glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);  glVertex3f(-W, -H + drop, D); glVertex3f(W, -H - drop, D); glVertex3f(W, H - drop, D); glVertex3f(-W, H + drop, D);
    glNormal3f(0, 0, -1); glVertex3f(W, -H - drop, -D); glVertex3f(-W, -H + drop, -D); glVertex3f(-W, H + drop, -D); glVertex3f(W, H - drop, -D);
    glNormal3f(-1, 0, 0); glVertex3f(-W, -H + drop, -D); glVertex3f(-W, -H + drop, D); glVertex3f(-W, H + drop, D); glVertex3f(-W, H + drop, -D);
    glNormal3f(1, 0, 0);  glVertex3f(W, -H - drop, D); glVertex3f(W, -H - drop, -D); glVertex3f(W, H - drop, -D); glVertex3f(W, H - drop, D);
    glNormal3f(0, 1, 0);  glVertex3f(-W, H + drop, D); glVertex3f(W, H - drop, D); glVertex3f(W, H - drop, -D); glVertex3f(-W, H + drop, -D);
    glNormal3f(0, -1, 0); glVertex3f(-W, -H + drop, -D); glVertex3f(W, -H - drop, -D); glVertex3f(W, -H - drop, D); glVertex3f(-W, -H + drop, D);
    glEnd();
}

void drawTabung(float radius, float tinggiTabung, float tinggiKerucut) {
    GLUquadricObj* q = gluNewQuadric();
    gluQuadricDrawStyle(q, GLU_FILL);
    // 1. Badan Tabung
    glPushMatrix();
    glRotatef(-90, 1, 0, 0); // Putar agar berdiri tegak
    gluCylinder(q, radius, radius, tinggiTabung, 30, 1);
    // Tutup Bawah (Alas)
    gluDisk(q, 0.0f, radius, 30, 1);
    glPopMatrix();
    // 2. Tutup Kerucut (Di atas tabung)
    glPushMatrix();
    glTranslatef(0.0f, tinggiTabung, 0.0f); // Pindah ke ujung atas tabung
    glRotatef(-90, 1, 0, 0); // Putar agar berdiri
    glutSolidCone(radius, tinggiKerucut, 30, 10);
    glPopMatrix();
    gluDeleteQuadric(q);
}

void drawAtap(float p, float l, float t) {
    float over = 1.2f;
    float ridge = (p > l) ? p - l : 0;
    glDisable(GL_CULL_FACE);
    glColor3fv(roofTileColor);
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0.5, 1); glVertex3f(-p / 2 - over, 0, l / 2 + over); glVertex3f(p / 2 + over, 0, l / 2 + over); glVertex3f(ridge / 2, t, 0); glVertex3f(-p / 2 - over, 0, l / 2 + over); glVertex3f(ridge / 2, t, 0); glVertex3f(-ridge / 2, t, 0);
    glNormal3f(0, 0.5, -1); glVertex3f(-p / 2 - over, 0, -l / 2 - over); glVertex3f(p / 2 + over, 0, -l / 2 - over); glVertex3f(ridge / 2, t, 0); glVertex3f(-p / 2 - over, 0, -l / 2 - over); glVertex3f(ridge / 2, t, 0); glVertex3f(-ridge / 2, t, 0);
    glNormal3f(-1, 0.5, 0); glVertex3f(-p / 2 - over, 0, l / 2 + over); glVertex3f(-p / 2 - over, 0, -l / 2 - over); glVertex3f(-ridge / 2, t, 0);
    glNormal3f(1, 0.5, 0); glVertex3f(p / 2 + over, 0, l / 2 + over); glVertex3f(p / 2 + over, 0, -l / 2 - over); glVertex3f(ridge / 2, t, 0);
    glEnd();
    glColor3fv(brownColor); glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP); glVertex3f(-p / 2 - over, 0, l / 2 + over); glVertex3f(p / 2 + over, 0, l / 2 + over); glVertex3f(p / 2 + over, 0, -l / 2 - over); glVertex3f(-p / 2 - over, 0, -l / 2 - over); glEnd();
}

void drawTieredLimasRoof(float centerX, float centerY, float centerZ, float baseWidth, float baseDepth, float totalHeight) {
    // --- KONFIGURASI PROPORSI ATAP ---
    float tier1Height = totalHeight * 0.45f; // Tinggi atap bawah (landai)
    float neckHeight = 1.5f;                // Tinggi dinding penghubung (leher)
    float tier2Height = totalHeight * 0.55f; // Tinggi atap atas (curam)
    // Ukuran Atap Atas (60% dari atap bawah)
    float topWidth = baseWidth * 0.6f;
    float topDepth = baseDepth * 0.6f;
    // --- 1. ATAP BAWAH (TIER 1) ---
    glColor3fv(musalaRoofMain);
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    // Gambar Listplang (Papan tepi atap) - Hijau
    glColor3fv(musalaRoofAccent);
    glTranslatef(0.0f, 0.0f, 0.0f);
    drawBlock(baseWidth + 0.5f, 0.4f, baseDepth + 0.5f);
    glPopMatrix();
    // --- 2. LEHER / DINDING PENGHUBUNG ---
    // Posisinya ada di puncak atap bawah (sedikit turun agar tertanam)
    float neckY = centerY + (tier1Height * 0.85f);
    glColor3fv(musalaWallColor); // Warna dinding
    glPushMatrix();
    glTranslatef(centerX, neckY + (neckHeight / 2.0f), centerZ);
    drawBlock(topWidth - 1.0f, neckHeight, topDepth - 1.0f);
    glPopMatrix();
    // --- 3. ATAP ATAS (TIER 2) ---
    // Posisinya di atas leher
    float topRoofY = neckY + neckHeight;
    glColor3fv(musalaRoofMain);
    glPushMatrix();
    glTranslatef(centerX, topRoofY, centerZ);
    // Gambar Listplang Atas
    glColor3fv(musalaRoofAccent);
    drawBlock(topWidth + 0.5f, 0.4f, topDepth + 0.5f);
    glPopMatrix();
}

void drawRightTriPrism(float width, float height, float depth) {
    float w = width / 2.0f;
    float h = height / 2.0f;
    float d = depth / 2.0f;
    glBegin(GL_TRIANGLES);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-w, -h, -d); glVertex3f(-w, h, -d); glVertex3f(-w, -h, d);
    glVertex3f(-w, h, -d);  glVertex3f(-w, h, d);  glVertex3f(-w, -h, d);
    glNormal3f(1.0f, 1.0f, 0.0f); // Normal estimasi
    glVertex3f(w, -h, -d); glVertex3f(-w, h, -d); glVertex3f(-w, -h, d);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-w, -h, d); glVertex3f(w, -h, d); glVertex3f(-w, h, d);
    glVertex3f(-w, -h, -d); glVertex3f(-w, h, -d); glVertex3f(w, -h, -d);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(-w, -h, d); glVertex3f(w, -h, d); glVertex3f(w, -h, -d); glVertex3f(-w, -h, -d);
    glVertex3f(-w, -h, d); glVertex3f(-w, -h, -d); glVertex3f(-w, h, -d); glVertex3f(-w, h, d);
    glVertex3f(-w, h, d); glVertex3f(-w, h, -d); glVertex3f(w, -h, -d); glVertex3f(w, -h, d);
    glEnd();
}

void drawIndustrialStaircase(float startX, float startY, float startZ, bool facingNegX) {
    float stepRise = 0.4f;   // Tinggi per anak tangga (kecil biar smooth)
    float stepRun = 0.8f;   // Panjang pijakan (kedalaman)
    float stepWidth = 4.0f;  // Lebar tangga
    float treadThick = 0.1f; // Tebal papan kayu
    int stepsPerFlight = 10;
    // Arah X (1.0 atau -1.0 tergantung facingNegX)
    // Jika facingNegX (menghadap X negatif), maka tangga "maju" ke arah -X dari tembok.
    float xDir = facingNegX ? -1.0f : 1.0f;
    // =======================================================================
    // 1. FLIGHT 1 (TANGGA BAWAH) - MENGHADAP Z POSITIF
    // =======================================================================
    // Posisi: Di bagian depan area (Z lebih kecil/negatif relatif terhadap flight 2).
    // Arah naik: Z semakin bertambah (Positif).
    float f1StartX = startX;
    float f1StartY = startY;
    float f1StartZ = startZ; // Mulai dari Z awal
    for (int i = 0; i < stepsPerFlight; i++) {
        float curY = f1StartY + (i * stepRise);
        float curZ = f1StartZ + (i * stepRun); // Maju ke arah Z Positif
        // Pijakan Kayu
        glColor3fv(woodTreadColor);
        glPushMatrix();
        // Pusat Balok ada di tengah, jadi geser X sejauh setengah lebar tangga * arah
        glTranslatef(f1StartX + (stepWidth / 2.0f * xDir), curY + stepRise / 2.0f, curZ + stepRun / 2.0f);
        drawBlock(stepWidth, treadThick, stepRun);
        glPopMatrix();
        glColor3fv(quartzColor);
        // Kiri
        glPushMatrix();
        glTranslatef(f1StartX + (0.2f * xDir), curY, curZ + stepRun / 2.0f);
        glRotatef(-30.0f, 1.0f, 0.0f, 0.0f); // Miring menanjak ke Z+
        drawBlock(0.2f, stepRise * 4.0f, stepRun * 1.5f);
        glPopMatrix();
        // Kanan
        glPushMatrix();
        glTranslatef(f1StartX + ((stepWidth - 0.2f) * xDir), curY, curZ + stepRun / 2.0f);
        glRotatef(-30.0f, 1.0f, 0.0f, 0.0f);
        drawBlock(0.2f, stepRise * 4.0f, stepRun * 1.5f);
        glPopMatrix();
    }
    // =======================================================================
    // 2. BORDES / LANDING (LANTAI TENGAH)
    // =======================================================================
    // Posisi: Di ujung atas Flight 1.
    // Ketinggian: Y = 4.0f.
    // Menghubungkan Z akhir Flight 1 ke Z awal Flight 2.
    float landingY = f1StartY + (stepsPerFlight * stepRise); // Y = 4.0
    float landingZ = f1StartZ + (stepsPerFlight * stepRun);  // Z di ujung tangga 1
    float landingDepth = 3.0f; // Lebar bordes ke arah Z
    glColor3fv(woodTreadColor);
    glPushMatrix();
    float landingCenterX = startX + (stepWidth * xDir);
    glTranslatef(landingCenterX, landingY, landingZ + (landingDepth / 2.0f));
    drawBlock(stepWidth * 2.0f, treadThick, landingDepth);
    glPopMatrix();
    // Tiang Penyangga Bordes
    glColor3fv(quartzColor);
    glPushMatrix();
    glTranslatef(landingCenterX, landingY / 2.0f, landingZ + (landingDepth / 2.0f));
    drawBlock(0.5f, landingY, 0.5f);
    glPopMatrix();
    // =======================================================================
    // 3. FLIGHT 2 (TANGGA ATAS) - MENGHADAP Z NEGATIF
    // =======================================================================
    // Posisi X: Di sebelah Flight 1 (Geser sejauh stepWidth * xDir)
    // Posisi Y: Mulai dari Bordes (4.0) naik ke 8.0.
    // Arah naik: Z semakin BERKURANG (Negatif), balik ke arah startZ.
    float f2StartX = startX + (stepWidth * xDir); // Geser ke samping
    float f2StartY = landingY;
    float f2StartZ = landingZ; 
    for (int i = 0; i < stepsPerFlight; i++) {
        float curY = f2StartY + (i * stepRise);
        // Z mundur (dikurangi) karena menghadap Z negatif
        float curZ = f2StartZ - (i * stepRun) - stepRun;
        // Pijakan
        glColor3fv(woodTreadColor);
        glPushMatrix();
        glTranslatef(f2StartX + (stepWidth / 2.0f * xDir), curY + stepRise / 2.0f, curZ + stepRun / 2.0f);
        drawBlock(stepWidth, treadThick, stepRun);
        glPopMatrix();
        // Penyangga Besi
        glColor3fv(quartzColor);
        // Kiri
        glPushMatrix();
        glTranslatef(f2StartX + (0.2f * xDir), curY, curZ + stepRun / 2.0f);
        glRotatef(30.0f, 1.0f, 0.0f, 0.0f); // Miring ke arah sebaliknya (Z-)
        drawBlock(0.2f, stepRise * 4.0f, stepRun * 1.5f);
        glPopMatrix();
        // Kanan
        glPushMatrix();
        glTranslatef(f2StartX + ((stepWidth - 0.2f) * xDir), curY, curZ + stepRun / 2.0f);
        glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
        drawBlock(0.2f, stepRise * 4.0f, stepRun * 1.5f);
        glPopMatrix();
    }
}

void drawStairUnit(float startX, float startY, float startZ, bool facingNegX) {
    // --- DIMENSI (Sudah dikecilkan agar tidak "Kebesaran") ---
    float stepRise = 0.4f;   // Tinggi per anak tangga (Standar)
    float stepRun = 0.8f;   // Panjang pijakan (Standar)
    float stepWidth = 4.0f;  // Lebar tangga
    float treadThick = 0.1f; // Tebal papan
    int steps = 10;          
    float xDir = facingNegX ? -1.0f : 1.0f;
    // =======================================================================
    // 1. FLIGHT 1 (BAWAH) - NAIK KE ARAH Z NEGATIF (MUNDUR)
    // =======================================================================
    for (int i = 0; i < steps; i++) {
        float curY = startY + (i * stepRise) + (stepRise / 2.0f);
        // RUMUS TERBALIK: Dikurangi (Mundur ke Z Negatif)
        float curZ = startZ - (i * stepRun) - (stepRun / 2.0f);
        // A. Pijakan Kayu
        glColor3fv(woodTreadColor); // Pastikan warna ini ada
        glPushMatrix();
        // Geser X setengah lebar tangga
        glTranslatef(startX + (stepWidth / 2.0f * xDir), curY, curZ);
        drawBlock(stepWidth, treadThick, stepRun);
        glPopMatrix();

        // B. Penyangga Besi (Stringer)
        glColor3fv(quartzColor); // Pastikan warna ini ada
        // Kiri
        glPushMatrix();
        glTranslatef(startX + (0.2f * xDir), curY, curZ);
        // Rotasi dimiringkan ke arah Z Negatif
        if (facingNegX) glRotatef(30.0f, 1.0f, 0.0f, 0.0f); else glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
        drawBlock(0.2f, stepRise * 4.0f, stepRun * 1.5f);
        glPopMatrix();
        // Kanan
        glPushMatrix();
        glTranslatef(startX + ((stepWidth - 0.2f) * xDir), curY, curZ);
        if (facingNegX) glRotatef(30.0f, 1.0f, 0.0f, 0.0f); else glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
        drawBlock(0.2f, stepRise * 4.0f, stepRun * 1.5f);
        glPopMatrix();
    }
    // =======================================================================
    // 2. BORDES / LANDING (TENGAH)
    // =======================================================================
    float landingY = startY + (steps * stepRise);
    float landingZ = startZ - (steps * stepRun);
    float landingDepth = 3.0f;
    float landingCenterX = startX + (stepWidth * xDir) + (0.5f * xDir); 
    glColor3fv(woodTreadColor);
    glPushMatrix();
    // Lebar bordes = 2x lebar tangga + spasi
    glTranslatef(landingCenterX, landingY, landingZ - (landingDepth / 2.0f));
    drawBlock((stepWidth * 2.0f) + 2.0f, treadThick, landingDepth);
    glPopMatrix();
    // Tiang Penyangga Bordes
    glColor3fv(quartzColor);
    glPushMatrix();
    glTranslatef(landingCenterX, landingY / 2.0f, landingZ - (landingDepth / 2.0f));
    drawBlock(0.5f, landingY, 0.5f);
    glPopMatrix();
    // =======================================================================
    // 3. FLIGHT 2 (ATAS) - NAIK KE ARAH Z POSITIF (MAJU)
    // =======================================================================
    // Posisi X geser ke samping (Jalur sebelahnya)
    float f2StartX = startX + (stepWidth * xDir);
    float f2StartY = landingY;
    float f2StartZ = landingZ;
    for (int i = 0; i < steps; i++) {
        float curY = f2StartY + (i * stepRise);
        // RUMUS TERBALIK: Ditambah (Maju ke Z Positif)
        float curZ = f2StartZ + (i * stepRun);
        // Pijakan
        glColor3fv(woodTreadColor);
        glPushMatrix();
        glTranslatef(f2StartX + (stepWidth / 2.0f * xDir), curY, curZ);
        drawBlock(stepWidth, treadThick, stepRun);
        glPopMatrix();
        // Penyangga
        glColor3fv(quartzColor);
        // Kiri
        glPushMatrix();
        glTranslatef(f2StartX + (0.2f * xDir), curY, curZ);
        glRotatef(-30.0f, 1.0f, 0.0f, 0.0f); // Miring ke Z Positif
        drawBlock(0.2f, stepRise * 4.0f, stepRun * 1.5f);
        glPopMatrix();
        // Kanan
        glPushMatrix();
        glTranslatef(f2StartX + ((stepWidth - 0.2f) * xDir), curY, curZ);
        glRotatef(-30.0f, 1.0f, 0.0f, 0.0f);
        drawBlock(0.2f, stepRise * 4.0f, stepRun * 1.5f);
        glPopMatrix();
    }
}

void drawWalkway(float length, float width) {
    // --- KONFIGURASI ---
    float totalHeight = 7.0f;
    float roofHeight = 2.5f;  // Tinggi segitiga atap
    float pillarHeight = totalHeight - roofHeight; // 4.5
    float roofOver = 0.8f;  // Lebar lebihan atap
    float halfW = width / 2.0f;
    float halfL = length / 2.0f;
    float roofW = halfW + roofOver; // Lebar atap menyesuaikan lebar jalan
    // --- 1. LANTAI (ALAS) ---
    glColor3f(0.6f, 0.6f, 0.65f); // Abu Beton
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 0.0f);
    // Alas sedikit lebih lebar dari jalan (+1.0)
    drawBlock(width + 1.0f, 0.2f, length);
    glPopMatrix();
    // --- 2. PILAR PENYANGGA (LOOPING) ---
    float spacing = 4.0f;
    int numPillars = (int)(length / spacing);
    glColor3fv(darkForestGreen); 
    for (int i = 0; i <= numPillars; i++) {
        float zPos = -halfL + (i * spacing);
        if (zPos > halfL + 0.1f) break;
        // Pilar Kiri (Menyesuaikan Width)
        glPushMatrix();
        glTranslatef(-halfW + 0.3f, pillarHeight / 2.0f, zPos);
        drawBlock(0.6f, pillarHeight, 0.6f);
        glPopMatrix();
        // Pilar Kanan (Menyesuaikan Width)
        glPushMatrix();
        glTranslatef(halfW - 0.3f, pillarHeight / 2.0f, zPos);
        drawBlock(0.6f, pillarHeight, 0.6f);
        glPopMatrix();
        // Balok Melintang Atas
        glPushMatrix();
        glTranslatef(0.0f, pillarHeight - 0.3f, zPos);
        drawBlock(width, 0.6f, 0.4f);
        glPopMatrix();
    }
    // --- 3. ATAP ---
    glColor3f(0.8f, 0.4f, 0.1f); // Merah Bata
    glPushMatrix();
    glTranslatef(0.0f, pillarHeight, 0.0f);
    glBegin(GL_QUADS);
    // Kanan
    glVertex3f(roofW, 0.0f, halfL);
    glVertex3f(roofW, 0.0f, -halfL);
    glVertex3f(0.0f, roofHeight, -halfL);
    glVertex3f(0.0f, roofHeight, halfL);
    // Kiri
    glVertex3f(0.0f, roofHeight, halfL);
    glVertex3f(0.0f, roofHeight, -halfL);
    glVertex3f(-roofW, 0.0f, -halfL);
    glVertex3f(-roofW, 0.0f, halfL);
    // Plafond
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex3f(-roofW, 0.0f, halfL);
    glVertex3f(roofW, 0.0f, halfL);
    glVertex3f(roofW, 0.0f, -halfL);
    glVertex3f(-roofW, 0.0f, -halfL);
    glEnd();
    // Tutup Segitiga (Gable)
    glColor3f(0.8f, 0.4f, 0.1f); // Balik ke Merah Bata
    glBegin(GL_TRIANGLES);
    // Depan
    glVertex3f(-roofW, 0.0f, halfL);
    glVertex3f(roofW, 0.0f, halfL);
    glVertex3f(0.0f, roofHeight, halfL);
    // Belakang
    glVertex3f(roofW, 0.0f, -halfL);
    glVertex3f(-roofW, 0.0f, -halfL);
    glVertex3f(0.0f, roofHeight, -halfL);
    glEnd();
    glPopMatrix();
}

void drawText3D(const char* text, float x, float y, float z, float scale) {
    glPushMatrix(); glTranslatef(x, y, z); glScalef(scale, scale, scale); glLineWidth(3.0f);
    for (const char* c = text; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glLineWidth(1.0f); glPopMatrix();
}

// ==========================================
// KONSTRUKSI GEDUNG
// ==========================================
void drawjalandantrotoar() {
    // --- JALAN RAYA ---
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, 50.0f);
    glVertex3f(300.0f, 0.0f, 50.0f);
    glVertex3f(300.0f, 0.0f, -400.0f);
    glVertex3f(-100.0f, 0.0f, -400.0f);
    glEnd();
    glColor3fv(concreteColor);
    // --- TROTOAR POS SATPAM ---
    glPushMatrix(); glTranslatef(-9.0f, 0.2f, -34.0f); drawBlock(3.0f, 0.4f, 50.0f); glPopMatrix();
    // --- TROTOAR KANAN GAPURA ---
    glPushMatrix(); glTranslatef(130.0f, 0.2f, -10.0f); drawBlock(240.0f, 0.4f, 3.0f); glPopMatrix();
    // --- TROTOAR A1 ---
    glPushMatrix(); glTranslatef(13.0f, 0.2f, -50.0f); drawBlock(11.0f, 0.4f, 3.0f); glPopMatrix();
    // --- TROTOAR A2 ---
    glPushMatrix(); glTranslatef(9.0f, 0.2f, -72.0f); drawBlock(3.0f, 0.4f, 43.0f); glPopMatrix();
	// --- TROTOAR A3 ---
    glPushMatrix(); glTranslatef(9.0f, 0.2f, -126.0f); drawBlock(3.0f, 0.4f, 28.0f); glPopMatrix();
	// --- TROTOAR A4 ---
    glPushMatrix(); glTranslatef(9.0f, 0.2f, -222.0f); drawBlock(3.0f, 0.4f, 116.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(37.0f, 0.2f, -278.5f); drawBlock(56.0f, 0.4f, 3.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(90.0f, 0.2f, -278.5f); drawBlock(30.0f, 0.4f, 3.0f); glPopMatrix();
	// --- TROTOAR A5 ---
    glPushMatrix(); glTranslatef(180.0f, 0.2f, -278.5f); drawBlock(90.0f, 0.4f, 3.0f); glPopMatrix();
	// --- TROTOAR A6 ---
    glPushMatrix(); glTranslatef(223.5f, 0.2f, -225); drawBlock(3.0f, 0.4f, 105.0f); glPopMatrix();
	// --- TROTOAR A7 ---
    glPushMatrix(); glTranslatef(223.5f, 0.2f, -82); drawBlock(3.0f, 0.4f, 120.0f); glPopMatrix();
	// --- TROTOAR A8 ---
    glPushMatrix(); glTranslatef(248.5f, 0.2f, -190.0f); drawBlock(3.0f, 0.4f, 360.0f); glPopMatrix();
    // --- TROTOAR A9 ---
    glPushMatrix(); glTranslatef(-9.0f, 0.2f, -115.0f); drawBlock(3.0f, 0.4f, 50.0f); glPopMatrix();
    // --- TROTOAR A10 ---
    glPushMatrix(); glTranslatef(-9.0f, 0.2f, -235.0f); drawBlock(3.0f, 0.4f, 150.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(72.0f, 0.2f, -308.5f); drawBlock(162.0f, 0.4f, 3.0f); glPopMatrix();
	// --- TROTOAR E1 ---
	glPushMatrix(); glTranslatef(200.0f, 0.2f, -370.0f); drawBlock(100.0f, 0.4f, 3.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(200.0f, 0.2f, -308.5f); drawBlock(50.0f, 0.4f, 3.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(151.5, 0.2f, -340); drawBlock(3.0f, 0.4f, 60.0f); glPopMatrix();
}

void drawInterior() {
	float ZI = -103.0f;
    // BOLA
    glColor3fv(pureWhite); 
    glPushMatrix(); glTranslatef(8.0f, -0.3f, ZI - 6); drawBola(1.0f, 1.0f, 1.0f, 0.7f); glPopMatrix();
    glPushMatrix(); glTranslatef(8.0f, -0.3f, ZI - 3); drawBola(1.0f, 1.0f, 1.0f, 0.7f); glPopMatrix();
    glPushMatrix(); glTranslatef(8.0f, -0.3f, ZI + 6); drawBola(1.0f, 1.0f, 1.0f, 0.7f); glPopMatrix();
    glPushMatrix(); glTranslatef(8.0f, -0.3f, ZI + 3); drawBola(1.0f, 1.0f, 1.0f, 0.7f); glPopMatrix();
    // BATU & TULISAN
    glColor3fv(stoneColor);
    glPushMatrix(); glTranslatef(12.0f, 1.5f, ZI +1); drawBlock(0.5f, 4.0f, 6.0f); glPopMatrix();
    glColor3fv(quartzColor);
    glPushMatrix(); glTranslatef(11.7f, 1.8f, ZI+1); drawBlock(0.1f, 2.5f, 5.0f); glPopMatrix();
    glColor3fv(pitchBlack);
    glPushMatrix();
    glTranslatef(11.6, 2.5, ZI-1.1); glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); glScalef(0.002f, 0.002f, 0.001f);
    glLineWidth(3.0f);
    for (const char* c = "UNIVERSITAS NEGERI SURABAYA"; *c != '\0'; c++) glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(11.6, 2, ZI-0.2); glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); glScalef(0.002f, 0.002f, 0.001f);
    for (const char* c = "FAKULTAS TEKNIK"; *c != '\0'; c++) glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(11.6, 1.5, ZI+0.3); glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); glScalef(0.002f, 0.002f, 0.001f);
    for (const char* c = "JURUSAN"; *c != '\0'; c++) glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(11.6, 1, ZI+0.6); glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); glScalef(0.002f, 0.002f, 0.001f);
    for (const char* c = "PKK"; *c != '\0'; c++) glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    glPopMatrix();
}

void drawGapura() {
    // ---------------- PILAR KIRI ----------------
   // 1. Base (Hitam 4 Block)
    glColor3fv(softBlack); glPushMatrix(); glTranslatef(-8.0f, 2.0f, -10.0f); drawBlock(3.0f, 4.0f, 3.0f); glPopMatrix();
    // 2. Body (Orange 7 Block) 
    glColor3fv(orangeColor); glPushMatrix(); glTranslatef(-8.0f, 7.5f, -10.0f); drawBlock(3.0f, 7.0f, 3.0f); glPopMatrix();
    // 3. Atap Limas 
    glColor3f(0.75f, 0.75f, 0.80f); glPushMatrix(); glTranslatef(-8.0f, 11.0f, -10.0f); drawLimas(); glPopMatrix();
    // ---------------- PILAR KANAN ----------------
    // 1. Base (Hitam 3 Block)
    glColor3fv(softBlack); glPushMatrix(); glTranslatef(8.0f, 2.0f, -10.0f); drawBlock(3.0f, 4.0f, 3.0f); glPopMatrix();
    // 2. Body (Orange 6 Block)
    glColor3fv(orangeColor); glPushMatrix(); glTranslatef(8.0f, 7.5f, -10.0f); drawBlock(3.0f, 7.0f, 3.0f); glPopMatrix();
    // 3. Atap Limas 
    glColor3f(0.75f, 0.75f, 0.80f); glPushMatrix(); glTranslatef(8.0f, 11.0f, -10.0f); drawLimas(); glPopMatrix();
    // ---------------- PENGHUBUNG ----------------
    glPushMatrix(); glTranslatef(0.0f, 9.5f, -10.0f); drawBlock(17.0f, 1.0f, 1.0f); glPopMatrix();
    glColor3fv(pitchBlack);
    drawText3D("UNIVERSITAS NEGERI SURABAYA", -5.4f, 9.3f, -9.4f, 0.005f);
    drawDiamond();
}

void drawPosSatpam() {
    // ================= 1. BAGIAN KIRI =================
    // Bawah (Batu)
    glColor3fv(stoneColor);
    glPushMatrix(); glTranslatef(-14.0f, 1.5f, -15.5f); drawBlock(3.0f, 3.0f, 7.0f); glPopMatrix();
    // Atas (Cream)
    glColor3fv(creamColor);
    glPushMatrix(); glTranslatef(-14.0f, 5.0f, -15.5f); drawBlock(3.0f, 4.0f, 7.0f); glPopMatrix();
    // ================= 2. BAGIAN KANAN DEPAN =================
    // Bawah (Batu)
    glColor3fv(stoneColor);
    glPushMatrix(); glTranslatef(-11.5f, 1.5f, -14.0f); drawBlock(2.0f, 3.0f, 4.0f); glPopMatrix();
    // Atas (Cream)
    glColor3fv(creamColor);
    glPushMatrix(); glTranslatef(-11.5f, 5.0f, -14.0f); drawBlock(2.0f, 4.0f, 4.0f); glPopMatrix();
    // ================= 3. HALAMAN & PINTU (BELAKANG) =================
    // A. ALAS PUTIH (LANTAI) - Z JADI 3
    glColor3fv(quartzColor);
    glPushMatrix(); glTranslatef(-11.5f, 0.5f, -17.5f); drawBlock(2.0f, 1.0f, 3.0f); glPopMatrix();
    // B. KANOPI ATAS (MENYESUAIKAN HALAMAN)
    glColor3fv(creamColor);
    glPushMatrix(); glTranslatef(-11.5f, 6.5f, -17.5f); drawBlock(2.0f, 1.0f, 3.0f); glPopMatrix();
    // C. TIANG PENYANGGA (MENYESUAIKAN UJUNG)
    glColor3fv(moccaColor);
    glPushMatrix(); glTranslatef(-10.6f, 3.5f, -18.9f); drawBlock(0.2f, 5.0f, 0.2f); glPopMatrix();
    // D. PINTU (HITAM)
    glColor3fv(darkGlassColor);
    glPushMatrix(); glTranslatef(-11.5f, 2.0f, -16.1f); drawBlock(1.0f, 2.0f, 0.2f); glPopMatrix();
    // ================= 4. JENDELA (HITAM) =================
    glPushMatrix(); glTranslatef(-10.4f, 4.0f, -14.0f); drawBlock(0.2f, 2.0f, 2.0f); glPopMatrix();
}

void drawMenaraAir() {
    float ZM = -60, XM = 20, YM = 12;
    // -- TIANG PENYANGGA --
    glColor3fv(TowerGreen);
    glPushMatrix(); glTranslatef(XM - 2.5f, YM, ZM - 2.5f); drawBlock(0.5f, YM * 2, 0.5f); glPopMatrix();
    glPushMatrix(); glTranslatef(XM + 2.5f, YM, ZM - 2.5f); drawBlock(0.5f, YM* 2, 0.5f); glPopMatrix();
    glPushMatrix(); glTranslatef(XM - 2.5f, YM, ZM + 2.5f); drawBlock(0.5f, YM*2, 0.5f); glPopMatrix();
    glPushMatrix(); glTranslatef(XM + 2.5f, YM, ZM + 2.5f); drawBlock(0.5f, YM*2, 0.5f); glPopMatrix();
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(XM, 1 + (i * 7), ZM);
        glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
        glScalef(3.7f, 3.7f, 3.7f);
        glLineWidth(7.0f);
        glutWireOctahedron();
        glLineWidth(1.0f); 
        glPopMatrix();
    }
    // -- ALAS ATAS --
    glPushMatrix(); glTranslatef(XM, YM + 7, ZM); drawBlock(5.0f, 0.5f, 5.0f); glPopMatrix();
    // -- TANGKI AIR --
    glColor3fv(forestGreen); 
    glPushMatrix(); glTranslatef(XM, 19.1f, ZM); drawTabung(2.5f, 4.0f, 1.5f); glPopMatrix();
    // -- TANGGA --
    glColor3fv(LightGreen);
    glPushMatrix(); glTranslatef(XM+0.5, YM-3, ZM+2.7); drawBlock(0.2f, 20, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(XM-0.5, YM-3, ZM+2.7); drawBlock(0.2f, 20, 0.2f); glPopMatrix();
    for (float dy = 0.5f; dy < 19.0f; dy += 1.0f) {
        glPushMatrix(); glTranslatef(XM, dy, ZM + 2.7); drawBlock(1.0f, 0.2f, 0.2f); glPopMatrix();
    }
}

void drawMusala() {
    // --- KOORDINAT PUSAT ---
    float posX = 110.0f;
    float posZ = -125.0f; // Pusat Gedung
    // --- DIMENSI ---
    float bodyW = 35.0f;
    float bodyD = 25.0f; // Tebal gedung (12.5 ke depan, 12.5 ke belakang)
    float bodyH = 8.0f;
    float terraceH = 1.0f;
    float terraceD = 6.0f;
    // --- WARNA ---
    float wallColor[3] = { 0.95f, 0.95f, 0.90f };
    float pillarColor[3] = { 0.90f, 0.90f, 0.85f };
    float roofColor[3] = { 0.2f, 0.5f, 0.3f };
    float glassColor[3] = { 0.2f, 0.2f, 0.2f };
    // ==========================================
    // 1. LANTAI DASAR / PODIUM
    // ==========================================
    glColor3fv(concreteColor);
    glPushMatrix();
    glTranslatef(posX, terraceH / 2.0f, posZ);
    drawBlock(bodyW + 12.0f, terraceH, bodyD + 12.0f);
    glPopMatrix();
    // ==========================================
    // 2. BADAN UTAMA GEDUNG
    // ==========================================
    glColor3fv(wallColor);
    glPushMatrix();
    glTranslatef(posX, terraceH + (bodyH / 2.0f), posZ);
    drawBlock(bodyW, bodyH, bodyD);
    glPopMatrix();
    // ==========================================
    // 3. BAGIAN DEPAN (SEKARANG MENGHADAP Z NEGATIF)
    // ==========================================
    float frontWallZ = posZ - (bodyD / 2.0f);
    float terraceCenterZ = frontWallZ - (terraceD / 2.0f);
    glPushMatrix();
    glTranslatef(posX, terraceH + 0.5f, terraceCenterZ);
    drawBlock(bodyW, 1.0f, terraceD);
    glPopMatrix();
    // --- TANGGA DEPAN ---
    glColor3fv(stoneColor);
    // Di depan teras (Lebih negatif lagi Z-nya)
    float stairZ = terraceCenterZ - (terraceD / 2.0f);
    glPushMatrix(); glTranslatef(posX, 0.2f, stairZ - 1.5f); drawBlock(10.0f, 0.4f, 2.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(posX, 0.5f, stairZ - 0.5f); drawBlock(10.0f, 0.4f, 2.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(posX, 0.8f, stairZ + 0.5f); drawBlock(10.0f, 0.4f, 2.0f); glPopMatrix();
    // --- PILAR TERAS ---
    glColor3fv(pillarColor);
    float pillarH = bodyH;
    float pillarY = terraceH + (pillarH / 2.0f);
    // Pilar Baris Depan (Paling Negatif Z)
    float pFrontZ = terraceCenterZ - 2.0f;
    // Pilar Baris Belakang (Nempel Dinding)
    float pBackZ = frontWallZ - 0.5f;
    for (float offX = -14.0f; offX <= 14.1f; offX += 9) {
        // Pilar Depan
        glPushMatrix();
        glTranslatef(posX + offX, pillarY, pFrontZ);
        drawBlock(1.2f, pillarH, 1.2f);
        glPopMatrix();
        // Pilar Belakang
        /*glPushMatrix();
        glTranslatef(posX + offX, pillarY, pBackZ);
        drawBlock(1.0f, pillarH, 1.0f);
        glPopMatrix();*/
    }
    // ==========================================
    // 4. PINTU UTAMA (DI DINDING Z NEGATIF)
    // ==========================================
    float doorZ = frontWallZ - 0.1f;
    float doorY = terraceH + 3.5f;
    // Frame
    glColor3fv(stoneColor);
    glPushMatrix(); glTranslatef(posX, doorY, doorZ); drawBlock(6.0f, 7.0f, 0.4f); glPopMatrix();
    // Daun Pintu
    glColor3fv(brownColor);
    glPushMatrix(); glTranslatef(posX, doorY, doorZ - 0.2f); drawBlock(5.0f, 6.5f, 0.2f); glPopMatrix();
    // Gagang Pintu
    glColor3fv(goldColor);
    glPushMatrix(); glTranslatef(posX - 0.5f, doorY, doorZ - 0.3f); glutSolidSphere(0.2, 10, 10); glPopMatrix();
    glPushMatrix(); glTranslatef(posX + 0.5f, doorY, doorZ - 0.3f); glutSolidSphere(0.2, 10, 10); glPopMatrix();
    // ==========================================
    // 5. JENDELA & TULISAN
    // ==========================================
    glColor3fv(glassColor);
    float winY = terraceH + 4.0f;
    // Jendela Depan (Kiri Kanan Pintu)
    glPushMatrix(); glTranslatef(posX - 8.0f, winY, doorZ); drawBlock(3.0f, 5.0f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(posX + 8.0f, winY, doorZ); drawBlock(3.0f, 5.0f, 0.2f); glPopMatrix();
    // Jendela Samping (Tidak Berubah Posisi, hanya Loop sepanjang Z)
    float sideLeftX = posX - 17.6f;
    float sideRightX = posX + 17.6f;
    for (float offZ = -8.0f; offZ <= 8.0f; offZ += 8.0f) {
        glPushMatrix(); glTranslatef(sideLeftX, winY, posZ + offZ); drawBlock(0.2f, 5.0f, 3.0f); glPopMatrix();
        glPushMatrix(); glTranslatef(sideRightX, winY, posZ + offZ); drawBlock(0.2f, 5.0f, 3.0f); glPopMatrix();
    }
    // Papan Nama
    glColor3fv(pitchBlack);
    glPushMatrix(); glTranslatef(posX, terraceH + 7.5f, doorZ - 0.2f); drawBlock(4.0f, 0.8f, 0.1f); glPopMatrix();
    glColor3fv(pureWhite);
    glPushMatrix();
    glTranslatef(posX + 1, terraceH + 7.3f, doorZ - 0.3f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f); // Putar Balik
    glScalef(0.004f, 0.004f, 0.004f);
    glLineWidth(3.0f);
    for (const char* c = "MUSHOLA"; *c != '\0'; c++) glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    glLineWidth(1.0f);
    glPopMatrix();
    // ==========================================
    // 6. ATAP LIMAS
    // ==========================================
    float roofBaseY = terraceH + bodyH;
    float roofH = 7.0f;
    float rW = (bodyW / 2.0f) + 4.0f;
    float rD = (bodyD / 2.0f) + 4.0f;
    // Geser Z atap sedikit ke arah negatif (Depan) untuk menaungi teras
    float roofCenterZ = posZ - 3.0f;
    glColor3fv(roofColor);
    glPushMatrix();
    glTranslatef(posX, roofBaseY, roofCenterZ);
    glBegin(GL_TRIANGLES);
    // Depan (Z-) -> Perhatikan urutan verteks
    glVertex3f(-rW, 0.0f, -rD); glVertex3f(rW, 0.0f, -rD);  glVertex3f(0.0f, roofH, 0.0f);
    // Belakang (Z+)
    glVertex3f(rW, 0.0f, rD);   glVertex3f(-rW, 0.0f, rD);  glVertex3f(0.0f, roofH, 0.0f);
    // Kanan (X+)
    glVertex3f(rW, 0.0f, -rD);  glVertex3f(rW, 0.0f, rD);   glVertex3f(0.0f, roofH, 0.0f);
    // Kiri (X-)
    glVertex3f(-rW, 0.0f, rD);  glVertex3f(-rW, 0.0f, -rD); glVertex3f(0.0f, roofH, 0.0f);
    glEnd();
    // Penutup Bawah
    glBegin(GL_QUADS);
    glVertex3f(-rW, 0.0f, rD); glVertex3f(rW, 0.0f, rD);
    glVertex3f(rW, 0.0f, -rD); glVertex3f(-rW, 0.0f, -rD);
    glEnd();
    glPopMatrix();
    // Kubah
    glColor3fv(goldColor);
    glPushMatrix();
    glTranslatef(posX, roofBaseY + roofH, roofCenterZ);
    glutSolidSphere(1.2f, 16, 16);
    glTranslatef(0.0f, 1.2f, 0.0f);
    glutSolidSphere(0.6f, 16, 16);
    glPopMatrix();
}

void drawLorong() {
    // A4 
    glPushMatrix();
    glTranslatef(70.0f, 0.0f, -162.0f); 
    drawWalkway(50.0f, 7); 
    glPopMatrix();
	// A3
    glPushMatrix();
    glTranslatef(39.0f, 0.0f, -159.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    drawWalkway(56.0f, 8.5);
    glPopMatrix();
	// A2
    glPushMatrix();
    glTranslatef(55.0f, 0.0f, -102.5f);
    drawWalkway(20.0f, 9);
    glPopMatrix();
	// A1
    glPushMatrix();
    glTranslatef(55.0f, 0.0f, -57.5f);
    drawWalkway(20.0f, 9);
    glPopMatrix();
    glColor3fv(softBlack);
    for (float dz = -163; dz < -154; dz += 1.0f) {
        glPushMatrix();
        glTranslatef(9, 0.5, dz);
        drawBlock(0.2, 1, 0.2);
        glPopMatrix();
    }
    glColor3fv(safetyYellow);
    for (float dz = -163; dz < -154; dz += 1.0f) {
        glPushMatrix();
        glTranslatef(9, 1.5, dz);
        drawBlock(0.2, 1, 0.2);
        glPopMatrix();
    }
    glColor3fv(pureWhite);
    for (float dz = -153; dz < -141; dz += 2.0f) {
        glPushMatrix();
        glTranslatef(8, -0.3, dz);
        drawBola(1, 1, 1, 0.7);
        glPopMatrix();
    }
}

void drawE1() {
    float ZE = -350;
    float XE = 200;
    float YE = 9;
    // -- BADAN GEDUNG & ATAP --
    glColor3fv(roofTileColor); // ATAP
    glPushMatrix(); glTranslatef(XE, YE + 11, ZE); drawAtap(53, 26, 7); glPopMatrix();
    glColor3fv(LightGreen);
    glPushMatrix(); glTranslatef(XE, YE + 10, ZE); drawBlock(56, 2, 29); glPopMatrix();
    glColor3fv(DarkGreen);
    glPushMatrix(); glTranslatef(XE, YE, ZE); drawBlock(52, 18, 25); glPopMatrix();
    // -- BAGIAN DEPAN --
    glPushMatrix(); glTranslatef(XE, YE-2, ZE+13); drawBlock(10, 15, 1); glPopMatrix();
    glColor3fv(LightGreen);
    glPushMatrix(); glTranslatef(XE+4.5, YE-2, ZE + 13.6); drawBlock(1, 15, 0.1); glPopMatrix();
    glPushMatrix(); glTranslatef(XE-4.5, YE-2, ZE + 13.6); drawBlock(1, 15, 0.1); glPopMatrix();
    glPushMatrix(); glTranslatef(XE, YE + 6, ZE + 13.6); drawBlock(10, 1, 0.1); glPopMatrix();
    // -- KANOPI & PILAR & ALAS --
    glPushMatrix(); glTranslatef(XE, YE - 4, ZE + 17); drawBlock(10, 1, 7); glPopMatrix();
    glPushMatrix(); glTranslatef(XE + 4.5, YE - 7, ZE + 19); drawBlock(1, 5, 0.5); glPopMatrix();
    glPushMatrix(); glTranslatef(XE - 4.5, YE - 7, ZE + 19); drawBlock(1, 5, 0.5); glPopMatrix();
    glColor3fv(creamColor);
    glPushMatrix(); glTranslatef(XE, YE - 9.3, ZE + 17); drawBlock(10, 1, 7); glPopMatrix();
    // -- ORNAMEN DEPAN --
    glColor3fv(sageGreen);
    for (float dx = 185; dx < 217; dx += 5.0f) {
        glPushMatrix(); glTranslatef(dx, YE, ZE + 12.5); drawBlock(0.5, 18, 0.2); glPopMatrix();
    }
    glColor3fv(forestGreen);
    for (float dy = 5; dy < 16; dy += 5.0f) {
        glPushMatrix(); glTranslatef(XE, dy, ZE + 12.5); drawBlock(38, 1, 0.5); glPopMatrix();
    }
    // -- TULISAN --
    glColor3fv(iceWhiteColor); 
    // ================= BARIS 1 =================
    glPushMatrix();
    glTranslatef(XE-0.7, YE + 2, ZE + 13.6f); glScalef(0.003f, 0.003f, 0.003f); glLineWidth(3.0f); 
    for (const char* c = "UNESA"; *c != '\0'; c++) glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    glPopMatrix();
    // ================= BARIS 2 =================
    glPushMatrix();
    glTranslatef(XE-3.5, YE+1, ZE + 13.6f); glScalef(0.006f, 0.006f, 0.006f); glLineWidth(4.0f); 
    for (const char* c = "FAKULTAS TEKNIK"; *c != '\0'; c++) glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    glPopMatrix();
    // ================= BARIS 3 =================
    glPushMatrix();
    glTranslatef(XE-3.3, YE, ZE + 13.6f); glScalef(0.003f, 0.004f, 0.004f); glLineWidth(3.0f);
    for (const char* c = "UNIVERSITAS NEGERI SURABAYA"; *c != '\0'; c++) glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    glPopMatrix();
	// -- JENDELA --
	glColor3fv(darkGlassColor);
    for (float dx = 177.5; dx < 225.0f; dx += 5.0f) {
        for (float dy = 3.5f; dy < 14.0f; dy += 5.0f) {
            glPushMatrix(); glTranslatef(dx, dy, ZE+12.5); drawBlock(3.0f, 1.0f, 0.2f); glPopMatrix();
        }
    }
	// -- PINTU DEPAN --
    glColor3fv(doorGlassColor);
    glPushMatrix(); glTranslatef(XE, 1.25f, ZE + 13.6f); drawBlock(3.0f, 2.5f, 0.2f); glPopMatrix();
    // ORNAMEN PINTU (FRAME SAGE)
    glColor3fv(sageGreen);
    glPushMatrix();
    glTranslatef(XE - 1.7f, 1.25f, ZE + 13.7f);
    drawBlock(0.4f, 2.5f, 0.4f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(XE + 1.7f, 1.25f, ZE + 13.7f);
    drawBlock(0.4f, 2.5f, 0.4f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(XE, 2.7f, ZE + 13.7f);
    drawBlock(3.8f, 0.4f, 0.4f);
    glPopMatrix();
    // ================= BAGIAN SAMPING =================
    // -- ORNAMEN PINTU --
    glPushMatrix(); glTranslatef(XE, 2.7f, ZE); drawBlock(52.8f, 0.4f, 3.8f); glPopMatrix();
    glPushMatrix(); glTranslatef(XE, 1.25f, ZE - 1.7f); drawBlock(52.8f, 2.5f, 0.4f); glPopMatrix();
    glPushMatrix(); glTranslatef(XE, 1.25f, ZE + 1.7f); drawBlock(52.8f, 2.5f, 0.4f); glPopMatrix();
    // -- PINTU --
    glColor3fv(doorGlassColor);
    glPushMatrix(); glTranslatef(XE, 1.25f, ZE); drawBlock(52.4f, 2.5f, 3.0f); glPopMatrix();
	// -- ALAS --
    glColor3fv(creamColor);
	glPushMatrix(); glTranslatef(XE, 0, ZE); drawBlock(56, 0.5, 4); glPopMatrix();
    // -- PILAR --
	glColor3fv(LightGreen);
    glPushMatrix(); glTranslatef(XE, YE, ZE+3); drawBlock(53, 18, 1); glPopMatrix();
    glPushMatrix(); glTranslatef(XE, YE, ZE-3); drawBlock(53, 18, 1); glPopMatrix();
}

void drawA1() {
    float centerX = 45.0f;
    float centerZ = -35.0f;
    float sizeX = 56.0f;
    float sizeY = 15.0f;
    float sizeZ = 26.0f;
    float wallX = 17.0f;
    // --- BADAN GEDUNG ---
    glColor3fv(creamColor);  glPushMatrix(); glTranslatef(centerX, 7.5f, centerZ); drawBlock(sizeX, sizeY, sizeZ); glPopMatrix();
    // --- JENDELA SAMPING ---
    glColor3f(0.6f, 0.8f, 0.9f);
    for (float dx = 23.0f; dx < 71.0f; dx += 6.0f) {
        for (float dy = 3.5f; dy < 14.0f; dy += 4.0f) {
            glPushMatrix();
            glTranslatef(dx, dy, centerZ - 13.1f);
            drawBlock(2.0f, 3.0f, 0.2f);
            glPopMatrix();
            glPushMatrix();
            glTranslatef(dx, dy, centerZ + 13.1f);
            drawBlock(2.0f, 3.0f, 0.2f);
            glPopMatrix();
        }
    }
    // ================= BAGIAN TERAS (DEPAN) =================
    float terraceWidthZ = 10.0f;
    float terraceCenterX = 15.0f;
    // --- ALAS / TERAS (LEBAR 4 BLOCK) ---
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(terraceCenterX, 0.5f, centerZ);
    drawBlock(4.0f, 1.0f, terraceWidthZ); // Lebar X jadi 4.0
    glPopMatrix();
    // --- PINTU KACA ---
    glColor3fv(doorGlassColor);
    glPushMatrix();
    glTranslatef(16.9f, 2.25f, centerZ);
    drawBlock(0.2f, 2.5f, 3.0f);
    glPopMatrix();
    // --- ORNAMEN PINTU (MARMER SAGE) ---
    glColor3f(0.55f, 0.65f, 0.55f);
    float ornamentX = 16.75f;
    // Tiang Kiri & Kanan
    glPushMatrix();
    glTranslatef(ornamentX, 2.25f, centerZ - 1.7f);
    drawBlock(0.5f, 2.5f, 0.4f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(ornamentX, 2.25f, centerZ + 1.7f);
    drawBlock(0.5f, 2.5f, 0.4f);
    glPopMatrix();
    // Balok Atas
    glPushMatrix();
    glTranslatef(ornamentX, 3.7f, centerZ);
    drawBlock(0.5f, 0.4f, 3.8f);
    glPopMatrix();
    // --- KANOPI (LEBAR 4 BLOCK) ---
    glColor3fv(silverDark);
    glPushMatrix();
    glTranslatef(terraceCenterX, 5.5f, centerZ);
    drawBlock(4.0f, 1.0f, terraceWidthZ); // Lebar X jadi 4.0
    glPopMatrix();
    // --- ORNAMEN TAMBAHAN DI ATAS KANOPI (MOCCA) ---
    glColor3f(0.75f, 0.60f, 0.50f);
    // Pilar Panjang Kiri
    glPushMatrix();
    glTranslatef(ornamentX, 10.5f, centerZ - 1.7f);
    drawBlock(0.2f, 9.0f, 1.0f);
    glPopMatrix();
    // Pilar Panjang Kanan
    glPushMatrix();
    glTranslatef(ornamentX, 10.5f, centerZ + 1.7f);
    drawBlock(0.2f, 9.0f, 1.0f);
    glPopMatrix();
    // --- ORNAMEN ---
    glColor3fv(brownColor); 
    float frameX = 16.85f;
    glPushMatrix();
    glTranslatef(frameX, 7.5f, centerZ - 11.5f);
    drawBlock(0.1f, 15.0f, 1.0f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(frameX, 7.5f, centerZ + 11.5f);
    drawBlock(0.1f, 15.0f, 1.0f);
    glPopMatrix();
    glPushMatrix();
    // --- TULISAN ---
    glColor3fv(greyColor);
    glPushMatrix();
    glTranslatef(12.9f, 5.3f, centerZ - 1.5f);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.003f, 0.004f, 0.004f);
    glLineWidth(3.0f);
    for (const char* c = "JURUSAN PKK"; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glLineWidth(1.0f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(16.9f, 8.0f, -30.0f);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.010f, 0.010f, 0.010f);
    glLineWidth(3.0f);
    for (const char* c = "A1"; *c != '\0'; c++) glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    glLineWidth(1.0f);
    glPopMatrix();
    // --- TIANG PENYANGGA KANOPI (Margin 1 block) ---
    glColor3f(0.75f, 0.60f, 0.50f);
    glPushMatrix();
    glTranslatef(14, 3.0f, centerZ - 4.0f);
    drawBlock(0.4f, 4.0f, 0.4f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(14, 3.0f, centerZ + 4.0f);
    drawBlock(0.4f, 4.0f, 0.4f);
    glPopMatrix();
    // --- TANGGA DEPAN (Maju mengikuti alas) ---
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    // X digeser ke 12.5f (Di depan alas 13.0)
    glTranslatef(12.5f, 0.25f, centerZ);
    drawBlock(1.0f, 0.5f, terraceWidthZ);
    glPopMatrix();
    // --- 2. ATAP LIMAS (PYRAMID) ---
    glColor3fv(roofTileColor);
    glPushMatrix();
    glTranslatef(centerX, 15, centerZ);
	drawAtap(sizeX + 2.0f, sizeZ + 2.0f, 6);
    glPopMatrix();
}

void drawA2() {
    float centerX = 55.0f;
    float centerZ = -80.0f;
    float sizeX = 56.0f;
    float sizeY = 15.0f;
    float sizeZ = 26.0f;
    float wallX = 17.0f;
    // --- BADAN GEDUNG ---
    glColor3fv(creamColor);  glPushMatrix(); glTranslatef(centerX, 7.5f, centerZ); drawBlock(sizeX, sizeY, sizeZ); glPopMatrix();
    // --- JENDELA SAMPING ---
    glColor3fv(doorGlassColor); 
    for (float dx = 31.0f; dx < 82.0f; dx += 8.0f) { // Jarak antar jendela diperlebar (8.0f)
        for (float dy = 4.0f; dy < 14.0f; dy += 5.0f) {
            glPushMatrix();
            glTranslatef(dx, dy, centerZ + 13.1f); // Sedikit menonjol dari dinding depan
            drawBlock(2.5f, 3.5f, 0.2f);
            glPopMatrix();
            glPushMatrix();
            glTranslatef(dx, dy, centerZ - 13.1f); // Sedikit menonjol dari dinding belakang
            drawBlock(2.5f, 3.5f, 0.2f);
            glPopMatrix();
        }
    }
    // ================= BAGIAN TERAS (SAMPING SEBALIKNYA) =================
    float sideTerraceX = 55.0f;
    float oppositeWallZ = -93.0f;   // Posisi dinding belakang
    float terraceDepth = 4.0f;
    float terraceWidth = 10.0f;
    float currentTerraceZ = oppositeWallZ - (terraceDepth / 2.0f);
    float frameX = 16.85f;
    // --- ORNAMEN MENGHADAP JALAN ---
    glColor3fv(brownColor);
    glPushMatrix(); glTranslatef(26.9f, 7.5f, centerZ + 2); drawBlock(0.1f, 15.0f, 1.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(26.9f, 7.5f, centerZ + 12); drawBlock(0.1f, 15.0f, 1.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(26.9f, 7.5f, centerZ - 2); drawBlock(0.1f, 15.0f, 1.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(26.9f, 7.5f, centerZ - 12); drawBlock(0.1f, 15.0f, 1.0f); glPopMatrix();
    // --- ALAS / TERAS ---
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(sideTerraceX, 0.5f, currentTerraceZ);
    drawBlock(terraceWidth, 1.0f, terraceDepth);
    glPopMatrix();
    // --- PINTU KACA (Di dinding) ---
    glColor3fv(doorGlassColor);
    glPushMatrix();
    // Z dikurangi sedikit (-0.1) agar tidak flickering dengan dinding
    glTranslatef(sideTerraceX, 2.25f, oppositeWallZ - 0.1f);
    drawBlock(3.0f, 2.5f, 0.2f);
    glPopMatrix();
    // --- ORNAMEN PINTU (MARMER SAGE) ---
    glColor3f(0.55f, 0.65f, 0.55f);
    float doorGap = 1.7f;
    // Tiang Pintu
    glPushMatrix();
    glTranslatef(sideTerraceX - doorGap, 2.25f, oppositeWallZ - 0.2f);
    drawBlock(0.4f, 2.5f, 0.5f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(sideTerraceX + doorGap, 2.25f, oppositeWallZ - 0.2f);
    drawBlock(0.4f, 2.5f, 0.5f);
    glPopMatrix();
    // Balok Atas Pintu
    glPushMatrix();
    glTranslatef(sideTerraceX, 3.7f, oppositeWallZ - 0.2f);
    drawBlock(3.8f, 0.4f, 0.5f);
    glPopMatrix();
    // --- KANOPI ATAS ---
    glColor3f(0.60f, 0.60f, 0.65f);
    glPushMatrix();
    glTranslatef(sideTerraceX, 5.5f, currentTerraceZ);
    drawBlock(terraceWidth, 1.0f, terraceDepth);
    glPopMatrix();
    // --- TIANG PENYANGGA KANOPI (Di ujung luar) ---
    glColor3f(0.75f, 0.60f, 0.50f);
    // Posisi Z ada di ujung paling luar (semakin negatif)
    float pillarZ = oppositeWallZ - terraceDepth + 0.5f;
    float pillarDistX = 4.0f;
    glPushMatrix();
    glTranslatef(sideTerraceX - pillarDistX, 3.0f, pillarZ);
    drawBlock(0.4f, 4.0f, 0.4f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(sideTerraceX + pillarDistX, 3.0f, pillarZ);
    drawBlock(0.4f, 4.0f, 0.4f);
    glPopMatrix();
    // --- ORNAMEN PILAR PANJANG (Mocca) ---
    glPushMatrix();
    glTranslatef(sideTerraceX - doorGap, 10.5f, oppositeWallZ - 0.2f);
    drawBlock(1.0f, 9.0f, 0.2f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(sideTerraceX + doorGap, 10.5f, oppositeWallZ - 0.2f);
    drawBlock(1.0f, 9.0f, 0.2f);
    glPopMatrix();
    // --- TULISAN "A2" DI DINDING SAMPING KIRI ---
    glColor3fv(greyColor);
    glPushMatrix();
    glTranslatef(26.9f, 8.0f, -80.9f);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.01f, 0.01f, 0.01f);
    glLineWidth(4.0f); 
    for (const char* c = "A2"; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glLineWidth(1.0f); 
    glPopMatrix();
    // --- TANGGA (Di ujung paling luar) ---
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslatef(sideTerraceX, 0.25f, currentTerraceZ - (terraceDepth / 2.0f) - 0.5f);
    drawBlock(terraceWidth, 0.5f, 1.0f);
    glPopMatrix();
    // --- ATAP ---
    glColor3fv(roofTileColor);
    glPushMatrix();
    glTranslatef(centerX, 15, centerZ);
    drawAtap(sizeX + 2.0f, sizeZ + 2.0f, 6);
    glPopMatrix();
}

void drawA3() {
    float centerX = 55.0f, centerZ = -125.0f;
	float sizeX = 56.0f, sizeY = 15.0f, sizeZ = 26.0f;
    // --- BADAN GEDUNG ---
    glColor3fv(creamColor);
    glPushMatrix();
    glTranslatef(centerX, 7.5f, centerZ);
    drawBlock(sizeX, sizeY, sizeZ);
    glPopMatrix();
    // --- JENDELA SAMPING ---
    glColor3fv(doorGlassColor);
    for (float dx = 31; dx < 82; dx += 8.0f) {
        for (float dy = 4.0f; dy < 14.0f; dy += 5.0f) {
            // Jendela Sisi Depan
            glPushMatrix();
            glTranslatef(dx, dy, centerZ + 13.1f);
            drawBlock(2.5f, 3.5f, 0.2f);
            glPopMatrix();
            // Jendela Sisi Belakang
            glPushMatrix();
            glTranslatef(dx, dy, centerZ - 13.1f);
            drawBlock(2.5f, 3.5f, 0.2f);
            glPopMatrix();
        }
    }
    // ================= BAGIAN TERAS =================
    float sideTerraceX = centerX;           // Posisi teras mengikuti pusat gedung (55.0f)
    float sideWallZ = centerZ + 13.0f;
    float terraceDepth = 4.0f;
    float terraceWidth = 10.0f;
    float currentTerraceZ = sideWallZ + (terraceDepth / 2.0f);
    // --- ALAS / TERAS ---
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(sideTerraceX, 0.5f, currentTerraceZ);
    drawBlock(terraceWidth, 1.0f, terraceDepth);
    glPopMatrix();
    // --- PINTU KACA ---
    glColor3fv(doorGlassColor);
    glPushMatrix();
    glTranslatef(sideTerraceX, 2.25f, sideWallZ + 0.1f);
    drawBlock(3.0f, 2.5f, 0.2f);
    glPopMatrix();
    // --- ORNAMEN PINTU ---
    glColor3f(0.55f, 0.65f, 0.55f);
    float doorGap = 1.7f;
    // Tiang Pintu & Balok Atas
    glPushMatrix(); glTranslatef(sideTerraceX - doorGap, 2.25f, sideWallZ + 0.2f); drawBlock(0.4f, 2.5f, 0.5f); glPopMatrix();
    glPushMatrix(); glTranslatef(sideTerraceX + doorGap, 2.25f, sideWallZ + 0.2f); drawBlock(0.4f, 2.5f, 0.5f); glPopMatrix();
    glPushMatrix(); glTranslatef(sideTerraceX, 3.7f, sideWallZ + 0.2f); drawBlock(3.8f, 0.4f, 0.5f); glPopMatrix();
    // --- KANOPI ATAS ---
    glColor3f(0.60f, 0.60f, 0.65f);
    glPushMatrix();
    glTranslatef(sideTerraceX, 5.5f, currentTerraceZ);
    drawBlock(terraceWidth, 1.0f, terraceDepth);
    glPopMatrix();
    // --- TIANG PENYANGGA KANOPI ---
    glColor3f(0.75f, 0.60f, 0.50f);
    float pillarZ = sideWallZ + terraceDepth - 0.5f;
    float pillarDistX = 4.0f;
    glPushMatrix(); glTranslatef(sideTerraceX - pillarDistX, 3.0f, pillarZ); drawBlock(0.4f, 4.0f, 0.4f); glPopMatrix();
    glPushMatrix(); glTranslatef(sideTerraceX + pillarDistX, 3.0f, pillarZ); drawBlock(0.4f, 4.0f, 0.4f); glPopMatrix();
    // --- ORNAMEN PILAR PANJANG ---
    glPushMatrix(); glTranslatef(sideTerraceX - doorGap, 10.5f, sideWallZ + 0.2f); drawBlock(1.0f, 9.0f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(sideTerraceX + doorGap, 10.5f, sideWallZ + 0.2f); drawBlock(1.0f, 9.0f, 0.2f); glPopMatrix();
    // --- TANGGA ---
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslatef(sideTerraceX, 0.25f, currentTerraceZ + (terraceDepth / 2.0f) + 0.5f);
    drawBlock(terraceWidth, 0.5f, 1.0f);
    glPopMatrix();
    // --- ATAP ---
    glColor3fv(roofTileColor);
    glPushMatrix();
    glTranslatef(centerX, 15, centerZ);
    drawAtap(sizeX + 2.0f, sizeZ + 2.0f, 6);
    glPopMatrix();
    // ================= BAGIAN SAMPING MENGHADAP JALAN =================
	// --- TULISAN ---
    float leftWallX = centerX - (sizeX / 2.0f) - 0.2f;
    glColor3fv(greyColor);
    glPushMatrix();
    glTranslatef(leftWallX, 6.0f, centerZ+6);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.012f, 0.012f, 0.012f); 
    glLineWidth(4.0f);
    for (const char* c = "A3"; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(leftWallX, 9.0f, centerZ-11.8);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.009f, 0.009f, 0.009f);
    for (const char* c = "PENDIDIKAN KESEJAHTERAAN KELUARGA"; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glLineWidth(1.0f);
    glPopMatrix();
    // --- ORNAMEN MENGHADAP JALAN ---
    glColor3fv(brownColor);
    glPushMatrix(); glTranslatef(26.9f, 7.5f, centerZ+2); drawBlock(0.1f, 15.0f, 1.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(26.9f, 7.5f, centerZ+12); drawBlock(0.1f, 15.0f, 1.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(26.9f, 7.5f, centerZ-2); drawBlock(0.1f, 15.0f, 1.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(26.9f, 7.5f, centerZ-12); drawBlock(0.1f, 15.0f, 1.0f); glPopMatrix();
    for (float dy = 8.5f; dy < 10.5f; dy += 0.3f) {
        glPushMatrix();
        glTranslatef(26.9, dy, centerZ);
        drawBlock(0.1, 0.1f, 25);
        glPopMatrix();
    }
}

void drawA4() {
    float centerX = 70.0f, centerZ = -220.0f;
    float sizeX = 50.0f, sizeY = 13.0f, sizeZ = 70.0f;
    // ============================
    // 1. BADAN GEDUNG
    // ============================
    glColor3f(0.93f, 0.88f, 0.80f);
    glPushMatrix();
    glTranslatef(centerX, sizeY / 2, centerZ);
    drawBlock(sizeX, sizeY, sizeZ);
    glPopMatrix();
    // ============================
    // DEPAN GEDUNG = ARAH –Y
    // ============================
    float frontY = centerZ - sizeZ / 2 - 0.15f;
    float cx = centerX;
    // ============================
// GARIS HIJAU PEMISAH LANTAI (A4)
// ============================
// Warna hijau khas A4 Unesa
    glColor3f(0.10f, 0.60f, 0.32f);
    float greenY1 = 7.0f;
    float greenY2 = sizeY - 1.5f;
    float greenThickness = 0.5f;
    // ============================
    // Garis Hijau Bawah
    // ============================
    glPushMatrix();
    glTranslatef(centerX, greenY1, centerZ - (sizeZ / 2) - 0.05f);  // arah depan (-Z)
    drawBlock(sizeX + 1.0f, 1.0f, greenThickness);
    glPopMatrix();
    // ============================
    // Garis Hijau Atas
    // ============================
    glPushMatrix();
    glTranslatef(centerX, greenY2, centerZ - (sizeZ / 2) - 0.05f);
    drawBlock(sizeX + 1.0f, 1.0f, greenThickness);
    glPopMatrix();
    // ============================
    // Garis Hijau Samping Kiri
    // ============================
    glPushMatrix();
    glTranslatef(centerX - (sizeX / 2) - 0.05f, 12.5f, centerZ);
    drawBlock(greenThickness, 1.0f, sizeZ + 1.0f);
    glPopMatrix();
    // ============================
// Garis Hijau Samping Kanan
// ============================
    glPushMatrix();
    glTranslatef(centerX + (sizeX / 2) + 0.05f, 12.5f, centerZ);
    drawBlock(greenThickness, 1.0f, sizeZ + 1.0f);
    glPopMatrix();
    // ============================
// Garis Hijau Belakang (opsional)
// ============================
    glPushMatrix();
    glTranslatef(centerX, 12.5f, centerZ + (sizeZ / 2) + 0.05f);
    drawBlock(sizeX + 1.0f, 1.0f, greenThickness);
    glPopMatrix();
    // ============================
// Garis Coklat Horizontal Besar
// ============================
    glColor3f(0.45f, 0.25f, 0.15f);   // coklat tua
    glPushMatrix();
    glTranslatef(cx, 6.3f, frontY - 0.25f);   // posisi tepat di bawah papan abu
    glRotatef(180, 0, 1, 0);
    drawBlock(sizeX - 25.0f, 1.0f, 0.5f);
    glPopMatrix();
    // ============================
    // Kolom-Kolom Vertikal Coklat
    // ============================
    int cols = 7;                  // jumlah kolom
    float spacing = (sizeX - 8.0f) / (cols - 1); // otomatis merata
    for (int i = 0; i < cols; i++) {
        float px = cx - (sizeX / 2) + 4.0f + i * spacing;
        glPushMatrix();
        glColor3f(0.45f, 0.25f, 0.15f);
        glTranslatef(px, 3.0f, frontY - 0.3f);   // tinggi mulai dari tanah
        glRotatef(180, 0, 1, 0);
        drawBlock(1.0f, 7.0f, 0.25f);            // tipis tapi tinggi
        glPopMatrix();
    }
    // ============================
// Garis Coklat Horizontal Besar (LANTAI 2)
// ============================
    glColor3f(0.45f, 0.25f, 0.15f);   // coklat tua
    glPushMatrix();
    glTranslatef(cx, 12.5f, frontY - 0.25f);   // posisi DI ATAS papan putih
    glRotatef(180, 0, 1, 0);
    drawBlock(sizeX - 1.0f, 1.0f, 0.5f);
    glPopMatrix();

    // ============================
// Kolom-Kolom Vertikal Coklat (LANTAI 2)
// ============================
    int cols2 = 7;
    float spacing2 = (sizeX - 8.0f) / (cols2 - 1);
    for (int i = 0; i < cols2; i++) {
        float px = cx - (sizeX / 2) + 4.0f + i * spacing2;
        glPushMatrix();
        glColor3f(0.45f, 0.25f, 0.15f);
        glTranslatef(px, 9.5f, frontY - 0.3f); // naik 0.5   // naik 6 unit dari kolom lantai 1
        glRotatef(180, 0, 1, 0);
        drawBlock(1.0f, 4.0f, 0.25f);            // sedikit lebih pendek dari lantai 1
        glPopMatrix();
    }
    // ============================
       // 2. PINTU DEPAN (arah –Y)
       // ============================
    glColor3f(0.25f, 0.35f, 0.45f);
    glPushMatrix();
    glTranslatef(cx, 3.0f, frontY);
    glRotatef(180, 0, 1, 0);  // ★ Menghadap –Y
    drawBlock(10.0f, 5.0f, 0.3f);
    glPopMatrix();
    // ============================
    // 3. PAPAN “TEKNIK SIPIL”
    // ============================
    glColor3fv(iceWhiteColor);
    glPushMatrix();
    glTranslatef(cx, 7.0f, frontY - 1.5f);
    glRotatef(180, 0, 1, 0);  // ★ Fasad –Y
    drawBlock(10, 1.5f, 3.0f);
    glPopMatrix();
    // 4. PAPAN “A4”
    for (float dx = 65; dx < 75; dx += 0.2f) {
        glPushMatrix();
        glTranslatef(dx, 9, frontY - 3.0f);
        drawBlock(0.1, 3, 0.1);
        glPopMatrix();
    }
    // -- ALAS DEPAN PINTU --
    glPushMatrix(); glTranslatef(cx, 0.0f, frontY - 1.5f); drawBlock(10, 0.5f, 3.0f); glPopMatrix();
    // ============================
 // TULISAN "TEKNIK SIPIL"
 // ============================
    glColor3f(0.55f, 0.55f, 0.55f); 
    glPushMatrix(); glTranslatef(cx + 4.0f, 6.5f, frontY - 3.1f); glRotatef(180, 0, 1, 0); glScalef(0.010f, 0.010f, 0.010f);
    glLineWidth(3.0f);
    for (const char* c = "TEKNIK SIPIL"; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glLineWidth(1.0f);
    glPopMatrix();
    glPushMatrix(); glTranslatef(cx+1, 8, frontY - 3.1f); glRotatef(180, 0, 1, 0); glScalef(0.010f, 0.010f, 0.010f);
    glLineWidth(5.0f);
    for (const char* c = "A4"; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glLineWidth(1.0f);
    glPopMatrix();
    // ============================
    // 5. JENDELA DEPAN
    // ============================
    glColor3f(0.55f, 0.75f, 0.90f);
    for (float dx = centerX - 17.5f; dx < centerX + 20.0f; dx += 7.0f) {
        for (float dy = 3.5f; dy < 11.0f; dy += 5.0f) {
            glPushMatrix();
            glTranslatef(dx, dy, centerZ - 35.0f); // Pastikan posisi Z ini benar sesuai tembok
            drawBlock(2.5f, 3.5f, 0.2f);
            glPopMatrix();
        }
    }
    // ============================
 // 6. ATAP LIMAS
 // ============================
    glColor3fv(roofTileColor);
    glPushMatrix();
    glTranslatef(centerX, 13, centerZ);
    drawAtap(50, 70, 6);
    glPopMatrix();
    // --- JENDELA SAMPING (DINAMIS) ---
    float startWindow = centerZ - 28.0f;
    float endWindow = centerZ + 30.0f;
    glColor3f(0.6f, 0.8f, 0.9f);
    for (float dz = startWindow; dz < endWindow; dz += 8.0f) {
        for (float dy = 4.0f; dy < 14.0f; dy += 5.0f) {
            // Jendela Sisi Depan
            glPushMatrix();
            glTranslatef(centerX+25.1, dy, dz);
            drawBlock(0.2f, 3.5f, 2.5f);
            glPopMatrix();
            // Jendela Sisi Belakang
            glPushMatrix();
            glTranslatef(centerX-25.1, dy, dz);
            drawBlock(0.2f, 3.5f, 2.5f);
            glPopMatrix();

        }
    }
	// TIANG KECIL DI TROTOAR DEPAN
    glColor3fv(softBlack);
    for (float dx = 66; dx < 75; dx += 1.0f) {
        glPushMatrix();
        glTranslatef(dx, 0.5, -278.5);
        drawBlock(0.2, 1, 0.2);
        glPopMatrix();
    }
    glColor3fv(safetyYellow);
    for (float dx = 66; dx < 75; dx += 1.0f) {
        glPushMatrix();
        glTranslatef(dx, 1.5, -278.5);
        drawBlock(0.2, 1, 0.2);
        glPopMatrix();
    }
    // === BAGIAN SAMPING ===
    glColor3fv(maroonColor);
    glPushMatrix();
    glTranslatef(cx-25.5, sizeY/2, centerZ);
    drawBlock(0.2, sizeY, 15);
    glPopMatrix();
    float gap = 5.0f;
    // TANGGA 
    glPushMatrix(); drawStairUnit(cx - 33.6, 0.0f, centerZ - 2.0f, false); glPopMatrix();
    glPushMatrix(); drawIndustrialStaircase(cx-33.6, 0.0f, centerZ + 2.0f, false); glPopMatrix();
    glPushMatrix();
    glTranslatef(cx - 29, 2.5, centerZ-13);
    drawBlock(10, 5, 0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(cx - 29, 2.5, centerZ + 13);
    drawBlock(10, 5, 0.5);
    glPopMatrix();
    // PINTU & PILAR & ALAS
    glColor3fv(brownColor);
    glPushMatrix();
    glTranslatef(cx - 25.5, sizeY/2, centerZ + 3);
    drawBlock(0.5, sizeY, 0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(cx - 25.5, sizeY/2, centerZ - 3);
    drawBlock(0.5, sizeY, 0.5);
    glPopMatrix();
    glPopMatrix();
	glColor3fv(moccaColor);
    glPushMatrix();
    glTranslatef(cx - 27.5, 8, centerZ);
    drawBlock(4, 0.5, 5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(cx - 27.5, 0.25, centerZ);
    drawBlock(4, 0.5, 5);
    glPopMatrix();
    glColor3fv(doorGlassColor);
    glPushMatrix();
    glTranslatef(cx - 25.7, 9.5, centerZ);
    drawBlock(0.2, 3, 3);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(cx - 25.7, 2, centerZ);
    drawBlock(0.2, 3, 3);
    glPopMatrix();
	// === BAGIAN BELAKANG ===
    glColor3fv(doorGlassColor);
    glPushMatrix();
    glTranslatef(cx, 1.75, centerZ + 35.1);
    drawBlock(3.0f, 3.5, 0.2f);
    glPopMatrix();
    // 2. ORNAMEN PINTU (Frame Sage Green)
    glColor3fv(sageGreen);
    // Tiang Kiri
    glPushMatrix();
    glTranslatef(cx - 1.7f, 1.75, centerZ + 35.2);
    drawBlock(0.4f, 3.5, 0.4f);
    glPopMatrix();
    // Tiang Kanan
    glPushMatrix();
    glTranslatef(cx + 1.7f, 1.75, centerZ + 35.2);
    drawBlock(0.4f, 3.5f, 0.4f);
    glPopMatrix();
    // Balok Atas (Topi Pintu)
    glPushMatrix();
    glTranslatef(cx, 3.7f, centerZ + 35.2);
    drawBlock(3.8f, 0.4f, 0.4f);
    glPopMatrix();
}

void drawA5() {
    float cx = 180.0f, cz = -240.0f;
    float W = 70.0f, H = 30.0f, D = 30.0f;
    float halfW = W * 0.5f;
    float halfD = D * 0.5f;
    float frontZ = cz - halfD;
    float backZ = cz + halfD;
    // ============================
    // 1. BADAN GEDUNG
    // ============================
    glColor3fv(creamColor);
    glPushMatrix();
    glTranslatef(cx, H * 0.5f, cz);
    drawBlock(W, H, D);
    glPopMatrix();
    // ===================================
    //   PANEL SAMPING KANAN A5 (DUA PANEL)
    // ===================================
    float panelThickness = 0.3f;
    float singlePanelWidth = 6.0f;   // lebar 1 panel oranye
    float panelHeight = H;
    float xRightPanel = cx + halfW - 0.05f;
    // PANEL 1
    glColor3f(0.70f, 0.35f, 0.15f);
    glPushMatrix();
    glTranslatef(xRightPanel, panelHeight * 0.5f, cz - (singlePanelWidth * 0.75f));
    drawBlock(panelThickness, panelHeight, singlePanelWidth);
    glPopMatrix();
    // PANEL 2 (di sampingnya)
    glColor3f(0.70f, 0.35f, 0.15f);
    glPushMatrix();
    glTranslatef(xRightPanel, panelHeight * 0.5f, cz + (singlePanelWidth * 0.75f));
    drawBlock(panelThickness, panelHeight, singlePanelWidth);
    glPopMatrix();
    // STRIP HORIZONTAL (dua panel)
    glColor3f(0.55f, 0.28f, 0.12f);
    for (float y = 2.0f; y < panelHeight - 1.0f; y += 1.2f) {
        // panel 1
        glPushMatrix();
        glTranslatef(xRightPanel + 0.05f, y, cz - (singlePanelWidth * 0.75f));
        drawBlock(0.2f, 0.2f, singlePanelWidth);
        glPopMatrix();
        // panel 2
        glPushMatrix();
        glTranslatef(xRightPanel + 0.05f, y, cz + (singlePanelWidth * 0.75f));
        drawBlock(0.2f, 0.2f, singlePanelWidth);
        glPopMatrix();
        // ===================================
        // 2 GARIS HORIZONTAL TEBAL - PANEL KANAN
        // ===================================
        float bandDepth = (singlePanelWidth * 2.0f) + 0.8f;  // panjang ke Z (2 panel)
        float bandThick = 0.4f;                              // tebal ke arah X
        float bandHeightY1 = 11.5f;                            // tinggi garis pertama
        float bandHeightY2 = 20.5f;                            // tinggi garis kedua
        // warna garis
        glColor3f(0.60f, 0.32f, 0.15f);
        // GARIS 1
        glPushMatrix();
        glTranslatef(xRightPanel + 0.02f, bandHeightY1, cz);
        drawBlock(bandThick, 0.7f, bandDepth);
        glPopMatrix();
        // GARIS 2
        glPushMatrix();
        glTranslatef(xRightPanel + 0.02f, bandHeightY2, cz);
        drawBlock(bandThick, 0.7f, bandDepth);
        glPopMatrix();
    }
    // ===================================
   //   PANEL SAMPING KIRI A5 (DUA PANEL)
   // ===================================
    float xLeftPanel = cx - halfW + 0.05f;
    // PANEL 1 (kiri luar)
    glColor3f(0.70f, 0.35f, 0.15f);
    glPushMatrix();
    glTranslatef(xLeftPanel, panelHeight * 0.5f, cz - (singlePanelWidth * 0.75f));
    drawBlock(panelThickness, panelHeight, singlePanelWidth);
    glPopMatrix();
    // PANEL 2 (kiri dalam)
    glColor3f(0.70f, 0.35f, 0.15f);
    glPushMatrix();
    glTranslatef(xLeftPanel, panelHeight * 0.5f, cz + (singlePanelWidth * 0.75f));
    drawBlock(panelThickness, panelHeight, singlePanelWidth);
    glPopMatrix();
    // STRIP HORIZONTAL PANEL KIRI
    glColor3f(0.55f, 0.28f, 0.12f);
    for (float y = 2.0f; y < panelHeight - 1.0f; y += 1.2f) {
        // panel 1
        glPushMatrix();
        glTranslatef(xLeftPanel - 0.05f, y, cz - (singlePanelWidth * 0.75f));
        drawBlock(0.2f, 0.2f, singlePanelWidth);
        glPopMatrix();
        // panel 2
        glPushMatrix();
        glTranslatef(xLeftPanel - 0.05f, y, cz + (singlePanelWidth * 0.75f));
        drawBlock(0.2f, 0.2f, singlePanelWidth);
        glPopMatrix();
        // ===================================
        // 2 GARIS HORIZONTAL TEBAL - PANEL KIRI
        // ===================================
        // deklarasi variabel (samakan persis dengan sisi kanan)
        float bandDepthL = (singlePanelWidth * 2.0f) + 0.8f;  // panjang ke Z (2 panel)
        float bandThickL = 0.4f;                              // tebal ke arah X
        float bandHeightY1L = 11.5f;                          // tinggi garis pertama
        float bandHeightY2L = 20.5f;                          // tinggi garis kedua
        // warna garis
        glColor3f(0.60f, 0.32f, 0.15f);
        // GARIS 1 (bawah)
        glPushMatrix();
        glTranslatef(xLeftPanel - 0.02f, bandHeightY1L, cz);
        drawBlock(bandThickL, 0.7f, bandDepthL);
        glPopMatrix();
        // GARIS 2 (atas)
        glPushMatrix();
        glTranslatef(xLeftPanel - 0.02f, bandHeightY2L, cz);
        drawBlock(bandThickL, 0.7f, bandDepthL);
        glPopMatrix();
    }
    // ============================
    //   TULISAN "TEKNIK ELEKTRO 
    // ============================
    glColor3f(0.95f, 0.95f, 0.95f); 
    glPushMatrix();
    glTranslatef(cx + 30.0f, 10, frontZ - 6.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.015f, 0.015f, 0.015f);
    glLineWidth(4.0f);
    for (const char* c = "TEKNIK ELEKTRO"; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glLineWidth(1.0f);
    glPopMatrix();
    // ============================
    // 2. KANOPI (dipindah ke sisi –Z)
    // ============================
    glColor3f(0.65f, 0.55f, 0.60f);
    glPushMatrix();
    glTranslatef(cx, 11.0f, frontZ - 2.0f);
    glRotatef(180, 0, 1, 0);  // ★  menghadap –Y / –Z
    drawBlock(W + 10.0f, 2.2f, 7.0f);
    glPopMatrix();
    // ============================
    // 3. BALKON
    // ============================
    float balconyY[2] = { 15.5f, 24.5f };
    for (int i = 0; i < 2; i++) {
        glColor3f(0.95f, 0.90f, 0.83f);
        glPushMatrix();
        glTranslatef(cx, balconyY[i], frontZ - 0.5f);
        glRotatef(180, 0, 1, 0);
        drawBlock(W * 0.92f, 1.30f, 1.30f);
        glPopMatrix();
    }
    // ============================
    // 4. TIANG TIPIS
    // ============================
    glColor3f(0.87f, 0.58f, 0.20f);
    int columns = 12;
    for (int i = 0; i < columns; i++) {
        float px = cx - halfW + 6 + i * ((W - 12) / (columns - 1));
        float baseYs[3] = { 6.0f, 15.0f, 24.0f };
        for (int l = 0; l < 3; l++) {
            glPushMatrix();
            glTranslatef(px, baseYs[l], frontZ - 0.5f);
            glRotatef(180, 0, 1, 0);
            drawBlock(1.2f, 9.0f, 1.2f);
            glPopMatrix();
        }
    }
    // ============================
    // 5. JENDELA BESAR
    // ============================
    glColor3fv(iceBlueColor);
    float jendelaY[3] = { 8.5f, 17.5f, 26.5f };
    for (int l = 0; l < 3; l++) {
        glPushMatrix();
        glTranslatef(cx, jendelaY[l], frontZ - 0.3f);
        glRotatef(180, 0, 1, 0);
        drawBlock(W * 0.94f, 5.0f, 0.3f);
        glPopMatrix();
    }
    // frame coklat
    glColor3f(0.45f, 0.30f, 0.25f);
    for (int l = 0; l < 3; l++) {
        glPushMatrix();
        glTranslatef(cx, jendelaY[l] + 3.0f, frontZ - 0.4f);
        glRotatef(180, 0, 1, 0);
        drawBlock(W * 0.95f, 0.8f, 0.4f);
        glPopMatrix();
    }
    // ============================
    // 6. PINTU UTAMA + PAPAN
    // ============================
    glColor3f(0.32f, 0.15f, 0.10f);
    glPushMatrix();
    glTranslatef(cx, 5.5f, frontZ - 0.4f);
    glRotatef(180, 0, 1, 0);
    drawBlock(9.0f, 11.0f, 0.4f);
    glPopMatrix();
    // papan kiri
    glColor3f(0.25f, 0.30f, 0.45f);
    glPushMatrix();
    glTranslatef(cx - 25.0f, 6.0f, frontZ - 0.4f);
    glRotatef(180, 0, 1, 0);
    drawBlock(20.0f, 8.0f, 0.4f);
    glPopMatrix();
    // papan kanan
    glPushMatrix();
    glTranslatef(cx + 25.0f, 6.0f, frontZ - 0.4f);
    glRotatef(180, 0, 1, 0);
    drawBlock(20.0f, 8.0f, 0.4f);
    glPopMatrix();
    // ============================
 //  TULISAN "A5" 
 // ============================
    glColor3f(0.35f, 0.25f, 0.20f); 
    glPushMatrix();
    glTranslatef(cx+1.5, 12.5f, frontZ - 1.0f);  // posisi tepat di atas pintu
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);     // hadap ke depan
    glScalef(0.02f, 0.02f, 0.02f);        
    glLineWidth(3.0f);
    for (const char* c = "A5"; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glLineWidth(1.0f);
    glPopMatrix();
    // =====================================================
//  TAMPAK BELAKANG GEDUNG A5 
// =====================================================
    // ===== BALKON BELAKANG =====
    for (int i = 0; i < 2; i++) {
        glColor3f(0.95f, 0.90f, 0.83f);
        glPushMatrix();
        glTranslatef(cx, balconyY[i], backZ + 0.5f);
        drawBlock(W * 0.92f, 1.30f, 1.30f);
        glPopMatrix();
    }
    // ===== TIANG VERTIKAL BELAKANG =====
    glColor3f(0.87f, 0.58f, 0.20f);
    for (int i = 0; i < columns; i++) {
        float px = cx - halfW + 6 + i * ((W - 12) / (columns - 1));
        float baseYs[3] = { 6.0f, 15.0f, 24.0f };
        for (int l = 0; l < 3; l++) {
            glPushMatrix();
            glTranslatef(px, baseYs[l], backZ + 0.5f);
            drawBlock(1.2f, 9.0f, 1.2f);
            glPopMatrix();
        }
    }
    // ===== JENDELA BELAKANG =====
    glColor3fv(iceBlueColor);
    for (int l = 0; l < 3; l++) {
        glPushMatrix();
        glTranslatef(cx, jendelaY[l], backZ + 0.3f);
        drawBlock(W * 0.94f, 5.0f, 0.3f);
        glPopMatrix();
    }
    // frame jendela coklat
    glColor3f(0.45f, 0.30f, 0.25f);
    for (int l = 0; l < 3; l++) {
        glPushMatrix();
        glTranslatef(cx, jendelaY[l] + 3.0f, backZ + 0.4f);
        drawBlock(W * 0.95f, 0.8f, 0.4f);
        glPopMatrix();
    }
    // papan kiri belakang
    glColor3f(0.25f, 0.30f, 0.45f);
    glPushMatrix();
    glTranslatef(cx - 25.0f, 6.0f, backZ + 0.4f);
    drawBlock(20.0f, 8.0f, 0.4f);
    glPopMatrix();
    // papan kanan belakang
    glPushMatrix();
    glTranslatef(cx + 25.0f, 6.0f, backZ + 0.4f);
    drawBlock(20.0f, 8.0f, 0.4f);
    glPopMatrix();
    // ============================
// 7. ATAP LIMAS GEDUNG A5
// ============================
    glPushMatrix();
    glTranslatef(cx, 30, cz);
    drawAtap(70, 30, 6);
    glPopMatrix();
}

void drawA6() {
    float cx = 180.0f, cz = -190.0f;
    float W = 70.0f, H = 30.0f, D = 30.0f;
    float halfW = W * 0.5f;
    float halfD = D * 0.5f;
    // depan gedung menghadap –Y (berarti sisi Z yang lebih kecil)
    float frontZ = cz - halfD;
    float backZ = cz + halfD;
    // ============================
    // 1. BADAN GEDUNG
    // ============================
    glColor3fv(creamColor);
    glPushMatrix();
    glTranslatef(cx, H * 0.5f, cz);
    drawBlock(W, H, D);
    glPopMatrix();
    // ===================================
    //   PINTU POJOK BELAKANG–KANAN
    // ===================================
    {
        float doorW = 8.0f;
        float doorH = 12.0f;
        float doorX = cx + halfW - 0.2f;     // hampir ke dinding kanan
        float doorZ = cz + halfD - 0.2f;     // hampir ke dinding belakang
        float doorY = 6.0f;                  // tinggi pintu
        glColor3f(0.32f, 0.15f, 0.10f);      // coklat pintu
        glPushMatrix();
        glTranslatef(doorX, doorY, doorZ);
        // rotasi 45 derajat supaya sejajar dinding miring pojok
        glRotatef(-135, 0, 1, 0);
        //  -135 = menghadap diagonal belakang-kanan
        drawBlock(doorW, doorH, 0.4f);
        glPopMatrix();
    }
    // ============================
    // 2. KANOPI (dipindah ke sisi –Z)
    // ============================
    glColor3f(0.55f, 0.38f, 0.22f);
    glPushMatrix();
    glTranslatef(cx, 11.0f, frontZ - 1.0f);
    glRotatef(180, 0, 1, 0);  // ★ menghadap –Y / –Z
    drawBlock(W + 10.0f, 2.2f, 7.0f);
    glPopMatrix();
    // ============================
    // 3. BALKON
    // ============================
    float balconyY[2] = { 15.5f, 24.5f };
    for (int i = 0; i < 2; i++) {
        glColor3f(0.55f, 0.38f, 0.22f);
        glPushMatrix();
        glTranslatef(cx, balconyY[i], frontZ - 0.5f);
        glRotatef(180, 0, 1, 0);
        drawBlock(W * 0.92f, 1.30f, 1.30f);
        glPopMatrix();
    }
    // ============================
    // 4. TIANG TIPIS
    // ============================
    glColor3f(0.48f, 0.30f, 0.18f);

    int columns = 12;
    for (int i = 0; i < columns; i++) {

        float px = cx - halfW + 6 + i * ((W - 12) / (columns - 1));

        float baseYs[3] = { 6.0f, 15.0f, 24.0f };

        for (int l = 0; l < 3; l++) {
            glPushMatrix();
            glTranslatef(px, baseYs[l], frontZ - 0.5f);
            glRotatef(180, 0, 1, 0);
            drawBlock(1.2f, 9.0f, 1.2f);
            glPopMatrix();
        }
    }
    // ============================
    // 5. JENDELA BESAR
    // ============================
    glColor3fv(iceBlueColor);
    float jendelaY[3] = { 8.5f, 17.5f, 26.5f };
    for (int l = 0; l < 3; l++) {
        glPushMatrix();
        glTranslatef(cx, jendelaY[l], frontZ - 0.3f);
        glRotatef(180, 0, 1, 0);
        drawBlock(W * 0.94f, 5.0f, 0.3f);
        glPopMatrix();
    }
    // frame coklat
    glColor3f(0.45f, 0.30f, 0.25f);
    for (int l = 0; l < 3; l++) {
        glPushMatrix();
        glTranslatef(cx, jendelaY[l] + 3.0f, frontZ - 0.4f);
        glRotatef(180, 0, 1, 0);
        drawBlock(W * 0.95f, 0.8f, 0.4f);
        glPopMatrix();
    }
    // ============================
    // 6. PINTU UTAMA + PAPAN
    // ============================
    glColor3f(0.32f, 0.15f, 0.10f);
    glPushMatrix();
    glTranslatef(cx, 5.5f, frontZ - 0.4f);
    glRotatef(180, 0, 1, 0);
    drawBlock(9.0f, 11.0f, 0.4f);
    glPopMatrix();
    // papan kiri
    glColor3f(0.87f, 0.58f, 0.20f);
    glPushMatrix();
    glTranslatef(cx - 25.0f, 6.0f, frontZ - 0.4f);
    glRotatef(180, 0, 1, 0);
    drawBlock(20.0f, 8.0f, 0.4f);
    glPopMatrix();
    // papan kanan
    glPushMatrix();
    glTranslatef(cx + 25.0f, 6.0f, frontZ - 0.4f);
    glRotatef(180, 0, 1, 0);
    drawBlock(20.0f, 8.0f, 0.4f);
    glPopMatrix();
    // ============================
    // KANOPI PUTIH 
    // ============================
    glColor3f(0.95f, 0.95f, 0.95f);  // putih
    glPushMatrix();
    glTranslatef(cx, 10.0f, cz);
    drawBlock(12.0f, 2.0f, 44);           
    glPopMatrix();
    // ============================
   //   TULISAN "TEKNIK MESIN"
   // ============================
    glColor3f(0.80f, 0.80f, 0.80f); // abu-abu metal
    glPushMatrix();
    glTranslatef(cx-4.5, 9.5f, backZ + 7.2f);
    glScalef(0.010f, 0.010f, 0.010f);
    glLineWidth(3.0f);
    for (const char* c = "TEKNIK MESIN"; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glLineWidth(1.0f);
    glPopMatrix();
    // =====================================================
    //  TAMPAK BELAKANG GEDUNG A6 
    // =====================================================
    // ===== BALKON BELAKANG =====
    for (int i = 0; i < 2; i++) {
        glColor3f(0.95f, 0.90f, 0.83f);
        glPushMatrix();
        glTranslatef(cx, balconyY[i], backZ + 0.5f);
        drawBlock(W * 0.92f, 1.30f, 1.30f);
        glPopMatrix();
    }
    // ===== TIANG VERTIKAL BELAKANG =====
    glColor3f(0.48f, 0.30f, 0.18f);
    for (int i = 0; i < columns; i++) {
        float px = cx - halfW + 6 + i * ((W - 12) / (columns - 1));
        float baseYs[3] = { 6.0f, 15.0f, 24.0f };
        for (int l = 0; l < 3; l++) {
            glPushMatrix();
            glTranslatef(px, baseYs[l], backZ + 0.5f);
            drawBlock(1.2f, 9.0f, 1.2f);
            glPopMatrix();
        }
    }
    // ===== JENDELA BELAKANG =====
    glColor3fv(iceBlueColor);
    for (int l = 0; l < 3; l++) {
        glPushMatrix();
        glTranslatef(cx, jendelaY[l], backZ + 0.3f);
        drawBlock(W * 0.94f, 5.0f, 0.3f);
        glPopMatrix();
    }
    // frame jendela coklat
    glColor3f(0.45f, 0.30f, 0.25f);
    for (int l = 0; l < 3; l++) {
        glPushMatrix();
        glTranslatef(cx, jendelaY[l] + 3.0f, backZ + 0.4f);
        drawBlock(W * 0.95f, 0.8f, 0.4f);
        glPopMatrix();
    }
    // papan kiri belakang
    glColor3f(0.55f, 0.28f, 0.12f);
    glPushMatrix();
    glTranslatef(cx - 25.0f, 6.0f, backZ + 0.4f);
    drawBlock(20.0f, 8.0f, 0.4f);
    glPopMatrix();
    // papan kanan belakang
    glPushMatrix();
    glTranslatef(cx + 25.0f, 6.0f, backZ + 0.4f);
    drawBlock(20.0f, 8.0f, 0.4f);
    glPopMatrix();
    // ============================
   // KANOPI BELAKANG
   // ============================
    glColor3f(0.52f, 0.32f, 0.18f); // warna kanopi
    glPushMatrix();
    glTranslatef(cx, 11.0f, backZ + 2.0f);   // geser ke belakang
    // tidak perlu rotate 180 arah normalnya sudah benar
    drawBlock(W + 10.0f, 2.2f, 7.0f);
    glPopMatrix();
    // ============================
// PINTU BELAKANG A6
// ============================
    glColor3f(0.32f, 0.15f, 0.10f); // warna pintu
    glPushMatrix();
    glTranslatef(cx, 5.5f, backZ + 0.4f);
    drawBlock(9.0f, 11.0f, 0.4f);
    glPopMatrix();
    // PAPAN KIRI BELAKANG
    glColor3f(0.70f, 0.35f, 0.15f);
    glPushMatrix();
    glTranslatef(cx - 25.0f, 6.0f, backZ + 0.4f);
    drawBlock(20.0f, 8.0f, 0.4f);
    glPopMatrix();
    // PAPAN KANAN BELAKANG
    glPushMatrix();
    glTranslatef(cx + 25.0f, 6.0f, backZ + 0.4f);
    drawBlock(20.0f, 8.0f, 0.4f);
    glPopMatrix();
    // ===================================
//   PINTU SAMPING KIRI GEDUNG A6
// ===================================
    {
        float doorW = 9.0f;
        float doorH = 11.0f;
        float doorX = cx - halfW - 0.3f;   // tempel ke dinding kiri
        float doorZ = cz;                  // posisi tengah sisi kiri
        float doorY = 5.5f;                // tinggi pintu
        glColor3f(0.32f, 0.15f, 0.10f); // warna coklat pintu
        glPushMatrix();
        glTranslatef(doorX, doorY, doorZ);
        // pintu harus menghadap keluar (arah kiri), jadi rotasi 90°
        glRotatef(90, 0, 1, 0);
        drawBlock(doorW, doorH, 0.4f);
        glPopMatrix();
    }
    // ===================================
//   PINTU SAMPING KANAN
// ===================================
    {
        float doorX = cx + halfW + 0.3f; // posisi sisi kanan
        float doorZ = cz;
        float doorY = 5.5f;              // sama tinggi dengan pintu kiri
        glColor3f(0.32f, 0.15f, 0.10f);  // warna pintu (sama)
        glPushMatrix();
        glTranslatef(doorX, doorY, doorZ);
        glRotatef(90, 0, 1, 0);  // putar supaya menghadap keluar kanan
        drawBlock(9.0f, 11.0f, 0.4f);    // ukuran pintu
        glPopMatrix();
    }
    // ===================================
//   KANOPI PINTU SAMPING KIRI
// ===================================
    {
        float doorX = cx - halfW - 0.3f; // posisi pintu kiri
        float doorZ = cz;                // tengah z
        float canopyY = 11.0f;           
        glColor3f(0.65f, 0.50f, 0.35f);   // warna coklat lebih muda
        glPushMatrix();
        glTranslatef(doorX + 1.8f, canopyY, doorZ);
        glRotatef(90, 0, 1, 0); // hadap keluar kiri
        drawBlock(10.0f, 1.5f, 5.0f);   // panjang, tebal, kedalaman
        glPopMatrix();
    }
    // ===================================
//   KANOPI PINTU SAMPING KANAN
// ===================================
    {
        float doorX = cx + halfW + 0.3f; // sisi kanan
        float doorZ = cz;
        float canopyY = 11.0f;
        glColor3f(0.65f, 0.50f, 0.35f);
        glPushMatrix();
        glTranslatef(doorX - 1.8f, canopyY, doorZ);
        //              ^ minus karena keluar ke arah lain
        glRotatef(-90, 0, 1, 0); // hadap keluar kanan
        drawBlock(10.0f, 1.5f, 5.0f);
        glPopMatrix();
    }
    // ============================
    //  TULISAN "A6" (di atas kanopi kiri – sudah dibalik & dibesarkan)
    // ============================
    glColor3f(0.35f, 0.25f, 0.20f);  // coklat tua
    glPushMatrix();
    glTranslatef(cx - halfW, 13.0f, cz-1);
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.015f, 0.015f, 0.015f);
    glLineWidth(3.0f);
    for (const char* c = "A6"; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glLineWidth(1.0f);
    glPopMatrix();
    // ============================
// 7. ATAP LIMAS GEDUNG A5
// ============================
    glPushMatrix();
    glTranslatef(cx, 30, cz);
    drawAtap(70, 30, 6);
    glPopMatrix();
}

void drawA7() {
    float cX = 180.0f, cZ = -125.0f, sX = 56.0f, sY = 16.0f, sZ = 26.0f;
    float fWZ = cZ - (sZ / 2.0f), rWX = cX + (sX / 2.0f), lWX = cX - (sX / 2.0f);
    // BADAN
    glColor3fv(creamColor); glPushMatrix(); glTranslatef(cX, sY/2, cZ); drawBlock(sX, sY, sZ); glPopMatrix();
    // PINTU (Z NEGATIF)
    glColor3fv(doorGlassColor); glPushMatrix(); glTranslatef(cX, 2.5f, fWZ - 0.1f); drawBlock(5, 5, 0.2f); glPopMatrix();
    glColor3fv(sageGreen); float oZ = fWZ - 0.2f;
    glPushMatrix(); glTranslatef(cX - 2.5, 2.5f, oZ); drawBlock(1, 5, 0.5f); glPopMatrix();
    glPushMatrix(); glTranslatef(cX + 2.5, 2.5f, oZ); drawBlock(1, 5, 0.5f); glPopMatrix();
    // JENDELA (9 Buah per lantai)
    int nWin = 7;
    float wW = 3.0f, wH = 2.5f, gWin = 2.3f; 
    // Rumus Center Jendela: Total Lebar = (7*3) + (6*4) = 21 + 24 = 45.0
    float totWinW = (nWin * wW) + ((nWin - 1) * gWin);
    float startWinX = cX - (totWinW / 2.0f) + (wW / 2.0f);
    for (int f = 0; f < 2; f++) {
        float wY = 8.0f + (f * 6.0f);
        glColor3fv(windowGlassColor);
        for (int i = 0; i < nWin; i++) {
            float curX = startWinX + (i * (wW + gWin));
            glPushMatrix(); glTranslatef(curX, wY, fWZ - 0.1f); drawBlock(wW, wH, 0.2f); glPopMatrix();
        }
    }
    // --- 2. GAMBAR PILAR (10 BUAH - CENTERED TERPISAH) ---
    int nPil = 10;
    float pW = 0.5f, pD = 0.3f, pH = sY;
    float totPilW = 48.0f;
    float gPil = totPilW / (nPil - 1); // Jarak antar pilar
    float startPilX = cX - (totPilW / 2.0f);
    glColor3fv(brownColor);
    for (int p = 0; p < nPil; p++) {
        float curPX = startPilX + (p * gPil);
        glPushMatrix(); glTranslatef(curPX, sY/2, fWZ - 0.05f); drawBlock(pW, pH, pD); glPopMatrix();
    }
    // PRISMA DEPAN
    glColor3fv(roofTileColor);
    glPushMatrix(); glTranslatef(cX, 5.0f, fWZ - 1.5f); glRotatef(90, 0, 1, 0); drawRightTriPrism(3.0f, 3.0f, 50.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(cX, 11.0f, fWZ - 1.5f); glRotatef(90, 0, 1, 0); drawRightTriPrism(3.0f, 3.0f, 50.0f); glPopMatrix();
    // PILAR BAWAH PRISMA
    glColor3fv(moccaColor);
    for (float dx = cX-8; dx < cX+9; dx += 5.1) {
        glPushMatrix(); glTranslatef(dx, 1.8, fWZ - 6.7); drawBlock(0.5, 3.6, 0.3); glPopMatrix();
        }
    // KANOPI
    glColor3fv(quartzColor);
    glPushMatrix(); glTranslatef(cX, 5, fWZ - 3.5); drawBlock(17, 3, 7); glPopMatrix();
    // ALAS DEPAN
    glPushMatrix(); glTranslatef(cX, 0.1f, fWZ - 1.5); drawBlock(50, 0.2, 3.0f); glPopMatrix();
    // TANGGA KANAN & KIRI
    glPushMatrix(); glTranslatef(cX, 5.2, fWZ + 13.5); drawBlock(66, 0.2, 3.0f); glPopMatrix();
    float stW = 5.0f, stH = 0.5f, stD = 1.0f; int nS = 11;
    float rSX = rWX + (stW / 2.0f), lSX = lWX - (stW / 2.0f);
    for (int s = 0; s < nS; s++) {
        float sY = 0.5f + (s * stH), sZ = fWZ + 2.0f + (s * stD);
        glPushMatrix(); glTranslatef(rSX, sY-0.5, sZ); drawBlock(stW, stH, stD); glPopMatrix();
        glPushMatrix(); glTranslatef(lSX, sY-0.5, sZ); drawBlock(stW, stH, stD); glPopMatrix();
    }
    glColor3fv(moccaColor);
    glPushMatrix(); glTranslatef(rSX+2.5, 4, fWZ + 7.5f); glRotatef(90, 0, 1, 0); drawRightTriPrism(15.0f, 8, 1); glPopMatrix();
    glPushMatrix(); glTranslatef(lSX-2.5, 4, fWZ + 7.5f); glRotatef(90, 0, 1, 0); drawRightTriPrism(15.0f, 8, 1); glPopMatrix();
    glPushMatrix(); glTranslatef(cX, 6.5, fWZ + 14.8); drawBlock(66, 3, 0.5); glPopMatrix();
	// PINTU KANAN & KIRI
	glColor3fv(doorGlassColor);
    glPushMatrix(); glTranslatef(cX, 7, cZ); drawBlock(56.5, 4, 2); glPopMatrix();
    glColor3fv(brownColor);
    glPushMatrix(); glTranslatef(cX, sY/2, cZ+1.5); drawBlock(57, sY, 0.5); glPopMatrix();
    glPushMatrix(); glTranslatef(cX, sY/2, cZ - 1.5); drawBlock(57, sY, 0.5); glPopMatrix();
	// PRISMA KANAN & KIRI
    glColor3fv(roofTileColor);
    glPushMatrix(); glTranslatef(rSX-1.5, 11.0f, cZ); drawRightTriPrism(3.0f, 3.0f, 20.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(lSX + 1.5, 11.0f, cZ); glRotatef(180, 0, 1, 0); drawRightTriPrism(3.0f, 3.0f, 20.0f); glPopMatrix();
	// PILAR KANAN & KIRI 
    glColor3fv(brownColor);
    glPushMatrix(); glTranslatef(cX, sY / 2, cZ + 12.6); drawBlock(57, sY, 0.5); glPopMatrix();
    glPushMatrix(); glTranslatef(cX, sY / 2, cZ - 12.6); drawBlock(57, sY, 0.5); glPopMatrix();
    // ATAP LIMAS
    glColor3fv(roofTileColor);
    glPushMatrix();
    glTranslatef(cX, 16, cZ);
    drawAtap(sX + 2.0f, sZ + 2.0f, 6);
    glPopMatrix();
    // TULISAN
    glColor3fv(greyColor); 
    glPushMatrix();
    glTranslatef(cX-22, 7.0f, fWZ); glRotatef(180.0f, 0.0f, 1.0f, 0.0f); glScalef(0.02f, 0.02f, 0.02f);  glLineWidth(4.0f);
    glTranslatef(-100.0f, 0.0f, 0.0f);
    for (const char* c = "A7"; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glLineWidth(1.0f); glPopMatrix();
    // ==== BAGIAN BAWAH KANAN & KIRI ===
    glColor3fv(creamColor); 
    glPushMatrix(); glTranslatef(cX+25, 2.5, cZ+25); drawBlock(6, 5, 24); glPopMatrix();
    glPushMatrix(); glTranslatef(cX-25, 2.5, cZ + 25); drawBlock(6, 5, 24); glPopMatrix();
	// BAGIAN ATAS KANAN & KIRI
    glPushMatrix(); glTranslatef(cX + 25, 10.5, cZ + 43); drawBlock(6, 11, 60); glPopMatrix();
    glPushMatrix(); glTranslatef(cX - 25, 10.5, cZ + 43); drawBlock(6, 11, 60); glPopMatrix();
    // BAGIAN TENGAH A7 & A8
    float AZ = -82.5;
    glColor3fv(brownColor);
    glPushMatrix(); glTranslatef(cX + 25, 9, AZ + 5); drawBlock(8, 18, 1); glPopMatrix();
    glPushMatrix(); glTranslatef(cX - 25, 9, AZ + 5); drawBlock(8, 18, 1); glPopMatrix();
    glPushMatrix(); glTranslatef(cX + 25, 9, AZ - 5); drawBlock(8, 18, 1); glPopMatrix();
    glPushMatrix(); glTranslatef(cX - 25, 9, AZ - 5); drawBlock(8, 18, 1); glPopMatrix();
}

void drawA8() {
    float cX = 180.0f, cZ = -40.0f;
    float baseW = 56.0f; // Lebar X
    float baseH = 18.0f; // Tinggi Y
    float baseD = 26.0f; // Tebal Z (Kedalaman)
    float colW = 1.0f;   // Lebar Pilar
    float floorH = 4.0f; // Tinggi per lantai
    float slabT = 0.5f;  // Tebal Lantai
    // ===========================================================
    // MULAI GAMBAR (HANYA 1 PUSH UTAMA)
    // ===========================================================
    glPushMatrix();
    // --- A. BADAN UTAMA ---
    glColor3fv(creamColor);
    glPushMatrix();
    glTranslatef(cX, baseH / 2.0f, cZ + (baseD / 2.0f) - (colW / 2.0f));
    drawBlock(baseW, baseH, colW);
    glPopMatrix();
    // 2. Dinding Depan (Z Negatif)
    // Posisi: Z=cZ - 10.5
    glPushMatrix();
    glTranslatef(cX, baseH / 2.0f, cZ - (baseD / 2.0f) + (colW / 2.0f));
    drawBlock(baseW, baseH, colW);
    glPopMatrix();
    // 3. Dinding Kiri (X Negatif)
    // Posisi: X=cX - (56/2) + 0.5 = cX - 27.5
    glPushMatrix();
    glTranslatef(cX - (baseW / 2.0f) + (colW / 2.0f), baseH / 2.0f, cZ);
    drawBlock(colW, baseH, baseD);
    glPopMatrix();
    // 4. Dinding Kanan (X Positif)
    glPushMatrix();
    glTranslatef(cX + (baseW / 2.0f) - (colW / 2.0f), baseH / 2.0f, cZ);
    drawBlock(colW, baseH, baseD);
    glPopMatrix();
    // --- B. LANTAI & ATAP DATAR (SLAB) ---
    // Loop 5 lapis (Lantai 0, 1, 2, 3, Atap)
    glColor3fv(brownColor);
    for (int i = 0; i <= 4; i++) {
        float yPos = i * (floorH + slabT);
        glPushMatrix();
        glTranslatef(cX, yPos, cZ);
        drawBlock(baseW + 5.0f, slabT, baseD + 5.0f);
        glPopMatrix();
    }

    // --- C. PILAR VERTIKAL & JENDELA (LOOPING) ---
    float startX = cX - (baseW / 2.0f) + 4.0f;
    float endX = cX + (baseW / 2.0f) - 4.0f;
    float gapX = 8.0f; // Jarak antar pilar
    float frontZ = cZ - (baseD / 2.0f) - 0.2f;
    float backZ = cZ + (baseD / 2.0f) + 0.2f;
    for (float lx = startX; lx <= endX; lx += gapX) {
        if (lx > cX - 5.0f && lx < cX + 5.0f) continue;
        glColor3fv(brownColor);
        // Depan
        glPushMatrix(); glTranslatef(lx, baseH / 2.0f, frontZ); drawBlock(1.0f, baseH, 1.0f); glPopMatrix();
        // Belakang
        glPushMatrix(); glTranslatef(lx, baseH / 2.0f, backZ); drawBlock(1.0f, baseH, 1.0f); glPopMatrix();
        // JENDELA KACA (Di antara pilar)
        glColor3fv(doorGlassColor);
        for (int floor = 0; floor < 3; floor++) {
            float winY = (floor * (floorH + slabT)) + 7; 
            float winX = lx + (gapX / 2.0f);
            if (winX > endX) continue; 
            // Depan
            glPushMatrix(); glTranslatef(winX, winY, frontZ); drawBlock(3.0f, 2.0f, 0.2f); glPopMatrix();
            // Belakang
            glPushMatrix(); glTranslatef(winX, winY, backZ); drawBlock(3.0f, 2.0f, 0.2f); glPopMatrix();
        }
    }
    // --- D. MENARA TENGAH (LIFT/TANGGA) ---
    float towerW = 15.0f;
    float towerH = baseH + 4.0f; 
    glColor3fv(quartzColor);
    glPushMatrix();
    glTranslatef(cX, towerH / 2.0f, cZ); // Pas tengah gedung
    drawBlock(towerW, towerH, baseD + 2.0f); // Tembus depan belakang
    glPopMatrix();
    // Kaca Menara Vertikal
    glColor3fv(doorGlassColor);
    glPushMatrix();
    glTranslatef(cX, towerH / 2.0f, cZ - (baseD / 2.0f) - 1.1f); // Nempel depan menara
    drawBlock(2.0f, towerH - 2.0f, 0.2f);
    glPopMatrix();
    // --- E. KANOPI ---
	// Jendela Kaca Atas Kanopi
    glColor3fv(seaBlueColor);
    glPushMatrix(); glTranslatef(cX, 12, cZ); drawBlock(4.0f, 10, 32.5f); glPopMatrix();
	// Kanopi Utama
    glColor3fv(moccaColor);
    glPushMatrix(); glTranslatef(cX, 5, cZ); drawBlock(12.0f, 1, 37.0f); glPopMatrix();
    // Tiang Kanopi
    glColor3fv(brownColor);
    glPushMatrix(); glTranslatef(cX - 5.0f, 2.5f, cZ - 18); drawBlock(1, 5.0f, 1); glPopMatrix();
    glPushMatrix(); glTranslatef(cX + 5.0f, 2.5f, cZ - 18); drawBlock(1, 5.0f, 1); glPopMatrix();
    glPushMatrix(); glTranslatef(cX - 5.0f, 2.5f, cZ + 18); drawBlock(1, 5.0f, 1); glPopMatrix();
    glPushMatrix(); glTranslatef(cX + 5.0f, 2.5f, cZ + 18); drawBlock(1, 5.0f, 1); glPopMatrix();
    // Bangunan Tambahan Warna Merah
    glColor3fv(maroonColor);
    glPushMatrix(); glTranslatef(cX, 13, cZ); drawBlock(7.0f, 16, 32.0f); glPopMatrix();
    // --- F. TULISAN ---
    glColor3fv(greyColor);
    glPushMatrix();
    glTranslatef(cX - 13, 2.0f, cZ+13.1);
    glScalef(0.015f, 0.015f, 0.015f);
    glLineWidth(4.0f);
    for (const char* c = "A8"; *c != '\0'; c++) glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    glLineWidth(1.0f);
    glPopMatrix();
    glColor3fv(iceWhiteColor);
    glPushMatrix();
    glTranslatef(cX - 1.9, 19.0f, cZ + 16.1);
    glScalef(0.004, 0.004f, 0.004f);
    glLineWidth(4.0f);
    for (const char* c = "LABORATORIUM"; *c != '\0'; c++) glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    glLineWidth(1.0f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(cX - 2.2, 18.0f, cZ + 16.1);
    glScalef(0.004, 0.004f, 0.004f);
    glLineWidth(4.0f);
    for (const char* c = "TEKNIK TERPADU"; *c != '\0'; c++) glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    glLineWidth(1.0f);
    glPopMatrix();
    // --- PINTU ---
    // 1. DAUN PINTU KACA (Lebar 3, Tinggi 2.5)
    glColor3fv(doorGlassColor);
    glPushMatrix(); glTranslatef(cX, 1.75, cZ+14.1); drawBlock(3.0f, 3.5, 0.2f); glPopMatrix();
    // 2. ORNAMEN PINTU (Frame Sage Green)
    glColor3fv(sageGreen);
    // Tiang Kiri
    glPushMatrix(); glTranslatef(cX - 1.7f, 1.75, cZ + 14.2); drawBlock(0.4f, 3.5, 0.4f); glPopMatrix();
    // Tiang Kanan
    glPushMatrix(); glTranslatef(cX + 1.7f, 1.75, cZ + 14.2); drawBlock(0.4f, 3.5f, 0.4f); glPopMatrix();
    // Balok Atas (Topi Pintu)
    glPushMatrix(); glTranslatef(cX, 3.7f, cZ + 14.1); drawBlock(3.8f, 0.4f, 0.4f);  glPopMatrix();
	// BAGIAN BAWAH KANAN & KIRI
	glColor3fv(creamColor);
	glPushMatrix(); glTranslatef(cX + 25, 2.5, cZ - 25); drawBlock(6, 5, 24); glPopMatrix();
	glPushMatrix(); glTranslatef(cX - 25, 2.5, cZ - 25); drawBlock(6, 5, 24); glPopMatrix();
	// BAGIAN ATAS KANAN & KIRI
	// Jendela Kaca
    glColor3fv(doorGlassColor);
    float sWinW = 3.0f; // Lebar Jendela (Z)
    float sWinH = 2.5f; // Tinggi Jendela
    float gapZ = 5.0f; // Jarak antar jendela
    float gapY = 2.0f; // Jarak antar tingkat
    float totalWinLen = (10 * sWinW) + (9 * gapZ);
    float startWinZ = cZ-68 + (sWinW / 2.0f);
    // Posisi Y Awal (Lantai 2)
    float startWinY = 7.0f;
    // Loop 2 Tingkat
    for (int lvl = 0; lvl < 2; lvl++) {
        float curY = startWinY + (lvl * (sWinH + gapY));
        for (int i = 0; i < 10; i++) {
            float curZ = startWinZ + (i * (sWinW + gapZ));
            // 1. Sisi Kanan (X Positif)
            glPushMatrix();
            glTranslatef(cX + 28.1, curY, curZ);
            drawBlock(0.2f, sWinH, sWinW); 
            glPopMatrix();
            // 2. Sisi Kiri (X Negatif)
            glPushMatrix();
            glTranslatef(cX - 28.1, curY, curZ);
            drawBlock(0.2f, sWinH, sWinW);
            glPopMatrix();
        }
    }
    // Slab
    glColor3fv(brownColor);
    for (int i = 0; i <= 3; i++) {
        float yPos = i * (floorH + slabT);
        glPushMatrix();
        glTranslatef(cX + 25, yPos, cZ-42);
        drawBlock(8, 0.5, 60);
        glPopMatrix();
    }
    for (int i = 0; i <= 3; i++) {
        float yPos = i * (floorH + slabT);
        glPushMatrix();
        glTranslatef(cX - 25, yPos, cZ - 42);
        drawBlock(8, 0.5, 60);
        glPopMatrix();
    }
    glPopMatrix();
}
 
void drawA9() {
    float centerX = -48.0f, centerZ = -50.0f;
    // ==========================================
    // | BAGIAN 1: GEDUNG 1 |
    // ==========================================
    float uSX = 66.0f, uSZ = 16.0f;
    // LANTAI 1, 2, 3 & ATAP
    glColor3fv(quartzColor);
    glPushMatrix(); glTranslatef(centerX, 3.0f, centerZ); drawBlock(64.0f, 6.0f, 14.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(centerX, 6.5f, centerZ); drawBlock(uSX, 1.0f, uSZ); glPopMatrix();
    glColor3fv(seaBlueColor);
    glPushMatrix(); glTranslatef(centerX, 11.5f, centerZ); drawBlock(uSX, 9.0f, uSZ); glPopMatrix();
    glColor3fv(quartzColor);
    glPushMatrix(); glTranslatef(centerX, 16.5f, centerZ); drawBlock(uSX, 1.0f, uSZ); glPopMatrix();
    glPushMatrix(); glTranslatef(centerX, 20.0f, centerZ); drawBlock(64.0f, 6.0f, 14.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(centerX, 23.5f, centerZ); drawBlock(uSX, 1.0f, uSZ); glPopMatrix();
    glColor3fv(coolWhite);
    glPushMatrix(); glTranslatef(centerX, 24.0f, centerZ); drawBlock(uSX + 2.0f, 1.0f, uSZ + 2.0f); glPopMatrix();
    // ORNAMEN KACA (SABUK & HURUF N)
    glColor3fv(coolWhite);
    float bY[3] = { 8.0f, 12.0f, 15.0f };
    for (int i = 0; i < 3; i++) {
        glPushMatrix(); glTranslatef(centerX, bY[i], centerZ + 8.1f); drawBlock(uSX, 1.0f, 0.2f); glPopMatrix();
        glPushMatrix(); glTranslatef(centerX + 25.0f, bY[i], centerZ - 8.1f); drawBlock(uSZ, 1.0f, 0.2f); glPopMatrix();
        glPushMatrix(); glTranslatef(-14.9f, bY[i], centerZ - 5.5f); drawBlock(0.2f, 1.0f, 5.0f); glPopMatrix();
        glPushMatrix(); glTranslatef(-14.9f, bY[i], centerZ + 5.5f); drawBlock(0.2f, 1.0f, 5.0f); glPopMatrix();
    }
    float oX = -14.8f;
    glPushMatrix(); glTranslatef(oX, 11.5f, centerZ - 2.0f); drawBlock(0.5f, 9.0f, 2.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(oX, 11.5f, centerZ + 2.0f); drawBlock(0.5f, 9.0f, 2.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(oX, 15.5f, centerZ); drawBlock(0.5f, 1.0f, 2.0f); glPopMatrix();
    // AKSESORIS BAWAH
    glColor3f(0.9f, 0.9f, 0.9f);
    glPushMatrix(); glTranslatef(-15.0f, 0.5f, centerZ); drawBlock(2.0f, 1.0f, 16.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(centerX, 0.5f, centerZ + 8.0f); drawBlock(64.0f, 1.0f, 2.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(centerX + 26.0f, 0.5f, centerZ - 8.0f); drawBlock(14.0f, 1.0f, 2.0f); glPopMatrix();
    // JENDELA (Lantai 1 & 3)
    glColor3fv(iceBlueColor);
    float wY[2] = { 4.0f, 20.0f };
    for (int i = 0; i < 2; i++) {
        glPushMatrix(); glTranslatef(-15.9f, wY[i], centerZ); drawBlock(0.2f, 3.0f, 2.0f); glPopMatrix();
        glPushMatrix(); glTranslatef(-15.9f, wY[i], centerZ - 4.0f); drawBlock(0.2f, 3.0f, 2.0f); glPopMatrix();
        glPushMatrix(); glTranslatef(-15.9f, wY[i], centerZ + 4.0f); drawBlock(0.2f, 3.0f, 2.0f); glPopMatrix();
        glPushMatrix(); glTranslatef(-20.0f, wY[i], centerZ - 7.1f); drawBlock(4.0f, 3.0f, 0.2f); glPopMatrix();
        glPushMatrix(); glTranslatef(-26.0f, wY[i], centerZ - 7.1f); drawBlock(4.0f, 3.0f, 0.2f); glPopMatrix();
    }
    // ==========================================
    // | BAGIAN 2: GEDUNG UTAMA |
    // ==========================================
    float c2X = -55.0f, sZ = -57.0f, wallX = -30.0f;
    float glZ = 24.0f, glCZ = -69.0f;
    // STRUKTUR KACA
    glColor3fv(quartzColor);
    glPushMatrix(); glTranslatef(c2X, 0.5f, glCZ); drawBlock(50.0f, 1.0f, glZ); glPopMatrix();
    glPushMatrix(); glTranslatef(c2X, 16.5f, glCZ); drawBlock(50.0f, 1.0f, glZ); glPopMatrix();
    glColor3fv(seaBlueColor);
    glPushMatrix(); glTranslatef(c2X, 8.5f, glCZ); drawBlock(49.9f, 15.0f, glZ - 0.1f); glPopMatrix();
    glColor3f(0.8f, 0.8f, 0.9f);
    glPushMatrix(); glTranslatef(c2X, 6.0f, glCZ); drawBlock(49.5f, 0.5f, glZ - 0.5f); glPopMatrix();
    glPushMatrix(); glTranslatef(c2X, 11.0f, glCZ); drawBlock(49.5f, 0.5f, glZ - 0.5f); glPopMatrix();
    // QUARTZ BELAKANG & JENDELA
    glColor3fv(quartzColor); glPushMatrix(); glTranslatef(c2X, 8.5f, -85.5f); drawBlock(50.0f, 17.0f, 9.0f); glPopMatrix();
    glColor3fv(iceBlueColor); glPushMatrix(); glTranslatef(wallX + 0.1f, 3.5f, -86.0f); drawBlock(0.1f, 2.0f, 3.0f); glPopMatrix();
    // Tulisan A9
    glColor3f(0.60f, 0.60f, 0.65f);
    glPushMatrix(); glTranslatef(wallX + 0.2f, 7.5f, -85.4f); glRotatef(90, 0, 1, 0); glScalef(0.009f, 0.009f, 0.009f); glLineWidth(3);
    for (const char* c = "A9"; *c; c++) glutStrokeCharacter(GLUT_STROKE_ROMAN, *c); glLineWidth(1); glPopMatrix();
    // KANOPI & JENDELA ATAS
    float canZ = -77.0f, canLen = 26.0f;
    glColor3fv(quartzColor); glPushMatrix(); glTranslatef(wallX + 1.0f, 14.5f, canZ); drawBlock(2.0f, 5.0f, canLen); glPopMatrix();
    glColor3fv(seaBlueColor);
    glPushMatrix(); glTranslatef(wallX + 2.1f, 14.5f, -69.0f); drawBlock(0.1f, 2.0f, 3.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(wallX + 2.1f, 14.5f, -77.5f); drawBlock(0.1f, 2.0f, 2.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(wallX + 2.1f, 14.5f, -86.0f); drawBlock(0.1f, 2.0f, 3.0f); glPopMatrix();
    // Kanopi Horizontal
    float hCX = wallX + 5.5f;
    glColor3fv(coolWhite); glPushMatrix(); glTranslatef(hCX, 12.5f, canZ); glScalef(7.0f, 0.8f, canLen); glLineWidth(2); glutWireCube(1.0); glLineWidth(1); glPopMatrix();
    glColor3fv(quartzColor);
    glPushMatrix(); glTranslatef(hCX, 13.0f, canZ); drawBlock(7.0f, 0.2f, canLen); glPopMatrix();
    glPushMatrix(); glTranslatef(hCX, 12.0f, canZ); drawBlock(7.0f, 0.2f, canLen); glPopMatrix();
    glPushMatrix(); glTranslatef(hCX - 5.0f, 12.5f, -60.5f); drawBlock(1.0f, 1.0f, 7.0f); glPopMatrix();
    // KABEL PENAHAN
    glColor3fv(coolWhite); glLineWidth(4.0f);
    float cabX = hCX + 3.4f, czOff[3] = { 0.0f, 6.0f, -6.0f };
    glBegin(GL_LINES);
    for (int i = 0; i < 3; i++) { glVertex3f(wallX, 16.5f, canZ + czOff[i]); glVertex3f(cabX, 13.0f, canZ + czOff[i]); }
    glEnd(); glLineWidth(1.0f);
    // PILAR PENYANGGA
    glColor3fv(coolWhite);
    float pOff[4] = { -8.0f, -16.0f, -25.0f, -32.7f };
    float stairX = -24.5f;
    for (int i = 0; i < 4; i++) { glPushMatrix(); glTranslatef(-29.5f, 6.0f, sZ + pOff[i]); drawBlock(1.0f, 12.0f, 1.0f); glPopMatrix(); }
    // ALAS, TANGGA, PRASASTI
    glColor3f(0.9f, 0.9f, 0.9f); glPushMatrix(); glTranslatef(wallX + 2.5f, 0.5f, -73.0f); drawBlock(5.0f, 1.0f, 32.0f); glPopMatrix();
    float stX = -24.5f;
    glColor3f(0.35f, 0.35f, 0.35f); glPushMatrix(); glTranslatef(stairX, 2.0f, -63.0f); drawBlock(1.0f, 4.0f, 8.0f); glPopMatrix();
    glColor3fv(iceWhiteColor);
    glPushMatrix(); glTranslatef(stairX + 0.6f, 2.8f, -60.5f); glRotatef(90, 0, 1, 0); glScalef(0.006f, 0.006f, 0.006f); glLineWidth(3);
    for (const char* c = "LABORATORY"; *c; c++) glutStrokeCharacter(GLUT_STROKE_ROMAN, *c); glPopMatrix();
    glPushMatrix(); glTranslatef(stairX + 0.6f, 1.5f, -59.7f); glRotatef(90, 0, 1, 0); glScalef(0.003f, 0.003f, 0.003f); glLineWidth(2);
    for (const char* c = "TECHNOLOGY ENTREPRENEURSHIP"; *c; c++) glutStrokeCharacter(GLUT_STROKE_ROMAN, *c); glPopMatrix();
    glColor3f(0.7f, 0.7f, 0.7f); glPushMatrix(); glTranslatef(stairX, 0.25f, -78.0f); drawBlock(1.0f, 0.5f, 22.0f); glPopMatrix();
    // PINTU & ORNAMEN
    float dZ = -77.5f;
    glColor3fv(doorGlassColor); glPushMatrix(); glTranslatef(-29.9f, 2.25f, dZ); drawBlock(0.2f, 2.5f, 3.0f); glPopMatrix();
    glColor3fv(sageGreen);
    glPushMatrix(); glTranslatef(-29.75f, 2.25f, dZ - 1.7f); drawBlock(0.5f, 2.5f, 0.4f); glPopMatrix();
    glPushMatrix(); glTranslatef(-29.75f, 2.25f, dZ + 1.7f); drawBlock(0.5f, 2.5f, 0.4f); glPopMatrix();
    glPushMatrix(); glTranslatef(-29.75f, 3.7f, dZ); drawBlock(0.5f, 0.4f, 3.8f); glPopMatrix();
    // LANTAI 3 TAMBAHAN
    float tZ = sZ - 17.0f;
    glColor3fv(quartzColor); glPushMatrix(); glTranslatef(c2X, 19.5f, tZ); drawBlock(50.0f, 6.0f, 32.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(c2X, 23.0f, tZ); drawBlock(52.0f, 1.0f, 34.0f); glPopMatrix();
    glColor3fv(coolWhite); glPushMatrix(); glTranslatef(c2X, 24.0f, tZ); drawBlock(54.0f, 1.0f, 36.0f); glPopMatrix();
    glColor3fv(iceBlueColor);
    float wz[4] = { -4.0f, -12.0f, -20.5f, -29.0f };
    for (int i = 0; i < 4; i++) { glPushMatrix(); glTranslatef(-29.9f, 20, sZ + wz[i]); drawBlock(0.2f, 3.0f, 4.0f); glPopMatrix(); }
}

void drawA10() {
    // ========================================================
    // | BAGIAN 1: GEDUNG SELATAN | (Range X: -35 s/d -80. Center -57.5.Range Z: -120 s/d -135. Center -127.5.)
    // ========================================================
    float centerX = -57.5f;
    float centerZ = -127.5f;
    float sizeX = 45.0f;
    float sizeY = 5.0f;
    float sizeZ = 15.0f;
    // 1. BADAN GEDUNG (QUARTZ)
    glColor3fv(quartzColor); glPushMatrix(); glTranslatef(centerX, 12.0f, centerZ); drawBlock(sizeX, sizeY + 19, sizeZ); glPopMatrix();
    // 2. ATAP DATAR
    glPushMatrix(); glTranslatef(centerX + 1, 6.25f, centerZ + 2.0f); drawBlock(sizeX + 2.0f, 2.5f, sizeZ + 4.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(centerX + 1, 25.0f, centerZ + 2.0f); drawBlock(sizeX + 2.5f, 3.0f, sizeZ + 4.0f); glPopMatrix();
    // ================= ORNAMEN DEPAN (MENGHADAP JALAN / X POSITIF) =================
    float faceX = -34.9f;
    glColor3fv(brownColor);
    // A. 3 PILAR VERTIKAL (POSISI 1, 8, 15)
    glPushMatrix(); glTranslatef(faceX, 2.5f, -120.5f); drawBlock(0.2f, 5.0f, 1.0f); glPopMatrix();
    // Pilar 2 (Block 8 -> Tengah -> Z = -127.5)
    glPushMatrix(); glTranslatef(faceX, 2.5f, -127.5f); drawBlock(0.2f, 5.0f, 1.0f); glPopMatrix();
    // Pilar 3 (Block 15 -> Z = -134.5)
    glPushMatrix(); glTranslatef(faceX, 2.5f, -134.5f); drawBlock(0.2f, 5.0f, 1.0f); glPopMatrix();
    // B. BALOK HORIZONTAL BAWAH (PENGHUBUNG)
    glPushMatrix(); glTranslatef(faceX, 0.0f, -124.0f); drawBlock(0.2f, 1.0f, 6.0f); glPopMatrix();
    // Celah 2 (Antara -127.5 dan -134.5) -> Center -131.0.
    glPushMatrix(); glTranslatef(faceX, 0.0f, -131.0f); drawBlock(0.2f, 1.0f, 6.0f); glPopMatrix();
    // ================= ORNAMEN SAMPING (HURUF U - MENGHADAP Z POSITIF) =================
    // Menempel di dinding samping Z = -120.0f
    float sideZ = -119.9f;
    // 1. PILAR VERTIKAL KANAN
    glPushMatrix(); glTranslatef(-35.0f, 2.5f, sideZ); drawBlock(0.2f, 5.0f, 0.2f); glPopMatrix();
    // 2. PILAR VERTIKAL KIRI
    glPushMatrix(); glTranslatef(-80.0f, 12.5f, sideZ); drawBlock(0.2f, 25.0f, 0.2f); glPopMatrix();
    // 3. BALOK HORIZONTAL BAWAH (PENGHUBUNG)
    glPushMatrix(); glTranslatef(-57.5f, 0.0f, sideZ); drawBlock(45.0f, 1.0f, 0.2f); glPopMatrix();
    // ================= JENDELA (ICE BLUE) =================
    glColor3fv(iceBlueColor);
    // Jendela 1 (Kanan)
    glPushMatrix(); glTranslatef(faceX, 2.50f, -124.0f); drawBlock(0.2f, 3.0f, 2.0f);  glPopMatrix();
    // Jendela 2 (Kiri)
    glPushMatrix(); glTranslatef(faceX, 2.50f, -131.0f); drawBlock(0.2f, 3.0f, 2.0f); glPopMatrix();
    // ================= JENDELA SAMPING KANAN (GABUNGAN 4 TINGKAT) =================
    float sideWinZ = -119.9f;
    for (float wx = -40.0f; wx > -76.0f; wx -= 8.0f) {
        for (int tier = 0; tier < 4; tier++) {
            float winY = 2.5f + (tier * 6.0f);
            glPushMatrix();
            glTranslatef(wx, winY, sideWinZ);
            drawBlock(3.0f, 2.0f, 0.2f);
            glPopMatrix();
        }
    }
    // ================= TAMBAHAN BANGUNAN MAJU 3 TINGKAT (DI ATAS ATAP) =================
    float extX = -34.75f;
    float extZ = centerZ + 2.0f;
    float extWidthZ = sizeZ + 4.0f;
    float startY = 6.0f;
    // --- LOOPING 3 TINGKAT ---
    for (int level = 0; level < 3; level++) {
        float levelHeight = 6.0f;
        float levelY = startY + (level * levelHeight) + 3.0f;
        // 1. DINDING TINGKATAN (QUARTZ)
        glColor3fv(quartzColor);
        glPushMatrix(); glTranslatef(extX, levelY, extZ); drawBlock(4.0f, levelHeight, extWidthZ); glPopMatrix();
        // 2. JENDELA (2 GRUP @ 3 JENDELA)
        glColor3fv(iceBlueColor);
        for (int j = 0; j < 3; j++) {
            glPushMatrix();
            float zPos = extZ + 2.0f + (j * 2.0f);
            glTranslatef(extX + 2.0f, levelY, zPos);
            drawBlock(0.1f, 3.0f, 1.0f);
            glPopMatrix();
        }
        for (int k = 0; k < 3; k++) {
            glPushMatrix();
            // Geser ke kiri (Z-) dari tengah.
            // Start offset -2.0, jarak antar jendela -2.0
            float zPos = extZ - 2.0f - (k * 2.0f);
            glTranslatef(extX + 2.0f, levelY, zPos);
            drawBlock(0.1f, 3.0f, 1.0f);
            glPopMatrix();
        }
    }
    // ========================================================
    // | BAGIAN 2: GEDUNG TENGAH |
    // ========================================================
    // Koordinat: X=-40 s/d -60. Y=0 s/d 25. Z=-135 s/d -157.
    float c2_X = -50.0f;  // Center X
    float c2_Y = 12.5f;   // Center Y
    float c2_Z = -146.0f; // Center Z
    float s2_X = 20.0f;
    float s2_Y = 25.0f;
    float s2_Z = 22.0f;
    // BADAN GEDUNG POLOS
    glColor3fv(quartzColor);
    glPushMatrix(); glTranslatef(c2_X, c2_Y, c2_Z); drawBlock(s2_X, s2_Y, s2_Z); glPopMatrix();
    glPushMatrix(); glTranslatef(-40.3f, 27.5f, c2_Z); drawBlock(0.5f, 5.0f, 20.0f); glPopMatrix();
    // 2. JENDELA VERTIKAL (FULL HEIGHT)
    glColor3fv(seaBlueColor);
    float winX = -39.9f;
    float winHeight = 25.0f; // Y 0-25
    float winY = 12.5f;      // Center Y
    // Jendela 1: Z -137 s/d -139 (Width 2). Center -138.0.
    glPushMatrix(); glTranslatef(winX, winY, -138.0f); drawBlock(0.2f, winHeight, 2.0f); glPopMatrix();
    // Jendela 2: Z -141 s/d -143 (Width 2). Center -142.0.
    glPushMatrix(); glTranslatef(winX, winY, -154.0f); drawBlock(0.2f, winHeight, 2.0f); glPopMatrix();
    // 3. ORNAMEN GARIS COKLAT (5 TINGKAT)
    glColor3fv(brownColor);
    float ornFaceX = -39.8f;
    float ornLenZ = 22.0f;
    for (int i = 0; i < 5; i++) {
        float ornY = 0.0f + (i * 6.0f);
        glPushMatrix();
        glTranslatef(ornFaceX, ornY, c2_Z);
        drawBlock(0.4f, 1.0f, ornLenZ);
        glPopMatrix();
    }
    glPushMatrix(); glTranslatef(-39.9f, 15.0f, -136.9f); drawBlock(0.1f, 30.0f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(-39.9f, 15.0f, -139.1f); drawBlock(0.1f, 30.0f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(-39.9f, 15.0f, -152.9f); drawBlock(0.1f, 30.0f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(-39.9f, 15.0f, -155.1f); drawBlock(0.1f, 30.0f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(-39.9f, 30.0f, -138.0f); drawBlock(0.1f, 0.2f, 2.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(-39.9f, 30.0f, -154.0f); drawBlock(0.1f, 0.2f, 2.0f); glPopMatrix();
    // 4. BALOK PUTIH UNTUK PINTU
    glColor3fv(quartzColor);
    glPushMatrix(); glTranslatef(-39.6f, 16.0f, c2_Z); drawBlock(0.6f, 32.0f, 10.0f); glPopMatrix();
    glColor3fv(quartzColor);
    glPushMatrix(); glTranslatef(-39.0f, 12.0f, c2_Z); drawBlock(0.6f, 1.0f, 10.0f); glPopMatrix();
    glColor3fv(seaBlueColor);
    glPushMatrix(); glTranslatef(-39.4f, 15.0f, c2_Z); drawBlock(0.8f, 30.0f, 8.0f); glPopMatrix();
    // --- ORNAMEN CHEVRON VERTIKAL ---
    faceX = -39.0f;
    float chevH = 2.0f, chevW = 3.0f, vDrop = 1.5f;
    glColor3fv(brownColor);
    // TINGKAT 1 (Y=16.0)
    glPushMatrix(); glTranslatef(faceX, 16.0f, c2_Z + 2.5f); glRotatef(90, 0, 1, 0); drawJajarGenjang(chevW, chevH, 0.4f, vDrop); glPopMatrix();
    glPushMatrix(); glTranslatef(faceX, 16.0f, c2_Z - 2.5f); glRotatef(90, 0, 1, 0); drawJajarGenjang(chevW, chevH, 0.4f, -vDrop); glPopMatrix();
    // TINGKAT 2 (Y=20.0)
    glPushMatrix(); glTranslatef(faceX, 20.0f, c2_Z + 2.5f); glRotatef(90, 0, 1, 0); drawJajarGenjang(chevW, chevH, 0.4f, vDrop); glPopMatrix();
    glPushMatrix(); glTranslatef(faceX, 20.0f, c2_Z - 2.5f); glRotatef(90, 0, 1, 0); drawJajarGenjang(chevW, chevH, 0.4f, -vDrop); glPopMatrix();
    // TINGKAT 3 (Y=24.0)
    glPushMatrix(); glTranslatef(faceX, 24.0f, c2_Z + 2.5f); glRotatef(90, 0, 1, 0); drawJajarGenjang(chevW, chevH, 0.4f, vDrop); glPopMatrix();
    glPushMatrix(); glTranslatef(faceX, 24.0f, c2_Z - 2.5f); glRotatef(90, 0, 1, 0); drawJajarGenjang(chevW, chevH, 0.4f, -vDrop); glPopMatrix();

    glPushMatrix(); glTranslatef(faceX, 28.0f, c2_Z + 2.0f); glRotatef(90, 0, 1, 0); drawJajarGenjang(4.0f, 2.0f, 0.4f, vDrop); glPopMatrix();
    glPushMatrix(); glTranslatef(faceX, 28.0f, c2_Z - 2.0f); glRotatef(90, 0, 1, 0); drawJajarGenjang(4.0f, 2.0f, 0.4f, -vDrop); glPopMatrix();

    glPushMatrix(); glTranslatef(-39.0f, 29.5f, c2_Z); drawBlock(0.4f, 2.0f, 8.0f); glPopMatrix();

    glColor3fv(iceWhiteColor);
    glPushMatrix(); glTranslatef(-38.9f, 28.0f, c2_Z + 0.65); glRotatef(90.0f, 0.0f, 1.0f, 0.0f); glScalef(0.003f, 0.003f, 0.003f);
    glLineWidth(2.0f);
    for (const char* c = "UNESA"; *c != '\0'; c++) glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    glPopMatrix();
    // ================= TAMBAHAN: KABEL PENAHAN KANOPI =================
    glColor3f(0.85f, 0.85f, 0.9f);
    glLineWidth(3.0f);
    float cableTopX = -39.5f;
    float cableTopY = 12.0f;
    float cableBotX = -34.6f;
    float cableBotY = 6.0f;
    glBegin(GL_LINES);
    // Kabel 1 (Sisi Z Positif)
    glVertex3f(cableTopX, cableTopY, c2_Z + 4.0f); glVertex3f(cableBotX, cableBotY, c2_Z + 4.0f);
    // Kabel 2 (Sisi Z Negatif)
    glVertex3f(cableTopX, cableTopY, c2_Z - 4.0f); glVertex3f(cableBotX, cableBotY, c2_Z - 4.0f);
    glEnd(); glLineWidth(1.0f); // Reset tebal garis
    // --- 5. KANOPI & ALAS ---
    float porchX = -37.1f;
    // A. KANOPI ATAS (Y=6.0)
    glColor3fv(quartzColor);
    glPushMatrix();
    glTranslatef(porchX, 6.0f, c2_Z);
    drawBlock(5.0f, 1.0f, 10.0f);
    glPopMatrix();
    // B. ALAS BAWAH (Y=0.5)
    glPushMatrix();
    glTranslatef(porchX, 0.5f, c2_Z);
    drawBlock(5.0f, 1.0f, 10.0f);
    glPopMatrix();
    // --- 6. TANGGA MENGELILINGI ALAS ---
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(-34.1f, 0.25f, c2_Z);
    drawBlock(1.0f, 0.5f, 12.0f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(porchX, 0.25f, c2_Z + 5.5f);
    drawBlock(5.0f, 0.5f, 1.0f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(porchX, 0.25f, c2_Z - 5.5f);
    drawBlock(5.0f, 0.5f, 1.0f);
    glPopMatrix();
    // --- 7. PINTU MASUK UTAMA (DI ATAS ALAS) ---
    float doorA10X = -39.0f;
    float doorA10Y = 2.25f;
    float doorA10Z = c2_Z;
    // A. DAUN PINTU (KACA BIRU MUDA)
    glColor3fv(doorGlassColor); // Gunakan warna kaca pintu standar
    glPushMatrix();
    glTranslatef(doorA10X, doorA10Y, doorA10Z);
    drawBlock(0.2f, 2.5f, 3.0f);
    glPopMatrix();
    // B. ORNAMEN PINTU (FRAME COKLAT)
    glColor3fv(brownColor);
    float frameX = -39.0f;
    glPushMatrix(); glTranslatef(frameX, doorA10Y, doorA10Z - 1.7f); drawBlock(0.4f, 2.5f, 0.4f); glPopMatrix();
    glPushMatrix(); glTranslatef(frameX, doorA10Y, doorA10Z + 1.7f); drawBlock(0.4f, 2.5f, 0.4f); glPopMatrix();
    glPushMatrix(); glTranslatef(frameX, 3.7f, doorA10Z); drawBlock(0.4f, 0.4f, 3.8f); glPopMatrix();
    // ========================================================
    // | BAGIAN 3: GEDUNG UTARA (Z -157 s/d -179) |
    // ========================================================
    float c3X = -57.5f;
    float c3Y = 12.5f;
    float c3Z = -168.0f;
    float s3X = 45.0f;
    float s3Y = 25.0f;
    float s3Z = 22.0f;
    // 1. BADAN GEDUNG (QUARTZ)
    glColor3fv(quartzColor);
    glPushMatrix();
    glTranslatef(c3X, c3Y, c3Z);
    drawBlock(s3X, s3Y, s3Z);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(centerX + 1, 6.25f, c3Z - 2.5f);
    drawBlock(sizeX + 2.0f, 2.5f, s3Z + 5.0f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(centerX + 1, 25.0f, c3Z - 2.5f);
    drawBlock(sizeX + 2.5f, 3.0f, s3Z + 5.0f);
    glPopMatrix();
    // --- ORNAMEN & JENDELA ---
    float wallFaceX = -34.9f;
    glColor3fv(brownColor);
    // A. 4 PILAR VERTIKAL
    // Pilar 1
    glPushMatrix(); glTranslatef(wallFaceX, 2.5f, -157.5f); drawBlock(0.4f, 5.0f, 1.0f); glPopMatrix();
    // Pilar 2
    glPushMatrix(); glTranslatef(wallFaceX, 2.5f, -163.5f); drawBlock(0.4f, 5.0f, 1.0f); glPopMatrix();
    // Pilar 3
    glPushMatrix(); glTranslatef(wallFaceX, 2.5f, -171.5f); drawBlock(0.4f, 5.0f, 1.0f); glPopMatrix();
    // Pilar 4
    glPushMatrix(); glTranslatef(wallFaceX, 2.5f, -178.5f); drawBlock(0.4f, 5.0f, 1.0f); glPopMatrix();
    // B. BALOK HORIZONTAL BAWAH
    glPushMatrix(); glTranslatef(wallFaceX, 0.0f, -168.0f); drawBlock(0.4f, 1.0f, 22.0f); glPopMatrix();
    // --- ORNAMEN SAMPING (HURUF U - MENGHADAP Z NEGATIF) ---
    float sideZNegatif = -179.1f;
    // 1. PILAR VERTIKAL KANAN
    glPushMatrix(); glTranslatef(-35.0f, 2.5f, sideZNegatif); drawBlock(0.2f, 5.0f, 0.2f);  glPopMatrix();
    // 2. PILAR VERTIKAL KIRI
    glPushMatrix(); glTranslatef(-80.0f, 12.5f, sideZNegatif); drawBlock(0.2f, 25.0f, 0.2f); glPopMatrix();
    // 3. BALOK HORIZONTAL BAWAH (PENGHUBUNG)
    glPushMatrix(); glTranslatef(-57.5f, 0.0f, sideZNegatif); drawBlock(45.0f, 1.0f, 0.2f); glPopMatrix();
    // C. 3 JENDELA (ICE BLUE)
    glColor3fv(iceBlueColor);
    // Jendela 1
    glPushMatrix(); glTranslatef(wallFaceX, 2.50f, -160.5f); drawBlock(0.2f, 3.0f, 2.0f); glPopMatrix();
    // Jendela 2
    glPushMatrix(); glTranslatef(wallFaceX, 2.50f, -167.5f); drawBlock(0.2f, 3.0f, 2.0f); glPopMatrix();
    // Jendela 3
    glPushMatrix(); glTranslatef(wallFaceX, 2.50f, -175.0f); drawBlock(0.2f, 3.0f, 2.0f); glPopMatrix();
    // ================= JENDELA SAMPING KIRI (MENGHADAP Z NEGATIF) =================
    for (float wx = -40.0f; wx > -76.0f; wx -= 8.0f) {
        for (int tier = 0; tier < 4; tier++) {
            float winY = 2.5f + (tier * 6.0f);
            glPushMatrix();
            glTranslatef(wx, winY, -179.1f);
            drawBlock(3.0f, 2.0f, 0.2f);
            glPopMatrix();
        }
    }
    // ================= TAMBAHAN: STRUKTUR MAJU 3 TINGKAT (BAGIAN 3) =================
    float ext3_X = -34.75f;
    float ext3_Z = -170.5f;
    float ext3_LenZ = 27.0f;
    float ext3_StartY = 6.0f;
    // --- LOOPING 3 TINGKAT ---
    for (int level = 0; level < 3; level++) {
        float levelH = 6.0f;
        float levelY = ext3_StartY + (level * levelH) + 3.0f; // Y Center
        // 1. DINDING QUARTZ TEBAL
        glColor3fv(quartzColor);
        glPushMatrix();
        glTranslatef(ext3_X, levelY, ext3_Z);
        drawBlock(4.0f, levelH, ext3_LenZ);
        glPopMatrix();
        // 2. JENDELA (3 GRUP)
        float groupOffsets[3] = { 9.0f, 0.0f, -9.0f };
        glColor3fv(iceBlueColor);
        for (int g = 0; g < 3; g++) {
            float currentGroupZ = ext3_Z + groupOffsets[g];
            for (int w = -1; w <= 1; w++) {
                glPushMatrix();
                glTranslatef(ext3_X + 2.1f, levelY, currentGroupZ + (w * 2.0f));
                drawBlock(0.1f, 3.0f, 1.0f);
                glPopMatrix();
            }
        }
    }
    // --- TULISAN ---
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    float textFaceX = (centerX + 1.0f) + ((sizeX + 2.5f) / 2.0f) + 0.1f;
    glTranslatef(textFaceX, 24.0f, c3Z + 9.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.013f, 0.013f, 0.013f);
    glLineWidth(3.0f);
    for (const char* c = "TEKNIK INFORMATIKA"; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(textFaceX, 9.0f, -157.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.007f, 0.007f, 0.007f);
    for (const char* c = "A10"; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glLineWidth(1.0f);
    glPopMatrix();
}

// ==========================================
// ENGINE LOGIC
// ==========================================
void processNormalKeys(unsigned char key, int x, int y) {
    keyStates[key] = true;
    if (key == 27) exit(0);
    
    // --- MODE MALAM (LIGHTING ON) ---
    if (key == 'm' || key == 'M') {
        // 1. Ubah Langit jadi Gelap
        glClearColor(0.02f, 0.02f, 0.1f, 1.0f);
        // 2. NYALAKAN SISTEM LIGHTING
        glEnable(GL_LIGHTING);
        // 3. Atur Cahaya Redup
        GLfloat nightAmbient[] = { 0.1f, 0.1f, 0.2f, 1.0f };
        GLfloat nightDiffuse[] = { 0.3f, 0.3f, 0.4f, 1.0f };
        glLightfv(GL_LIGHT0, GL_AMBIENT, nightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, nightDiffuse);
        glutPostRedisplay();
    }
    // --- MODE PAGI (LIGHTING OFF - FULL BRIGHT) ---
    if (key == 'p' || key == 'P') {
        glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
        glDisable(GL_LIGHTING);
        glutPostRedisplay();
    }
    switch (key) {
        // Reset ke Gerbang Depan
    case 'r': case 'R':
        xPos = 0.0f; zPos = 20.0f; yPos = 2.0f; angleX = 0.0f; break;
        // Gedung A1 (Kanan Depan)
    case '1':
        xPos = -10.0f; zPos = -35.0f; angleX = 1.57f; break;
        // Gedung A2 (Kanan Tengah) -> Kamera di jalan, Noleh Kanan
    case '2':
        xPos = -10.0f; zPos = -80.0f; angleX = 1.57f; break;
        // Gedung A3 (Kanan Belakang) -> Kamera di jalan, Noleh Kanan
    case '3':
        xPos = -10.0f; zPos = -125.0f; angleX = 1.57f; break;
        // Gedung A4 (Teknik Sipil - Paling Belakang)
    case '4':
        xPos = 70.0f; zPos = -300.0f; yPos = 2.0f; angleX = 3.14f; break;
        // Gedung A5 (Kiri Jauh Belakang)
    case '5':
        xPos = 180.0f; zPos = -315.0f; yPos = 2.0f; angleX = 3.14f; break;
        // Gedung A6 (Kiri Tengah Belakang)
    case '6':
        xPos = 180.0f; zPos = -150.0f; yPos = 5.0f; angleX = 0.0f; break;
        // Gedung A7 (Kiri Tengah)
    case '7':
        xPos = 170.0f; zPos = -150.0f; yPos = 5.0f; angleX = 3.14f; break;
        // Gedung A8 (Kiri Depan - Dekat A7)
    case '8':
        xPos = 180.0f; zPos = 0.0f; yPos = 10.0f; angleX = 0.0f; break;
        // Gedung A9 (Kiri Depan - Kompleks Kaca)
    case '9':
        xPos = 10.0f; zPos = -75.0f; angleX = -1.57f; break;
        // Gedung A10 (Kiri Belakang) -> Kamera di jalan, Noleh Kiri
    case '0':
        xPos = 20.0f; zPos = -145.0f; yPos = 10.0f; angleX = -1.57f; break;
    }

    angleY = 0.0f; // Reset dangak/nunduk
    lx = sin(angleX);
    lz = -cos(angleX);
    ly = tan(angleY);
}

void processNormalKeysUp(unsigned char key, int x, int y) { keyStates[key] = false; }
void processSpecialKeys(int key, int x, int y) { specialKeyStates[key] = true; }
void processSpecialKeysUp(int key, int x, int y) { specialKeyStates[key] = false; }

void timer(int value) {
    float moveSpeed = 1.0f; 
    float turnSpeed = 0.05f;
    // -- ROTASI --
    if (specialKeyStates[GLUT_KEY_LEFT]) angleX -= turnSpeed;
    if (specialKeyStates[GLUT_KEY_RIGHT]) angleX += turnSpeed;
    if (specialKeyStates[GLUT_KEY_UP] && angleY < 1.5f) angleY += turnSpeed;
    if (specialKeyStates[GLUT_KEY_DOWN] && angleY > -1.5f) angleY -= turnSpeed;
    lx = sin(angleX); lz = -cos(angleX); ly = tan(angleY);
    // -- GERAK --
    if (keyStates['w'] || keyStates['W']) { xPos += lx * moveSpeed; zPos += lz * moveSpeed; }
    if (keyStates['s'] || keyStates['S']) { xPos -= lx * moveSpeed; zPos -= lz * moveSpeed; }
    if (keyStates['a'] || keyStates['A']) { xPos += lz * moveSpeed; zPos -= lx * moveSpeed; }
    if (keyStates['d'] || keyStates['D']) { xPos -= lz * moveSpeed; zPos += lx * moveSpeed; }
    if (keyStates[32]) yPos += moveSpeed; // Spasi Naik
    if (keyStates['c'] || keyStates['C']) yPos -= moveSpeed; // C Turun
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void mouseWheel(int button, int dir, int x, int y) {
    if (dir > 0) {
        fov -= 2.0f; // Zoom In
    }
    else {
        fov += 2.0f; // Zoom Out
    }
    if (fov < 10.0f) fov = 10.0f;
    if (fov > 90.0f) fov = 90.0f;
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, (float)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(xPos, yPos, zPos, xPos + lx, yPos + ly, zPos + lz, 0.0f, 1.0f, 0.0f);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    // ----- Render Dunia -----
    drawjalandantrotoar();
    drawInterior();
    drawGapura();
    drawPosSatpam();
	drawMenaraAir();
	drawMusala();
    drawLorong();
    drawE1();
    drawA1();
    drawA2();
    drawA3();
    drawA4();
    drawA5();
    drawA6();
	drawA7();
	drawA8();
    drawA9();
    drawA10();
    drawCoordinates();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float ratio = (float)w / h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, ratio, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    // --- SETTING LIGHTING TAPI DIMATIKAN DULU ---
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    // Matikan Lighting agar mulai dalam mode "Warna Asli" (Pagi)
    glDisable(GL_LIGHTING);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Fakultas Teknik");
    init();
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(processNormalKeys);
    glutKeyboardUpFunc(processNormalKeysUp);
    glutSpecialFunc(processSpecialKeys);
    glutSpecialUpFunc(processSpecialKeysUp);
    glutDisplayFunc(display);
    glutMouseFunc(NULL); 
    glutMouseWheelFunc(mouseWheel);
    glutMainLoop();
    return 0;
}