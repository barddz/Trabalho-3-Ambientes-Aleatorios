// Pedro Barddal da Silva - RA: 21007988

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

int main()
{
    srand(time(0));
    int num_salas, num_sujeiras, sala, salas_retornadas = 0, menor_suj = 9, maior_suj = 0, dist_menor = 0, dist_maior = 0, suj_limpas = 0, num_rand;
    char ambiente, modo, lado, limpador;
    bool stop = false, return_d = false, return_e = false, falhou = false;

    cout << "Digite o numero de salas (1-10): ";
    cin >> num_salas;

    cout << "Digite o numero de sujeiras: ";
    cin >> num_sujeiras;

    cout << "Digite 'o' para ambiente observavel ou outro caractere para parcialmente observavel: ";
    cin >> ambiente;

    cout << "Digite 'a' para controlador automatico ou 'm' para manual: ";
    cin >> modo;

    cout << "O aspirador tera falhas? Digite '1' para Sim e '2' para Nao: ";
    cin >> limpador;

    vector<char> salas(num_salas, '?');
    vector<bool> visitadas(num_salas, false);
    for (int i = 0; i < num_sujeiras; ++i)
    {
        sala = rand() % num_salas;
        if (salas[sala] != 'x')
        {
            salas[sala] = 'x';
            if (sala > maior_suj)
            {
                maior_suj = sala;
            }
            if (menor_suj > sala)
            {
                menor_suj = sala;
            }
        }
        else
        {
            --i;
        }
    }

    int pos_aspirador = rand() % num_salas;
    char comando;

    dist_maior = maior_suj - pos_aspirador;
    dist_menor = pos_aspirador - menor_suj;

    if (ambiente == 'o')
    {
        for (int i = 0; num_salas > i; i++)
            visitadas[i] = true;
    }
    do
    {
        cout << '\n';
        cout << "SALA      | ";

        for (int i = 0; i < num_salas; ++i)
        {
            char c = 65 + i;
            cout << c << ' ';
        }

        cout << '\n';
        cout << "Aspirador | ";

        for (int i = 0; i < num_salas; ++i)
        {
            cout << (i == pos_aspirador ? 'x' : ' ') << ' ';
        }

        cout << '\n';
        cout << "Sujeira   | ";

        for (int i = 0; i < num_salas; ++i)
        {
            if (i == pos_aspirador || visitadas[i])
            {
                cout << (salas[i] == 'x' ? 'x' : ' ') << ' ';
            }
            else
            {
                cout << '?' << ' ';
            }
        }
        cout << '\n';
        cout << '\n';

        if (salas[pos_aspirador] == 'x' && limpador == '1')
        {
            num_rand = rand() % 10;
            if (num_rand < 7)
            {
                char c = 65 + pos_aspirador;
                cout << "Aspirador limpou a sala " << c << '\n'
                     << '\n';
                ++suj_limpas;
                salas[pos_aspirador] = ' ';
                falhou = false;
            }
            else
            {
                cout << "Aspirador falhou em limpar!" << '\n'
                     << '\n';
                if (modo == 'a')
                {
                    cout << "Aspirador permanecera na sala para tentar limpar" << '\n'
                         << '\n';
                }
                falhou = true;
            }
        }

        if (salas[pos_aspirador] == 'x' && limpador == '2')
        {
            char c = 65 + pos_aspirador;
            cout << "Aspirador limpou a sala " << c << '\n'
                 << '\n';
            ++suj_limpas;
            salas[pos_aspirador] = ' ';
            falhou = false;
        }
        visitadas[pos_aspirador] = true;

        if (modo == 'm')
        {

            cout << "Digite '1' para mover para a esquerda, '2' para mover para a direita, '3' para limpar a mesma sala: ";
            cin >> comando;

            if (comando == '1' && pos_aspirador > 0)
            {
                --pos_aspirador;
            }
            else if (comando == '2' && pos_aspirador < num_salas - 1)
            {
                ++pos_aspirador;
            }
        }

        if (modo == 'a' && ambiente != 'o' && falhou == false)
        {
            if (pos_aspirador + 1 > num_salas / 2 && lado != 'e')
            {
                lado = 'd';
            }
            else if (lado != 'd')
            {
                lado = 'e';
            }

            if (salas_retornadas + 1 == num_salas)
            {
                stop = true;
            }

            if (return_e == true && pos_aspirador > 0)
            {
                --pos_aspirador;
                ++salas_retornadas;
            }

            else if (return_d == true && pos_aspirador < num_salas - 1)
            {
                ++pos_aspirador;
                ++salas_retornadas;
            }

            if (lado == 'd' && pos_aspirador < num_salas - 1 && return_e == false && return_d == false)
            {
                ++pos_aspirador;
            }
            if (lado == 'e' && pos_aspirador > 0 && return_d == false && return_e == false)
            {
                --pos_aspirador;
            }

            if (lado == 'd' && pos_aspirador == num_salas - 1)
            {
                return_e = true;
            }
            if (lado == 'e' && pos_aspirador == 0)
            {
                return_d = true;
            }
        }

        if (modo == 'a' && ambiente == 'o' && falhou == false)
        {
            if ((dist_maior < dist_menor && dist_maior > 0) || menor_suj > pos_aspirador)
            {
                lado = 'd';
            }
            else if (lado != 'd')
            {
                lado = 'e';
            }

            if (suj_limpas == num_sujeiras)
            {
                stop = true;
            }

            if (return_e == true && pos_aspirador > 0)
            {
                --pos_aspirador;
            }

            else if (return_d == true && pos_aspirador < maior_suj)
            {
                ++pos_aspirador;
            }

            if (lado == 'd' && pos_aspirador < maior_suj && return_e == false && return_d == false)
            {
                ++pos_aspirador;
            }
            if (lado == 'e' && pos_aspirador > menor_suj && return_d == false && return_e == false)
            {
                --pos_aspirador;
            }

            if (lado == 'd' && pos_aspirador == maior_suj)
            {
                return_e = true;
            }
            if (lado == 'e' && pos_aspirador == menor_suj)
            {
                return_d = true;
            }
        }
    } while (stop != true);
    return 0;
}