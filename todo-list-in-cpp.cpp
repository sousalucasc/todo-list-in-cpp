#include <iostream>
#include <string> 
#include <list>
#include <ctime>

class TodoItem {
private:
    int id; 
    std::string description; 
    bool completed; 
public: 
    TodoItem() :id(0), description(""), completed(false) {} // Constructor com Initialization-list
    ~TodoItem() = default; // Destructor setado para default, ja que nao sera necessario limpeza manual
    // std::string gerencia sua memoria no heap internamente (RAII)
    // int e bool nao precisam serem deletados manualmente anyway

    bool create(std::string new_description) {
        //generates a random integer between 1 and 100
        id = rand() % 100 + 1;
        description = new_description;
        return true;
    }

    int getId() {return id;}
    std::string getDescription() { return description;}
    bool isCompleted() { return completed; }
    void setCompleted(bool val) { completed = val; }
};

int main(){
    int input_option;
    int input_id;
    std::string input_description;
    std::string version = "v0.0.1";
    std::list<TodoItem> todoItems; // Lista
    std::list<TodoItem>::iterator it; // Iteration Variable, como um cursor que aponta para cada item da lista

    srand(time(NULL)); // Seed randomica para o srand com base no horario
    todoItems.clear(); // Limpar lista antes de começar nosso loop (redundante)

    //TodoItem test; // Criando objeto test
    //test.create("this is a test"); // Passando descricao para a funcao criar
    //todoItems.push_back(test); // Adicionando na lista todoItems


    while (1) { // Loop infinito
        system("cls"); 
        // Limpa nosso CLI em cada iteração do loop

        std::cout << "Lista de Tarefas em C++ - " << version << std::endl;
        std::cout << std::endl;

        for (it = todoItems.begin(); it != todoItems.end(); it++) { // Rodar o loop até o ultimo elemento

            std::string completed = it->isCompleted() ? "FEITO" : "PENDENTE"; 
            // Operador ternario (condicional) compacto
            // Basicamente um if/else que retorna um valor

            std::cout << it->getId() << " | " << it->getDescription() << " | "
                << completed << std::endl;
            // Printa na tela cada item de cada lista, usando o iterador It como ponteiro!
        }

        if (todoItems.empty()) { // Caso lista esteja vazia, ira promptar para adicao de tarefas
            std::cout << "Adicione sua primeira tarefa!\n\n";
        }

        std::cout << "\n[1] Adicionar nova tarefa" << std::endl;
        std::cout << "[2] Completar uma tarefa" << std::endl;
        std::cout << "[3] Sair do programa" << std::endl;

        std::cout << "Opcao: ";
        std::cin >> input_option;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (input_option == 3) { // Caso queira sair do programa
            std::cout << "\nTenha um belo dia!" << std::endl;
            break;
        }
        else if (input_option == 1) {
            std::cout << "Adicione uma descricao: ";
            std::cin.clear(); // Comecando com um inputbuffer zerado
            std::cin.ignore(); // Ignorar primeiro retorno
            std::getline(std::cin, input_description); // Setar descricao podendo ter espacos

            TodoItem newItem;
            newItem.create(input_description);
            todoItems.push_back(newItem);
        }
        else if (input_option == 2) { // Caso queira marcar complete
            std::cout << "Qual o ID para marcar complete?" << std::endl;
            std::cin >> input_id;

            for (it = todoItems.begin(); it != todoItems.end(); it++) {

                if (input_id == it->getId()) {
                    it->setCompleted(true);
                    break;
                }
            }

        }
    }

    return 0;
}

