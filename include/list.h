#include <stdexcept>

using std::out_of_range;

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
    Node* tail;
    size_t size;

    Node* to_position(size_t position) const
    {
        Node* node = head;
        for (size_t n = 0; n != position; node = node->next, n++);
        return node;
    }

public:

    List() : head(nullptr), tail(head), size(0) {}
    List(const List& list) : head(nullptr), tail(head), size(list.size)
    {
        if (!list.isEmpty())
        {
            Node* node = head = new Node{ *list.head };
            for (; node->next != nullptr; node = node->next)
            {
                node->next = new Node{ *node->next };
            }
            tail = node;
        }
    }

    void push_front(const T& value)
    {
        Node* node = new Node{ value, head };
        head = node;
        if (tail == nullptr) tail = head;
        size++;
    }
    void push_back(const T& value)
    {
        Node* node = new Node{ value };
        if (tail != nullptr) tail->next = node;
        else head = node;

        tail = node;
        size++;
    }
    void insert_after(size_t position, const T& value)
    {
        if (position < 0 || position >= size) throw out_of_range("Bad index");

        Node* node = to_position(position);
        Node* new_node = new Node{ value, node->next };
        node->next = new_node;

        if (position == size - 1) tail = new_node;
        size++;
    }

    void pop_front()
    {
        if (isEmpty()) throw std::exception("Deleting an undefined pointer");

        Node* node = head->next;
        delete head;
        head = node;

        if (isEmpty()) tail = head;
        size--;
    }
    void erase_after(size_t position)
    {
        if (position < 0 || position >= size - 1) throw out_of_range("Bad index");

        Node* next;
        Node* node = to_position(position);
        next = node->next->next;
        delete node->next;
        node->next = next;

        if (node->next == nullptr) tail = node;
        size--;
    }

    size_t get_size() const
    {
        return size;
    }

    bool isEmpty() const noexcept
    {
        return head == nullptr;
    }

    class iterator
    {
    private:

        Node* node;

    public:

        iterator() : node(nullptr) {}
        iterator(Node* nd) : node(nd) {}

        iterator& operator++()
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
    Node* begin() const
    {
        return head;
    }
    Node* end() const
    {
        return nullptr;
    }

    bool operator==(const List& list) const  // for tests
    {
        if (size != list.size) return false;

        Node* node1 = head;
        Node* node2 = list.head;
        for (; node1 != nullptr; node1 = node1->next, node2 = node2->next)
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
        if (position < 0 || position >= size) throw out_of_range("Bad index");

        Node* node = to_position(position);
        return node->data;
    }
    const T& at(int position) const // controlled access
    {
        if (position < 0 || position >= size) throw out_of_range("Bad index");

        Node* node = to_position(position);
        return node->data;
    }

    ~List()
    {
        Node* node;
        while (!isEmpty())
        {
            node = head->next;
            delete head;
            head = node;
        }
    }
};
