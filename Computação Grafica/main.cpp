// ═══════════════════════════════════════════════
//  main.cpp
//
//  Dependências externas (header-only):
//    stb_image_write.h → https://github.com/nothings/stb
//
//  Compilar:
//    g++ -O2 -o raytracer main.cpp raycast.cpp -lm
//
//  Rodar:
//    ./raytracer   →  gera saida.ppm  e  saida.png
// ═══════════════════════════════════════════════

#include "raycast.h"

int main()
{
    using namespace rc;

    // ── 1. Esferas da cena ────────────────────────
    std::vector<Esfera> esferas;

    esferas.push_back({ Vec3( 0.0f, 0.0f, -3.0f), 1.0f, Color( 65, 105, 225) }); // azul
    esferas.push_back({ Vec3( 2.2f, 0.0f, -4.0f), 1.0f, Color(220,  60,  60) }); // vermelho
    esferas.push_back({ Vec3(-2.2f, 0.0f, -4.0f), 1.0f, Color( 50, 180,  80) }); // verde

    // ── 2. Câmera com os 5 conceitos ─────────────
    Camera cam;
    cam.olho    = Vec3(0.0f, 0.0f, 1.0f);   // posição 3D da câmera no mundo
    cam.look_at = Vec3(0.0f, 0.0f, 0.0f);   // ponto para onde a câmera aponta
    cam.up      = Vec3(0.0f, 1.0f, 0.0f);   // vetor de referência vertical
    cam.fov     = 60.0f;                     // campo de visão vertical em graus
    cam.nx      = 800;                       // resolução: colunas
    cam.ny      = 600;                       //            linhas

    // ── 3. Renderiza ──────────────────────────────
    Color corFundo(15, 15, 30);
    renderizar(cam, esferas, corFundo, "saida");

    return 0;
}
