#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char nome[50];
    char raca[50];
    int idade;
    float salario;
    char CPF[12];
} Pessoa;

typedef struct 
{
    char nome[50];
    int codigo;
    Pessoa *cidadaos;
    int capacidade;
} Cidade;

Cidade *NovaCidade(Cidade * censo, int* tam){
    // Basicamente so realoca 
    Cidade *aux;
    aux = realloc(censo, sizeof(Cidade) * (*(tam) + 1));
    if (aux != NULL)
    {
        censo = aux;
    } else {
        printf("Problema dos brabos encontrado na alocacao de memoria!\n");
        exit(1);
    }
    
    // Zera a capacidade de cada cidade para nao acumular lixo
    censo[*tam].capacidade = 0;
    printf("Digite o nome e o codigo , respectivamente, para registar essa nova cidade:\n");
    scanf(" %s %d", censo[*tam].nome, &censo[*tam].codigo);
    (*tam)++;
    // Limpa o terminal
    system("clear");
    return censo;
}
void InserirOuAtualizar(Cidade *censo, int tam){
    int aux_codigo, aux_index;
    printf("Qual o codigo da cidade que deseja inserir/atualizar:\n");
    // Vai procuar o index da cidade que tem o codigo correspondente
    scanf("%d", &aux_codigo);
    for (int i = 0; i < tam; i++)
    {
        if (aux_codigo == censo[i].codigo)
        {
            aux_index = i;
        }
    }
    Pessoa aux_pessoa;
    int flag = 0, index_pessoa = -1;
    printf("Digite Nome, Raca, Idade, Salario e CPF da nova pessoa:\n");
    //Basicamente cadrastar uma nova pessoa
    scanf(" %s %s %d %f %s", aux_pessoa.nome, aux_pessoa.raca, &aux_pessoa.idade, &aux_pessoa.salario, aux_pessoa.CPF);
    for (int i = 0; i < censo[aux_index].capacidade; i++)
    { // Procurar para ver se tem alguem com o CPF dito ja
        if (strcmp(aux_pessoa.CPF, censo[aux_index].cidadaos[i].CPF) == 0)
        {
            flag = 1, index_pessoa = i;
        }
    }
    if (flag != 1)
    {
        // Se nao ele realloca e adiciona no ultimo index
        Pessoa *aux;
        aux = realloc(censo[aux_index].cidadaos, sizeof(Pessoa) * (censo[aux_index].capacidade + 1));
        if (aux != NULL)
        {
            censo[aux_index].cidadaos = aux;
        } else {
            printf("Problema dos brabos encontrado na alocacao de memoria!\n");
            exit(1);
        }
        censo[aux_index].cidadaos[censo[aux_index].capacidade] = aux_pessoa;
        censo[aux_index].capacidade++;
        printf("Pessoa adicionada!\n");
    } else {
        // Se existir alguem ele atualiza os dados
        censo[aux_index].cidadaos[index_pessoa] = aux_pessoa;
        printf("Dados atualizados\n");
    } 
    system("clear");
}
void Remover(Cidade *censo, int tam){
    printf("Digite o codigo da cidade e o CPF da pessoa cancelada, vulgo removida:\n");
    int aux_codigo, aux_index = -1, flag = 0, index_procurado = -1;
    char aux_CPF[13];
    scanf(" %d %s", &aux_codigo, aux_CPF);
    // Procuar a cidade com o codigo e depois dentro dela a pessoa com o CPF correspondente
    for (int i = 0; i < tam; i++)
    {
        if (censo[i].codigo == aux_codigo)
        {
            aux_index = i;
        }
    }
    for (int i = 0; i < censo[aux_index].capacidade; i++)
    {
        if (strcmp(censo[aux_index].cidadaos[i].CPF, aux_CPF) == 0) 
        {
            flag = 1;
            index_procurado = i;
        }
    }
    if (flag == 1)
    { // Achou
        printf("Pessoa encontrada:\n");
        // Faz uma sobrescrita para eliminar o elemento que nao queremos
        for (int i = index_procurado; i < censo[aux_index].capacidade; i++)
        {
            censo[aux_index].cidadaos[i] = censo[aux_index].cidadaos[i + 1];
        }
        Pessoa *aux;
        censo[aux_index].capacidade--;
        aux = realloc(censo[aux_index].cidadaos, sizeof(Pessoa) * (censo[aux_index].capacidade));
        if (aux != NULL)
        {
            censo[aux_index].cidadaos = aux;
        } else {
            printf("Problema dos brabos encontrado na alocacao de memoria!\n");
            exit(1);
        }
    } else if (flag == 0)
    { // n achou
        printf("Pessoa nao encontrada!\n");
    }
    
    
}
void Procura(Cidade *censo, int tam){
    // Faz a exata mesma coisa do remover mas printa ao inves de exlcuir o dado
    printf("Digite o codigo da cidade e o CPF da pessoa a ser procurada:\n");
    int aux_codigo, aux_index = -1, flag = 0, index_procurado = -1;
    char aux_CPF[13];
    scanf(" %d %s", &aux_codigo, aux_CPF);
    for (int i = 0; i < tam && flag != 1; i++)
    {
        if (censo[i].codigo == aux_codigo)
        {
            aux_index = i, flag = 1;
        }
    }
    if (flag == 1)
    {
        flag = 0;
        for (int i = 0; i < censo[aux_index].capacidade; i++)
        {
            if (strcmp(censo[aux_index].cidadaos[i].CPF, aux_CPF) == 0) 
            {
                flag = 1;
                index_procurado = i;
            }
        }
        if (flag == 1)
        {
            printf("Nome: %s - raca: %s - Idade: %d - Salario %.2f CPF: %s\n", censo[aux_index].cidadaos[index_procurado].nome, censo[aux_index].cidadaos[index_procurado].raca, censo[aux_index].cidadaos[index_procurado].idade, censo[aux_index].cidadaos[index_procurado].salario, censo[aux_index].cidadaos[index_procurado].CPF);
        } else {
            printf("Nao foi possivel achar usuario!\n");
        }
    } else {
        printf("Cidade nao foi encontrada!\n");
    }
}
// E é sql é?
void ViewTable(Cidade *censo, int tam){
    // So printa tudo tendo
    for (int i = 0; i < tam; i++)
    {
        printf("-Cidade %s do codigo %d\n", censo[i].nome, censo[i].codigo);
        for (int z = 0; z < censo[i].capacidade; z++)
        {
            printf("Nome: %s - raca: %s - Idade: %d - Salario %.2f CPF: %s\n", censo[i].cidadaos[z].nome, censo[i].cidadaos[z].raca, censo[i].cidadaos[z].idade, censo[i].cidadaos[z].salario, censo[i].cidadaos[z].CPF);
        }
        
    }
    
}
void Desaloca(Cidade *censo, int tam){
    // So da free em cada cidadao de cada cidade e depois no ponteiro das cidades
    for (int i = 0; i < tam; i++)
    {
        free(censo[i].cidadaos);
    }
    free(censo);
}

int main(){
    Cidade *censo = NULL;
    int qtd_cidades = 0, opcao = -1;
    do
    {
        printf("-----------------Menu-------------------\n");
        printf("1- Nova cidade | 2- Inserir/Atualizar\n3- Remover     | 4- Procurar\n5- Ver tudo    | 6- Sair\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            censo = NovaCidade(censo, &qtd_cidades);
        break;
        case 2:
            InserirOuAtualizar(censo, qtd_cidades);
        break;
        case 3:
            Remover(censo, qtd_cidades);
        break;
        case 4:
            Procura(censo, qtd_cidades);
        break;
        case 5:
            ViewTable(censo, qtd_cidades);
        break;
        case 6:
            printf("Saindo...\n");
        break;
        default:
            printf("Algo de errado n ta certo\n");
            break;
        }
    } while (opcao != 6);
    Desaloca(censo, qtd_cidades);
    return 0;
}