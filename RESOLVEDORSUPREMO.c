#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void removeEspacos(char *str)
{
    int i, j = 0;
    char temp[100];
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ')
            temp[j++] = str[i];
    }
    temp[j] = '\0';
    strcpy(str, temp);
}

float extrairCoeficiente(char *termo)
{
    if (termo[0] == 'x')
        return 1.0;
    if (termo[0] == '-' && termo[1] == 'x')
        return -1.0;

    char buffer[30] = {0};
    sscanf(termo, "%[^x]", buffer);
    return atof(buffer);
}

void resolverEquacao(char *entrada)
{
    float a = 0, b = 0, c = 0;
    char eq[100];
    strcpy(eq, entrada);
    removeEspacos(eq);

    char *ladoEsq = strtok(eq, "=");
    char *ladoDir = strtok(NULL, "=");

    if (!ladoEsq || !ladoDir || strcmp(ladoDir, "0") != 0)
    {
        printf("Equacao invalida. Certifique-se de usar o formato correto (ex: x^2+2x+1=0).\n");
        return;
    }

    int i = 0, j = 0, sinal = 1;
    char termo[30];

    while (ladoEsq[i])
    {
        if (ladoEsq[i] == '+')
        {
            sinal = 1;
            i++;
        }
        else if (ladoEsq[i] == '-')
        {
            sinal = -1;
            i++;
        }

        j = 0;
        while (ladoEsq[i] && ladoEsq[i] != '+' && ladoEsq[i] != '-')
        {
            termo[j++] = ladoEsq[i++];
        }
        termo[j] = '\0';

        if (strstr(termo, "x^2") != NULL)
        {
            a += sinal * extrairCoeficiente(termo);
        }
        else if (strstr(termo, "x") != NULL && strstr(termo, "^") == NULL)
        {
            b += sinal * extrairCoeficiente(termo);
        }
        else
        {
            c += sinal * atof(termo);
        }
    }

    printf("\n--- Resultado ---\n");

    if (a == 0 && b == 0)
    {
        printf("Equacao invalida: nao ha termo com x.\n");
        return;
    }

    if (a == 0)
    {
        float x = -c / b;
        printf("Grau: 1o grau | Possui Solucao Real: Sim | Solucao: x=%.2f\n", x);
    }
    else
    {
        float delta = b * b - 4 * a * c;

        if (delta < 0)
        {
            printf("Grau: 2o grau | Possui Solucao Real: Nao | Solucao: x=N.A.\n");
        }
        else if (delta == 0)
        {
            float x = -b / (2 * a);
            printf("Grau: 2o grau | Possui Solucao Real: Sim | Solucao: x=%.2f\n", x);
        }
        else
        {
            float x1 = (-b + sqrt(delta)) / (2 * a);
            float x2 = (-b - sqrt(delta)) / (2 * a);
            printf("Grau: 2o grau | Possui Solucao Real: Sim | Solucao: x=%.2f, x=%.2f\n", x1, x2);
        }
    }
}

int main()
{
    int continuar = 1;
    char equacao[100];

    while (continuar)
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        printf("===============================\n");
        printf("    RESOLVEDOR SUPREMO EM C    \n");
        printf("===============================\n");
        printf("Digite a equacao (ex: x^2+2x+1=0 ou 5x+10=0):\n> ");

        getchar();
        fgets(equacao, sizeof(equacao), stdin);
        equacao[strcspn(equacao, "\n")] = '\0';

        resolverEquacao(equacao);

        printf("\nDeseja resolver outra equacao? (1 - Sim | 0 - Nao): ");
        scanf("%d", &continuar);
    }

    printf("\nObrigado por usar o RESOLVEDOR SUPREMO EM C!\n");
    return 0;
}