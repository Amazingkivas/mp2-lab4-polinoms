#include <stdexcept>

template<class Node, class T>
class Iterator
{
private:

    Node* node;

public:

    Iterator() : node(nullptr) {}
    Iterator(Node* nd) : node(nd) {}

    Iterator& operator++()
    {
        if (node != nullptr)
        {
            node = node->next;
        }
        return *this;
    }

    T& operator*()
    {
        return node->data;
    }

    bool operator==(const Node* nd) const
    {
        return node == nd;
    }

    bool operator!=(const Node* nd) const
    {
        return node != nd;
    }
};

template <class T>
class List
{
private:

    struct Node
    {
        T data;
        Node* next;
    };

    Node* head;
    size_t size;

    Node* to_position(size_t position) const
    {
        Node* node = head;
        for (size_t n = 0; n != position; node = node->next, n++);
        return node;
    }

public:

    typedef Iterator<Node, T> iterator;

    Node* begin()
    {
        return head;
    }
    Node* begin() const
    {
        return head;
    }
    Node* end()
    {
        return nullptr;
    }
    Node* end() const
    {
        return nullptr;
    }

    List() : head(nullptr), size(0) {}

    List(const List& list) : head(nullptr), size(list.size)
    {
        if (!list.isEmpty())
        {
            Node* node = head = new Node{ *list.head };
            for (; node->next != nullptr; node = node->next)
            {
                node->next = new Node{ *node->next };
            }
        }
    }

    void push_front(const T& value)
    {
        Node* node = new Node{ value, head };
        head = node;
        size++;
    }

    void insert_after(size_t position, const T& value)
    {
        Node* node = to_position(position);
        Node* new_node = new Node{ value, node->next };
        node->next = new_node;
        size++;
    }

    void pop_front()
    {
        Node* node = head->next;
        delete head;
        head = node;
        size--;
    }

    void erase_after(size_t position)
    {
        Node* next;
        Node* node = to_position(position);
        next = node->next->next;
        delete node->next;
        node->next = next;
        size--;
    }

    size_t get_size() const
    {
        return size;
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }

    bool operator==(const List& list) const  // for tests
    {
        if (size != list.size) return false;

        Node* node1 = head;
        Node* node2 = list.head;
        for (int i = 0; i < size; node1 = node1->next, node2 = node2->next, i++)
        {
            if (node1->data != node2->data) return false;
        }
        return true;
    }

    bool operator!=(const List& list) const  // for tests
    {
        return !(*this == list);
    }

    T& operator[](size_t position)
    {
        Node* node = to_position(position);
        return node->data;
    }

    const T& operator[](size_t position) const
    {
        Node* node = to_position(position);
        return node->data;
    }

    T& at(int position) // controlled access
    {
        if (position < 0 || position >= size) throw std::out_of_range("Bad index");

        Node* node = to_position(position);
        return node->data;
    }

    const T& at(int position) const // controlled access
    {
        if (position < 0 || position >= size) throw std::out_of_range("Bad index");

        Node* node = to_position(position);
        return node->data;
    }

    ~List()
    {
        while (!isEmpty()) pop_front();
    }
};
