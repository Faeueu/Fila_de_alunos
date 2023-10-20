#include <iostream>
using namespace std;

struct Conteudo {
    string nome;
    Conteudo* next;
};

struct Disciplina {
    string nome;
    int quantidadeCreditos;
    Conteudo* listaConteudos;
    Disciplina* next;
};

struct Aluno {
    string nome;
    string cpf;
    int idade;
    string matricula;
    Disciplina* listaDisciplina;
};

struct No {
    Aluno aluno;
    No* next;
};

struct Fila {
    No* inicio;
    No* fim;
};

bool isEmpty(Fila &fila) {
    if (fila.inicio == NULL && fila.fim == NULL) {
        return true;
    } else {
        return false;
    }
}

void Enqueue(Fila &fila, Aluno aluno) {
    No* novoAluno = new No;
    novoAluno->aluno = aluno;
    novoAluno->next = NULL;

    if (isEmpty(fila)) {
        fila.inicio = novoAluno;
        fila.fim = novoAluno;
    } else {
        fila.fim->next = novoAluno;
        fila.fim = novoAluno;
    }
}

void Dequeue(Fila &fila) {
    if (isEmpty(fila)) {
        cout << "Fila vazia. Nenhum aluno a ser removido." << endl;
    } else {
        No* temp = fila.inicio;
        fila.inicio = fila.inicio->next;
        delete temp;
    }
}

Aluno Front(Fila &fila) {
    if (isEmpty(fila)) {
        cout << "Fila vazia. Nenhum aluno na frente." << endl;
        return Aluno();
    } else {
        return fila.inicio->aluno;
    }
}

void printAluno(Aluno aluno) {
    cout << "Nome: " << aluno.nome << endl;
    cout << "CPF: " << aluno.cpf << endl;
    cout << "Idade: " << aluno.idade << endl;
    cout << "Matricula: " << aluno.matricula << endl;
    cout << "Disciplinas: " << endl;
    Disciplina* cadeira = aluno.listaDisciplina;
    while (cadeira != NULL) {
        cout << "  Nome da disciplina: " << cadeira->nome << endl;
        cout << "  Creditos: " << cadeira->quantidadeCreditos << endl;
        cout << "  Conteudos: ";
        Conteudo* modulo = cadeira->listaConteudos;
        while (modulo != NULL) {
            cout << modulo->nome << " ";
            modulo = modulo->next;
        }
        cout << endl;
        cadeira = cadeira->next;
    }
    cout << "*******************************" << endl;
}

int Size(Fila &fila) {
    No* temp = fila.inicio;
    int contador = 0;
    while (temp != NULL) {
        contador++;
        temp = temp->next;
    }
    return contador;
}

void addDisciplina(Aluno &aluno, Disciplina disciplina){
    if(aluno.listaDisciplina == NULL){
        aluno.listaDisciplina = new Disciplina(disciplina);
    } else {
        Disciplina *temp = aluno.listaDisciplina;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new Disciplina(disciplina);
    }
}

void removeDisciplina(Aluno &aluno, string nomeDisciplina){
    if(aluno.listaDisciplina == NULL){
        cout << "Lista de disciplinas vazia" << endl;
    } else {
        Disciplina *atual = aluno.listaDisciplina;
        Disciplina *anterior = NULL;

        while(atual != NULL && atual->nome != nomeDisciplina){
            anterior = atual;
            atual = atual->next;
        }
        if(atual == NULL){
            cout << "Disciplina nao encontrada" << endl;
        } else {
            if(anterior == NULL){
            aluno.listaDisciplina = atual->next;
            } else {
                anterior->next = atual->next;
            }
            delete atual;
        }
    }
}

void printDisciplina(Aluno &aluno){
    if(aluno.listaDisciplina == NULL){
        cout << "Disciplina vazia" << endl;
    } else {
        cout << "Disciplinas do aluno " << aluno.nome << ":" << endl;
        Disciplina *temp = aluno.listaDisciplina;
        while (temp != NULL) {
            cout << temp->nome << endl;
            temp = temp->next;
        }
    }
}

void addConteudo(Disciplina &disciplina, string nomeConteudo){
    if(disciplina.listaConteudos == NULL){
        disciplina.listaConteudos = new Conteudo({nomeConteudo, NULL});
    } else {
        Conteudo *temp = disciplina.listaConteudos;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new Conteudo({nomeConteudo, NULL});
    }
}

void removeConteudo(Disciplina &disciplina, string nomeConteudo){
    if(disciplina.listaConteudos == NULL){
        cout << "Lista de conteudos vazia" << endl;
    } else {
        Conteudo *atual = disciplina.listaConteudos;
        Conteudo *anterior = NULL;

        while(atual != NULL && atual->nome != nomeConteudo){
            anterior = atual;
            atual = atual->next;
        }

        if(atual == NULL){
            cout << "Conteudo nao encontrado" << endl;
        } else {
            if(anterior == NULL){ 
            disciplina.listaConteudos = atual->next;
            } else {
                anterior->next = atual->next;
            }
            delete atual;
        }
    }
}

void printConteudos(Disciplina &disciplina) {
    cout << "Conteudos da disciplina " << disciplina.nome << ": " << endl;
    Conteudo *temp = disciplina.listaConteudos;
    while (temp != NULL) {
        cout << temp->nome << endl;
        temp = temp->next;
    }
}

void printTodosAlunos(Fila &fila){
    No *temp = fila.inicio;
    while(temp != NULL){
        printAluno(temp->aluno);
        temp = temp->next;
    }
}
int main() {
    Fila fila = {NULL, NULL};

    Disciplina cadeira1 = {"Matematica", 4, NULL, NULL};
    Disciplina cadeira2 = {"Portugues", 3, NULL, NULL};
    Disciplina cadeira3 = {"Fisica", 5, NULL, NULL};


    Conteudo modulo1 = {"Calculo", NULL};
    Conteudo modulo2 = {"Algebra", NULL};
    Conteudo modulo3 = {"Sujeito", NULL};
    Conteudo modulo4 = {"Predicado", NULL};

    cadeira1.listaConteudos = &modulo1;
    modulo1.next = &modulo2;
    cadeira2.listaConteudos = &modulo3;
    modulo3.next = &modulo4;

    Aluno aluno1 = {"Rafael", "123.456.789-00", 20, "001", &cadeira1};
    Aluno aluno2 = {"Joseph", "987.654.321-00", 22, "002", &cadeira2};

    Enqueue(fila, aluno1);
    Enqueue(fila, aluno2);

    cout << "Tamanho da fila: " << Size(fila) << endl;
    cout << "Aluno na frente da fila: " << endl;
    printAluno(Front(fila));

    Dequeue(fila);

    cout << "Tamanho da fila apos remocao: " << Size(fila) << endl;

    cout << "Aluno na frente da fila: " << endl;
    printAluno(Front(fila));

    addDisciplina(aluno1, cadeira3);
    printDisciplina(aluno1);
    cout << endl;

    addConteudo(cadeira3, "Leis de Newton");
    addConteudo(cadeira3, "Eletrodinamica");

    printConteudos(cadeira1);
    //printConteudos(cadeira2);
    //
    printConteudos(cadeira3);
    
    //printTodosAlunos(fila);

    return 0;
}
