// ═══════════════════════════════════════════════
//  raycast.cpp  –  Implementação do Ray Casting
// ═══════════════════════════════════════════════

#include "raycast.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace rc {

// ───────────────────────────────────────────────────────────────
//  intersectar
//
//  Um raio é definido por:  P(t) = olho + t * d
//
//  A esfera é o conjunto de pontos P tais que |P - C|² = R²
//  Substituindo P(t):
//      |olho + t*d - C|² = R²
//
//  Definindo  oc = olho - C  (vetor do centro da esfera ao olho):
//      |t*d + oc|² = R²
//      t²(d·d) + 2t(d·oc) + (oc·oc - R²) = 0
//
//  Equação quadrática  At² + Bt + C = 0  onde:
//      A = d · d
//      B = 2 * (d · oc)
//      C = oc · oc  -  R²
//
//  Δ = B² - 4AC
//      Δ < 0  → sem intersecção
//      Δ ≥ 0  → t = (-B ± √Δ) / 2A
//               pegamos o menor t positivo (ponto mais próximo)
// ───────────────────────────────────────────────────────────────
float intersectar(const Vec3& olho, const Vec3& d, const Esfera& esfera)
{
    Vec3  oc    = olho - esfera.centro;
    float A     = d.dot(d);
    float B     = 2.0f * d.dot(oc);
    float C     = oc.dot(oc) - esfera.raio * esfera.raio;
    float delta = B*B - 4.0f*A*C;

    if (delta < 0.0f) return -1.0f;   // raio não acerta a esfera

    float sqrtD = std::sqrt(delta);
    float t1    = (-B - sqrtD) / (2.0f * A);  // ponto de entrada
    float t2    = (-B + sqrtD) / (2.0f * A);  // ponto de saída

    if (t1 > 1e-4f) return t1;   // entrada visível → retorna
    if (t2 > 1e-4f) return t2;   // câmera dentro da esfera → retorna saída
    return -1.0f;                 // esfera atrás da câmera
}

// ───────────────────────────────────────────────────────────────
//  renderizar
//
//  Constrói a base ortonormal da câmera a partir dos
//  5 conceitos (olho, look_at, up, fov, nx × ny) e lança
//  um raio por pixel.  Para cada pixel escolhe a esfera mais
//  próxima (menor t positivo) ou a cor de fundo.
// ───────────────────────────────────────────────────────────────
void renderizar(const Camera& cam,
                const std::vector<Esfera>& esferas,
                const Color& corFundo,
                const std::string& saida)
{
    // ── Base ortonormal da câmera ──────────────────
    //
    //   w: aponta de look_at para olho (eixo Z invertido)
    //   u: aponta para a direita  (up × w)
    //   v: aponta para cima na câmera (w × u)
    //
    Vec3 w = (cam.olho - cam.look_at).normalized();
    Vec3 u = cam.up.cross(w).normalized();
    Vec3 v = w.cross(u);

    // ── Dimensões da viewport ──────────────────────
    //
    //  halfH = tan(fov/2)  → metade da altura em unidades de mundo
    //  halfW = halfH * (nx/ny)  → metade da largura (ajuste de aspecto)
    //
    float halfH = std::tan((cam.fov * 3.14159265f / 180.0f) / 2.0f);
    float halfW = halfH * (float(cam.nx) / float(cam.ny));

    // Canto inferior-esquerdo da viewport
    //   cantoInferior = olho - w - v*halfH - u*halfW
    Vec3 canto = cam.olho - w - v * halfH - u * halfW;

    // Vetores que percorrem a viewport pixel a pixel
    Vec3 horizontal = u * (2.0f * halfW);
    Vec3 vertical   = v * (2.0f * halfH);

    // ── Buffer de pixels (RGB) ─────────────────────
    std::vector<unsigned char> buffer(cam.nx * cam.ny * 3);

    for (int j = cam.ny - 1; j >= 0; --j) {         // linhas: de cima para baixo
        for (int i = 0; i < cam.nx; ++i) {           // colunas: da esquerda para a direita

            // Coordenadas normalizadas [0,1] do pixel na viewport
            float s = float(i) / float(cam.nx - 1);
            float t = float(j) / float(cam.ny - 1);

            // Ponto na viewport e direção do raio
            Vec3 alvo = canto + horizontal * s + vertical * t;
            Vec3 d    = (alvo - cam.olho).normalized();

            // ── Encontra a esfera mais próxima ────────
            float tMin        = std::numeric_limits<float>::max();
            const Esfera* hit = nullptr;

            for (const auto& esfera : esferas) {
                float tHit = intersectar(cam.olho, d, esfera);
                if (tHit > 0.0f && tHit < tMin) {
                    tMin = tHit;
                    hit  = &esfera;
                }
            }

            // ── Cor do pixel ──────────────────────────
            Color cor = corFundo;
            if (hit) cor = hit->cor;

            // Escreve no buffer (linha j de cima para baixo)
            int idx = ((cam.ny - 1 - j) * cam.nx + i) * 3;
            buffer[idx + 0] = (unsigned char)cor.r;
            buffer[idx + 1] = (unsigned char)cor.g;
            buffer[idx + 2] = (unsigned char)cor.b;
        }
    }

    // ── Salva PPM (P3 / ASCII) ────────────────────
    std::string ppmFile = saida + ".ppm";
    std::ofstream ppm(ppmFile);
    ppm << "P3\n" << cam.nx << " " << cam.ny << "\n255\n";
    for (int i = 0; i < cam.nx * cam.ny; ++i)
        ppm << (int)buffer[i*3] << " " << (int)buffer[i*3+1] << " " << (int)buffer[i*3+2] << "\n";
    ppm.close();
    std::cout << "[rc] PPM salvo em: " << ppmFile << "\n";

    // ── Salva PNG via stb_image_write ─────────────
    std::string pngFile = saida + ".png";
    if (stbi_write_png(pngFile.c_str(), cam.nx, cam.ny, 3, buffer.data(), cam.nx * 3))
        std::cout << "[rc] PNG salvo em: " << pngFile << "\n";
    else
        std::cerr << "[rc] Erro ao salvar PNG.\n";
}

} // namespace rc
