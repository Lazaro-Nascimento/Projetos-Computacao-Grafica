#include <iostream>
#include <fstream>
#include <cmath>
#define RAIO 0.3f

struct olho_t{
    float centroX;
    float centroY;
    float distancia;
};

struct sorriso_t{
    float distancia;
    float centroX;
    float centroY;
};

struct rosto_t{
    float distancia;
    float centroX;
    float centroY;
};

void DesenharFormatoPPM(rosto_t rosto, olho_t olhoEsquerdo, olho_t olhoDireito, sorriso_t sorriso, std::ofstream& arquivo, int dim);

int main() {

    rosto_t rosto;

    olho_t olhoEsquerdo, olhoDireito;

    sorriso_t sorriso;

    int dim = 400;

    float alturaDosOlhos, posicaoXOlhoDireito, posicaoXOlhoEsquerdo;

    alturaDosOlhos = (float)(0.5 - RAIO/2);

    posicaoXOlhoDireito = (float)(0.5 - RAIO + RAIO + RAIO/2.0);

    posicaoXOlhoEsquerdo = (float)(0.5 - RAIO/2);

    rosto.centroX = 0.5f;
    rosto.centroY = 0.5f;

    sorriso.centroX = 0.5f;
    sorriso.centroY = 0.5f;

    olhoDireito.centroX = posicaoXOlhoDireito;
    olhoDireito.centroY = alturaDosOlhos;

    olhoEsquerdo.centroX = posicaoXOlhoEsquerdo;
    olhoEsquerdo.centroY = alturaDosOlhos;

    std::ofstream arquivo("/mnt/c/Users/lazar/Downloads/smileyface.ppm");

    arquivo << "P3\n" << dim << " " << dim << "\n255\n";

    DesenharFormatoPPM(rosto, olhoEsquerdo, olhoDireito, sorriso, arquivo, dim);

    arquivo.close();
    return 0;
}

void DesenharFormatoPPM(rosto_t rosto, olho_t olhoEsquerdo, olho_t olhoDireito, sorriso_t sorriso, std::ofstream& arquivo, int dim)
{
     for (int y = 0; y < dim; ++y) 
	 {
        for (int x = 0; x < dim; ++x)
		{
            float u = (float)x / dim;
            float v = (float)y / dim;
			
            rosto.distancia = std::sqrt(std::pow(u - rosto.centroX, 2) + std::pow(v - rosto.centroY, 2));
	    	olhoEsquerdo.distancia = std::sqrt(std::pow(u - olhoEsquerdo.centroX, 2) + std::pow(v - olhoEsquerdo.centroY, 2));
		    olhoDireito.distancia = std::sqrt(std::pow(u - olhoDireito.centroX, 2) + std::pow(v - olhoDireito.centroY, 2));
		    sorriso.distancia = std::sqrt(std::pow(u - sorriso.centroX, 2) + std::pow(v - sorriso.centroY,2));
	
		    if (olhoDireito.distancia < RAIO/5)
		    {
				arquivo << "0 0 0\n";
		    }
	
		    else if (olhoEsquerdo.distancia < RAIO/5)
			{
				arquivo << "0 0 0\n";
			}
	
		    else if (sorriso.distancia < RAIO/2 && v > rosto.centroY && sorriso.distancia > RAIO/3)
		    {
				arquivo << "0 0 0\n";
		    }
	
		    else if (rosto.distancia < RAIO)
			{
				arquivo << "255 255 0\n";
	        }
	
		    else 
			{
				arquivo << "0 0 0\n";
			}
		}
     }
}
