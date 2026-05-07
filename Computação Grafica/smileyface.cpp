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

struct vector3 {
	float x;
	float y;
	float z;
	vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};



float  dot(vector3 u, vector3 v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}


vector3  cross(vector3 u, vector3 v)
{
	return vector3(u.y * v.z - u.z * v.y,  u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}


vector3 normalize(vector3 u)
{
	float  norma = sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
	if (norma != 0)
	{
		return vector3(u.x/norma, u.y/norma, u.z/norma);
	}
	return vector3(0, 0, 0);
}

vector3 prod(vector3 u, float k)
{
	return vector3(u.x * k, u.y * k, u.z * k);
}

vector3 soma3(vector3 u, vector3 v, vector3 w)
{
	return vector3(u.x + v.x + w.x, u.y + v.y + w.y, u.z + v.z + w.z);
}

vector3 sub(vector3 u, vector3 w)
{
	return vector3(u.x - w.x, u.y - w.y, u.z - u.z);
}



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

    std::ofstream arquivo("PATH_FILE");

    arquivo << "P3\n" << dim << " " << dim << "\n255\n";

    DesenharFormatoPPM(rosto, olhoEsquerdo, olhoDireito, sorriso, arquivo, dim);

    arquivo.close();
    return 0;
}

void DesenharFormatoPPM(rosto_t rosto, olho_t olhoEsquerdo, olho_t olhoDireito, sorriso_t sorriso, std::ofstream& arquivo, int dim)
{

     vector3 u = vector3(0, 0, 0);
     vector3 v =  vector3(0, 0, 0);
     vector3 w = vector3(0, 0, 0); 
     vector3 o = vector3(0, 0, 0);
     float nx = dim;
     float ny = dim;
     float w = 200;
     float h = 200;


     for (int i = 0; i < dim; ++i) 
	 {
        for (int j = 0; j < dim; ++j)
	{
            float S = ((i+0.5)/nx - 0.5) * w;
            float T = (0.5 - (j+0.5)/ny - 0.5) * h;
	    vector3 d = normalize(soma(prod(u, S), prod(v, T), prod(w, -1)));

	    float A = dot(d, d);
		
	    for (esfera em esferas)
 	    {
		vector3 oc = sub(o, esfera.C);
		float B =  prod(prod(d, oc), 2);
		float C = dot(oc, oc) - esfera.R  * esfera.R;
		float delta = B*B - 4 * A * C;

		if (delta < 0)
		{

			pixel = cor_de_fundo;
		} else if (delta  == 0)

		{

			float t =  -B/(2*A);
			if (t > 0)
			{
				vector3 PI = soma(o , prod(d, t));
				normal_esfera = calculada usando o centro da esfera e o ponto PI
			}
			else if (t <= 0)
			{
				pixel = cor_de_fundo;
			}
		}
		else
		{

			pegar o menor t que é maior do que zero e calcular a cor com o ponto de intersecao correspondente.
		}
	    }

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
