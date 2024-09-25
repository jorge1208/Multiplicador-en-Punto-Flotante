#include <iostream>
#include <cmath>
#include <limits> 

struct componentes_float
{
    bool signo;
    int exponente;
    float mantisa;
};

componentes_float Separar_patrones(float num)
{
    unsigned int _num = *reinterpret_cast<unsigned int*>(&num);
    componentes_float componentes;
    componentes.signo = (_num >> 31) & 1; 
    componentes.exponente = ((_num >> 23) & 0xFF) - 127;
    componentes.mantisa = 1 + ((_num & 0x7FFFFF) / pow(2, 23)); 
    return componentes;
}

float multiplicacion(float multiplicando, float multiplicador)
{
    componentes_float c1 = Separar_patrones(multiplicando);
    componentes_float c2 = Separar_patrones(multiplicador);
    
    if (c1.mantisa == 0 || c2.mantisa == 0)
    {
        return 0.0f;
    }
    else
    {
        int nuevo_exponente = c1.exponente + c2.exponente;
        if (nuevo_exponente > std::numeric_limits<float>::max_exponent) 
        {
            std::cout << "¡Alerta de overflow! La suma de los exponentes excede el rango representable." << std::endl;
            return std::numeric_limits<float>::quiet_NaN();
        }
        else if (nuevo_exponente < std::numeric_limits<float>::min_exponent) 
        {
            std::cout << "¡Alerta de underflow! La suma de los exponentes es demasiado pequeña para ser representada con precisión." << std::endl;
            return std::numeric_limits<float>::quiet_NaN(); 
        }
        else 
        {
            float nueva_mantisa = c1.mantisa * c2.mantisa;

            while (nueva_mantisa >= 2.0f) {
                nueva_mantisa /= 2.0f;
                nuevo_exponente++; 
            }

           
            float resultado = nueva_mantisa * pow(2, nuevo_exponente);
            return resultado;
        }
    }
}

int main()
{
    float n_1, n_2;
    std::cout<<"Ingrese un numero: "<<std::endl;
    std::cin>>n_1;
    std::cout<<"Ingrese un numero: "<<std::endl;
    std::cin>>n_2;

    float result = multiplicacion(n_1, n_2);

    std::cout << "El resultado de la multiplicación es: " << result << std::endl;

    return 0;
}
