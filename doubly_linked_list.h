// Copyright [2017] <Stefano Bergamini Poletto>

#include <cstdint>
#include <stdexcept>

namespace structures {

/**
 * @brief      List of doubly linkeds.
 *
 * @tparam     T
 */
template<typename T>
class DoublyLinkedList {
 public:
    DoublyLinkedList() {
        head = nullptr;
        size_ = 0u;
    }
    //! destrutor
    ~DoublyLinkedList() {
        clear();
    }
    //! limpa lista
    void clear() {
        Node *atual, *anterior;
        atual = head;
        head = nullptr;
        while ( atual != nullptr ) {
            anterior = atual;
            atual = atual->next();
            delete anterior;
        }
        size_ = 0u;
    }
    //! insere no fim
    void push_back(const T& data) {
        insert(data, size_);
    }
    //! insere no inicio
    void push_front(const T& data) {
        Node *novo = new Node(data);
        if (novo == nullptr) {
            throw std::out_of_range("full list.");
        } else {
            novo->next(head);
            novo->prev(nullptr);
            head = novo;
            if (novo->next() != nullptr) {
                novo->next()->prev(novo);
            }
            ++size_;
        }
    }
    //! insere na posição desejada
    void insert(const T& data, std::size_t index) {
        Node *anterior, *novo;
        if (index > size_) {
          throw std::out_of_range("position error.");
        } else if (index == 0) {
            push_front(data);
        } else {
            novo = new Node(data);
            if (novo == nullptr) {
                throw std::out_of_range("full");
            } else {
                anterior = head;
                for (int i = 0; i < index - 1; ++i) {
                    anterior = anterior->next();
                }
                novo->next(anterior->next());
                if (novo->next() != nullptr) {
                    novo->next()->prev(novo);
                }
                anterior->next(novo);
                ++size_;
            }
        }
    }
    //! insere em ordem
    void insert_sorted(const T& data) {
        Node *atual;
        int posicao;
        if (empty()) {
            return push_front(data);
        } else {
            atual = head;
            posicao = 0;
            while (atual->next() != nullptr && data > atual->data()) {
                atual = atual->next();
                ++posicao;
            }
            if (data > atual->data()) {
                return(insert(data, posicao+1));
            } else {
                return(insert(data, posicao));
            }
        }
    }
    //! retira da posição
    T pop(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds");
        } else if (empty()) {
            throw std::out_of_range("Empty pop");
        } else if (index == 0) {
            return pop_front();
        } else {
            Node *anterior, *eliminar;
            T volta;
            anterior = head;
            for (int i = 0; i < index-1; ++i) {
                anterior = anterior->next();
            }
            eliminar = anterior->next();
            volta = eliminar->data();
            anterior->next(eliminar->next());
            if (eliminar->next() != nullptr)
                eliminar->next()->prev(anterior);

            --size_;
            delete eliminar;
            return volta;
        }
    }
    //! retira do fim
    T pop_back() {
        return pop(size_-1);
    }
    //! retira do inicio
    T pop_front() {
        Node *saiu;
        T volta;
        if (empty()) {
            throw std::out_of_range("empty list.");
        } else {
            saiu = head;
            volta = saiu->data();
            head = saiu->next();
            if (head != nullptr) {
                head->prev(nullptr);
            }
            --size_;
            delete saiu;
            return volta;
        }
    }
    //! retira desejado
    void remove(const T& data) {
        pop(find(data));
    }
    //! retorna se vazia
    bool empty() const {
        return size_ == 0;
    }
    //! retorna se contem certo elemento
    bool contains(const T& data) const {
        Node *aux = head;
        while (aux != nullptr) {
            if (aux->data() == data) {
                return true;
            }
            aux = aux->next();
        }
        return false;
    }
    //! acesso a um elemento
    T& at(std::size_t index) {
        if (index > size_) {
            throw std::out_of_range("position error.");
        } else if (empty()) {
            throw std::out_of_range("empty.");
        } else {
            Node *aux = head;
            for (int i = 0; i < index; ++i) {
                if (aux->next() == nullptr) {
                    throw std::out_of_range("Erro de posicao.");
                }
                aux = aux->next();
            }
            return aux->data();
        }
    }
    //! getter constante a um elemento
    const T& at(std::size_t index) const {
        Node *aux = head;
        for (int i = 0; i < index; ++i) {
            if (aux->next() == nullptr) {
                throw std::out_of_range("Erro de posicao.");
            }
            aux = aux->next();
        }
        return aux->data();
    }
    //! posição de um dado
    std::size_t find(const T& data) const {
        Node *caixa = head;
        std::size_t pos;
        if (empty()) {
            return (-1);
        } else {
            pos = 0;
            while (caixa->data() != data) {
                caixa = caixa->next();
                ++pos;
                if (caixa == nullptr) {
                    break;
                }
            }
            return pos;
        }
    }
    //! retorna o tamanho
    std::size_t size() const {
        return size_;
    }
 private :
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }
        void next(Node* node) {
            next_ = node;
        }
        Node* prev() {
            return prev_;
        }

        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }
     private :
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;
    std::size_t size_;
};

}  // namespace structures
