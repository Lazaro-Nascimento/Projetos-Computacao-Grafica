#include <iostream>
#include <fstream>
#include <cmath> // Necessário para sqrt() e pow()


struct olho_t{
    float centroX;
    float centroY;
};
int main() {

    olho_t olhoEsquerdo, olhoDireito;

    const int dim = 400;

    float centro_x = 0.5f, centro_y = 0.5f, raio = 0.3f, distanciaRosto, distanciaOlhoEsquerdo, distanciaOlhoDireito, distanciaSorriso;

    float alturaDosOlhos = (float)(0.5 - raio/2);

    float posicaoXOlhoDireito = (float)(0.5 - raio + raio + raio/2.0);

    float posicaoXOlhoEsquerdo = (float)(0.5 - raio/2);

    olhoDireito.centroX = posicaoXOlhoDireito;
    olhoDireito.centroY = alturaDosOlhos;

    olhoEsquerdo.centroX = posicaoXOlhoEsquerdo;
    olhoEsquerdo.centroY = alturaDosOlhos;

    std::ofstream arquivo("/mnt/c/Users/lazar/Downloads/circulo.ppm");

    arquivo << "P3\n" << dim << " " << dim << "\n255\n";

    for (int y = 0; y < dim; ++y) {
        for (int x = 0; x < dim; ++x) {
            // 1. Normalizar as coordenadas (0.0 a 1.0)
            float u = (float)x / dim;
            float v = (float)y / dim;

            // d = sqrt( (x2-x1)^2 + (y2-y1)^2 )
            distanciaRosto = std::sqrt(std::pow(u - centro_x, 2) + std::pow(v - centro_y, 2));

	    distanciaOlhoEsquerdo = std::sqrt(std::pow(u - olhoEsquerdo.centroX, 2) + std::pow(v - olhoEsquerdo.centroY, 2));

	    distanciaOlhoDireito = std::sqrt(std::pow(u - olhoDireito.centroX, 2) + std::pow(v - olhoDireito.centroY, 2));

	    distanciaSorriso = std::sqrt(std::pow(u - centro_x, 2) + std::pow(v - centro_y,2));

	    if (distanciaOlhoDireito < raio/5)
	    {
		arquivo << "0 0 0\n";
	    }

	    else if (distanciaOlhoEsquerdo < raio/5)
            {
                arquivo << "0 0 0\n";
            }

	    else if (distanciaSorriso < raio/2 && v > centro_y && distanciaSorriso > raio/3)
	    {
		arquivo << "0 0 0\n";
	    }

	    else if (distanciaRosto < raio) {
                arquivo << "255 255 0\n"; // Branco (dentro do círculo)
            }

	    else {
                arquivo << "0 0 0\n";       // Preto (fundo)
            }
        }
     }
    arquivo.close();
    return 0;
}
