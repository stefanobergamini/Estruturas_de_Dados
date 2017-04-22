// "Copyright [2017] Stefano Bergamini Poletto"

#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H
#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
//! Lista encadeada
class LinkedList {
 public:
    //! Construtor padrao
    LinkedList() {
        head = nullptr;
        size_ = 0;
    }  // construtor padrão
    //! Destrutor padrao
    ~LinkedList() {
        clear();
    }  // destrutor
    //! Limpa Lista
    void clear() {
        Node* proximo = head;
        Node* apagar = nullptr;
        for (int i = 0 ; i < size_ ; i++) {
            if (proximo -> next() != nullptr) {
                apagar = proximo;
                proximo = proximo -> next();
                delete apagar;
                size_--;
            } else {
                delete proximo;
            }
        }
    size_ = 0;
    }  // limpar lista
    //! push_back
    void push_back(const T& data) {
        Node* atual = head;
        if (empty()) {
            push_front(data);
        } else {
            for (int i = 0 ; i < size_-1 ; i++) {
                atual = atual -> next();
            }
            Node* novo = new Node(data , nullptr);
            atual -> next(novo);
            size_++;
        }
    }  // inserir no fim
    //! push_front
    void push_front(const T& data) {
        Node* aux = head;
        Node* dado = new Node(data , aux);
        head = dado;
        size_++;
    }  // inserir no início
    //! insert
    void insert(const T& data, std::size_t index) {
        if (index > size_ || index < 0) {
            throw std::out_of_range("Posição Invalida!");
        } else if (index == 0) {
            push_front(data);
        } else {
            Node* posicao = head;
            Node* aux = nullptr;
            for (int i = 0 ; i < size_ ; i++) {
                if (i == index) {
                    Node* novo = new Node(data , posicao);
                    aux -> next(novo);
                    size_++;
                    break;
                } else {
                aux = posicao;
                posicao = posicao -> next();
                }
            }
        }
    }  // inserir na posição
    //! insert_sorted
    void insert_sorted(const T& data) {  // inserir em ordem
        if (size_ == 0) {
            Node* novo = new Node(data, nullptr);
            head = novo;
            size_++;
        } else {
            Node* antes = nullptr;
            Node* atual = head;
            for (int i = 0; i < size_; i ++) {
                if (i == 0 && head -> data() > data) {
                    push_front(data);
                    return;
                }
                if (atual -> data() > data) {
                    Node* novo = new Node(data, atual);
                    antes -> next(novo);
                    size_++;
                    return;
                } else {
                    if (i == size_-1) {
                        Node* novo = new Node(data, nullptr);
                        atual -> next(novo);
                        size_++;
                        return;
                    }
                }
                antes = atual;
                atual = atual -> next();
            }
        }
    }  // inserir em ordem
    //! at (retorna elementeo em posiçao)
    T& at(std::size_t index) {
        Node* posicao = head;
        if (index >= size_ || index < 0) {
            throw std::out_of_range("Posição Invalida!!!");
        } else {
            for (int i = 0 ; i < size_ ; i++) {
                if (i == index) {
                    return posicao -> data();
                } else {
                    posicao = posicao -> next();
                }
            }
        }
        return posicao ->  data();
    }  // acessar um elemento na posição index
    //! pop (retira da posicao)
    T pop(std::size_t index) {
    T dado;
    if (index < 0 || index > size_-1) {
        throw std::out_of_range("Posição Invalida!!");
        } else {
        Node* atual = head;
        Node* proximo = head;
        Node* anterior = nullptr;
        for (int i = 0 ; i < size_-1 ; i++) {
            if (i == index) {
               dado = atual -> data();
               anterior -> next(proximo);
               delete atual;
               size_--;
               break;
            } else {
                anterior = atual;
                atual = atual -> next();
                proximo = atual -> next();
            }
        }
    }
    return dado;
    }  // retirar da posição
    //! pop_back
    T pop_back() {
        T dado;
        Node* aux = head;
        if (empty()) {
            throw std::out_of_range("VAZIO");
        } else {
        for (int i = 0 ; i < size_ ; i++) {
            if (i == size_-1) {
                dado = aux -> data();
                delete aux;
                size_--;
            } else {
                aux = aux -> next();
            }
        }
        }
        return dado;
    }  // retirar do fim
    //! pop_front
    T pop_front() {
        T dado;
        Node* posicao = head;
        if (empty()) {
            throw std::out_of_range("Lista Vazia!");
        } else {
            head = head -> next();
            dado = posicao -> data();
            delete (posicao);
            size_--;
            return dado;
        }
    }  // retirar do início
    //! remove
    void remove(const T& data) {
    Node* atual = head;
    Node* anterior = nullptr;
    Node* proximo = head -> next();
    for (int i = 0 ; i < size_-1; i++) {
        if (atual -> data() == data) {
            anterior -> next(proximo);
            delete atual;
            size_--;
        } else {
            anterior = atual;
            atual = atual -> next();
            proximo = atual -> next();
        }
    }
    }  // remover específico
    //! empty
    bool empty() const {
        return size_ == 0;
    }  // lista vazia
    //! contains
    bool contains(const T& data) const {
        Node* posicao = head;
        if (empty()) {
            throw std::out_of_range("Lista Vazia!");
        } else {
            for (int i = 0; i < size_ ; i++) {
                if (posicao -> data() == data) {
                    return true;
                } else {
                    posicao = posicao -> next();
                }
            }
        }
        return false;
    }  // contém
    //! find
    std::size_t find(const T& data) const {
        Node* posicao = head;
        T dado;
        for (int i = 0 ; i < size_ ; i++) {
            dado = posicao -> data();
            if (dado == data) {
                return i;
            } else {
            posicao = posicao -> next();
            }
            }
        return size_;
    }  // posição do dado
    //! size
    std::size_t size() const {
        return size_;
    }  // tamanho da lista

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif
