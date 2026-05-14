#pragma once

#include <cmath>
#include <string>
#include <vector>

// ═══════════════════════════════════════════════
//  raycast.h  –  Ray Casting simples
//  Conceitos: olho, look_at, up, fov, nx × ny
// ═══════════════════════════════════════════════

namespace rc {

// ───────────────────────────────────────────
//  Vetor 3D
// ───────────────────────────────────────────
struct Vec3 {
    float x, y, z;
    Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    Vec3  operator+(const Vec3& v) const { return { x+v.x, y+v.y, z+v.z }; }
    Vec3  operator-(const Vec3& v) const { return { x-v.x, y-v.y, z-v.z }; }
    Vec3  operator*(float k)       const { return { x*k,   y*k,   z*k   }; }
    Vec3  operator-()              const { return { -x, -y, -z }; }

    float dot(const Vec3& v)   const { return x*v.x + y*v.y + z*v.z; }
    Vec3  cross(const Vec3& v) const {
        return { y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x };
    }
    float norm()       const { return std::sqrt(x*x + y*y + z*z); }
    Vec3  normalized() const { float n = norm(); return n > 0 ? (*this)*(1.0f/n) : Vec3(); }
};

// ───────────────────────────────────────────
//  Cor RGB (0–255)
// ───────────────────────────────────────────
struct Color {
    int r, g, b;
    Color(int r = 0, int g = 0, int b = 0) : r(r), g(g), b(b) {}
};

// ───────────────────────────────────────────
//  Esfera: centro, raio e cor sólida
// ───────────────────────────────────────────
struct Esfera {
    Vec3  centro;
    float raio;
    Color cor;
};

// ───────────────────────────────────────────
//  Câmera – os 5 conceitos do ray casting
// ───────────────────────────────────────────
struct Camera {
    Vec3  olho;     // posição 3D da câmera no mundo
    Vec3  look_at;  // ponto para onde a câmera aponta
    Vec3  up;       // vetor de referência vertical  ex: (0,1,0)
    float fov;      // campo de visão vertical em graus
    int   nx, ny;   // resolução: nx colunas × ny linhas
};

// ───────────────────────────────────────────
//  Funções
// ───────────────────────────────────────────

// Testa se o raio (olho + t*d) acerta a esfera.
// Retorna o menor t > 0 no ponto de intersecção, ou -1 se não acertar.
float intersectar(const Vec3& olho, const Vec3& d, const Esfera& esfera);

// Renderiza a cena: gera PPM e PNG automaticamente.
void renderizar(const Camera& cam,
                const std::vector<Esfera>& esferas,
                const Color& corFundo,
                const std::string& saida);   // ex: "saida" → saida.ppm + saida.png

} // namespace rc
