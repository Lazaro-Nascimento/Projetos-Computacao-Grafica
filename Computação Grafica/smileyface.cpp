#include <iostream>
#include <fstream>
#include <cmath> // Necessário para sqrt() e pow()

int main() {
    const int dim = 500; // Largura e altura iguais
    std::ofstream arquivo("/mnt/c/Users/lazar/Downloads/circulo.ppm");

    arquivo << "P3\n" << dim << " " << dim << "\n255\n";

    for (int y = 0; y < dim; ++y) {
        for (int x = 0; x < dim; ++x) {
            // 1. Normalizar as coordenadas (0.0 a 1.0)
            float u = (float)x / dim;
            float v = (float)y / dim;

            // 2. Definir o centro e o raio (também normalizados)
            float centro_x = 0.5f;
            float centro_y = 0.5f;
            float raio = 0.3f;

            // 3. Cálculo da Distância Euclidiana
            // d = sqrt( (x2-x1)^2 + (y2-y1)^2 )
            float dist = std::sqrt(std::pow(u - centro_x, 2) + std::pow(v - centro_y, 2));
            // 4. Teste do Círculo


 	    float pos_olho_direito = (float)(0.5 - raio + raio + raio/2.0);

	    float pos_olho_esquerdo = (float)(0.5 - raio/2);

	    //std::cout << linha << "\n";
            if(pos_olho_direito == u && pos_olho_esquerdo == v){
		float raio_olho_direito = ;
		centrox_olho_direito = pos_olho_direito;
                centroy_olho_direito = pos_olho_esquerdo;
	    }

	    else if (dist < raio) {
                arquivo << "255 255 255\n"; // Branco (dentro do círculo)
            }
	    else {
                arquivo << "0 0 0\n";       // Preto (fundo)
            }
        }
     }
    arquivo.close();
    return 0;
}
