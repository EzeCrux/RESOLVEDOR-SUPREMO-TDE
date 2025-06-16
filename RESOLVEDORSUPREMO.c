#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float parse_coef(char *term, const char *var)
{
    char buffer[20];
    float coef = 0;

    if (strcmp(term, var) == 0)
        return 1;
    if (strcmp(term, "-") == 0 || strcmp(term, "-x") == 0 || strcmp(term, "-x^2") == 0)
        return -1;

    sscanf(term, "%[^x]", buffer);
    coef = atof(buffer);
    return coef;
}

void resolverEquacao(char *eq)
{
    float a = 0, b = 0, c = 0;
    char *ladoEsq, *ladoDir;
    char temp[100];
    strcpy(temp, eq);

    // Remover espacos
    char limpo[100] = {0};
    for (int i = 0, j = 0; temp[i]; i++)
        if (temp[i] != ' ')
            limpo[j++] = temp[i];

    ladoEsq = strtok(limpo, "=");
    ladoDir = strtok(NULL, "=");
    if (!ladoEsq || !ladoDir || strcmp(ladoDir, "0") != 0)
    {
        printf("Equacao invalida. Use formato correto com = 0.\n");
        return;
    }

    char termo[20];
    int i = 0, j = 0, sinal = 1;
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

        if (strstr(termo, "x^2"))
        {
            a += sinal * parse_coef(termo, "x^2");
        }
        else if (strstr(termo, "x"))
        {
            b += sinal * parse_coef(termo, "x");
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
        if (x == -0.0f)
            x = 0.0f;
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
            if (x == -0.0f)
                x = 0.0f;
            printf("Grau: 2o grau | Possui Solucao Real: Sim | Solucao: x=%.2f\n", x);
        }
        else
        {
            float x1 = (-b + sqrt(delta)) / (2 * a);
            float x2 = (-b - sqrt(delta)) / (2 * a);
            if (x1 == -0.0f)
                x1 = 0.0f;
            if (x2 == -0.0f)
                x2 = 0.0f;
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
        system("cls");
        printf("===============================\n");
        printf("    RESOLVEDOR SUPREMO EM C    \n");
        printf("===============================\n");
        printf("Digite a equacao (ex: x^2+2x+1=0 ou 5x+10=0):\n> ");

        getchar();
        fgets(equacao, sizeof(equacao), stdin);
        equacao[strcspn(equacao, "\n")] = 0;

        resolverEquacao(equacao);

        printf("\nDeseja resolver outra equacao? (1 - Sim | 0 - Nao): ");
        scanf("%d", &continuar);
    }

    printf("\nObrigado por usar o RESOLVEDOR SUPREMO EM C!\n");
    return 0;
}
