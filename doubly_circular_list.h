// Copyright [2017] <Stefano Bergamini>
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {
//! classe lista circular dupla
template<typename T>
class DoublyCircularList {
 public:
    //! construtor
    DoublyCircularList() {
        head = nullptr;
        size_ = 0u;
    }
    //! destrutor
    ~DoublyCircularList() {
        clear();
    }
    //! limpa lista
    void clear() {
        Node *atual, *anterior;
        atual = head;
        auto i = 0u;
        while (i < size_) {
            anterior = atual;
            atual = atual->next();
            delete anterior;
            ++i;
        }
        size_ = 0u;
        head = nullptr;
    }
    //! insere no fim
    void push_back(const T& data) {
        if (empty()) {
            push_front(data);
        } else {
            auto aux = end();
            auto novo = new Node(data, head, aux);
            head->prev(novo);
            aux->next(novo);
            ++size_;
        }
    }
    //! insere no início
    void push_front(const T& data) {
        auto novo = new Node(data);
        if (novo == nullptr) {
            throw std::out_of_range("erro lista cheia");
        }
        if (empty()) {
            head = novo;
            head->next(head);
            head->prev(head);
            ++size_;
        } else {
            novo->next(head);
            novo->prev(end());
            head = novo;
            end()->next(head);
            ++size_;
        }
    }
    //! insere na posição
    void insert(const T& data, std::size_t index) {
        if (index > size_)
            throw std::out_of_range("erro da posição");
        if (index == 0)
            return push_front(data);
        auto aux = head;
        for (int i = 0; i < index - 1; ++i) {
            aux = aux -> next();
        }
        auto novo = new Node(data, aux->next(), aux);
        if (novo == nullptr) {
            throw std::out_of_range("erro lista cheia");
        }
        aux->next()->prev(novo);
        aux->next(novo);
        ++size_;
    }
    //! insere em ordem
    void insert_sorted(const T& data) {
        if (empty())
            return push_front(data);
        auto atual = head;
        int index = 0u;
        while (index < size_ && data > atual->data()) {
            atual = atual->next();
            index++;
        }
        return insert(data, index);
    }
    //! retira da posição
    T pop(std::size_t index) {
        T dado;
        if (index == 0) {
            pop_front();
        } else if (index >= size_) {
            throw std::out_of_range("FORA DOS PADRÕES");
        } else {
            Node* atual = head;
            for (int i = 0 ; i != index ; i++) {
                atual = atual -> next();
            }
            Node *anterior, *proximo;
            anterior = atual->prev();
            proximo = atual->next();
            anterior -> next(proximo);
            proximo -> prev(anterior);
            dado = atual->data();
            delete atual;
            size_--;
        }
        return dado;
    }
    //! retira do fim
    T pop_back() {
        if (empty()) {
            throw std::out_of_range("lista vazia");
        }
        if (size_ == 1) {
            return pop_front();
        }
        auto dado = end()->data();
        auto del = end();
        del->prev()->next(head);
        head->prev(del->prev());
        delete del;
        --size_;
        return dado;
    }
    //! retira do início
    T pop_front() {
        Node *atual = head;
        T dado;
        if (empty()) {
            throw std::out_of_range("lista vazia");
        } else {
            dado = atual->data();
            Node *ulti = end();
            head = atual->next();
            head -> prev(ulti);
            ulti -> next(head);
            --size_;
            delete atual;
            return dado;
        }
    }
    //! retira específico
    void remove(const T& data) {
        pop(find(data));
    }
    //! lista vazia
    bool empty() const {
        return size_ == 0;
    }
    //! contém
    bool contains(const T& data) const {
        if (empty()) {
            throw std::out_of_range("lista vazia!");
        } else if (find(data) == size_) {
            return false;
        } else {
            return true;
        }
    }
    //! acesso a um elemento (checando limites)
    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Erro de posicao.");
        } else if (empty()) {
            throw std::out_of_range("lista vazia");
        } else {
            auto curr = head;
            for (int i = 0u; i < index; i++) {
                curr = curr->next();
            }
            return curr->data();
        }
    }
    //! getter constante a um elemento
    const T& at(std::size_t index) const {
        Node *curr = head;
        for (int i = 0; i < index; ++i) {
            curr = curr->next();
        }
        return curr->data();
    }
    //! posição de um dado
    std::size_t find(const T& data) const {
        if (empty()) {
            throw std::out_of_range("lista vazia");
        } else {
            auto curr = head;
            for (int i = 0; i < size_; ++i) {
                if (curr->data() == data) {
                    return i;
                }
                curr = curr->next();
            }
            return size_;
        }
    }
    //! tamanho
    std::size_t size() const {
        return size_;
    }

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        Node(const T& data, Node* next, Node* prev):
            data_{data},
            next_{next},
            prev_{prev}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
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

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* next_;
        Node* prev_;
    };

    Node* head;
    std::size_t size_;
    //! último nodo da lista
    Node* end() {
        return head->prev();
    }
};

}  // namespace structures

#endif
