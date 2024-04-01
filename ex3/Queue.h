#include <iostream>
#include <cassert>

template <class T>
class Queue
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &data) : data(data), next(nullptr) {}
    };
    Node *head;
    Node *rear;
    int m_size;

public:
    class Iterator;
    Iterator begin();
    Iterator end();

    class ConstIterator;
    ConstIterator begin() const;
    ConstIterator end() const;

    class EmptyQueue
    {
    };

    Queue() : head(nullptr), rear(nullptr), m_size(0){};

    Queue(const Queue &s);

    Queue<T> &operator=(const Queue &s);

    ~Queue();

    void pushBack(const T &data);

    void popFront();

    T &front();

    const T &front() const;

    bool isEmpty() const;

    int size() const;
};

template <class T>
Queue<T>::Queue(const Queue<T> &s) : head(nullptr), rear(nullptr), m_size(0)
{
    try
    {
        Node *temp = s.head;
        while (temp != nullptr)
        {
            pushBack(temp->data);
            temp = temp->next;
        }
    }
    catch (const std::bad_alloc &e)
    {
        while (!isEmpty())
        {
            popFront();
        }
        throw;
    }
}

template <class T>
Queue<T> &Queue<T>::operator=(const Queue<T> &s)
{
    int successPush = 0;
    int prevLen = size();
    if (this == &s)
    {
        return *this;
    }
    try
    {
        // Copy content from s
        Node *temp = s.head;
        while (temp != nullptr)
        {
            successPush++;
            pushBack(temp->data);
            temp = temp->next;
        }
        // Clear current content
        for (int i = 0; i < prevLen; i++)
        {
            popFront();
        }
    }
    catch (const std::bad_alloc &e)
    {
        for (int k = 0; k < successPush; k++)
        {
            popFront();
        }
        throw e;
    }

    return *this;
}

template <class T>
Queue<T>::~Queue()
{
    while (!isEmpty())
    {
        popFront();
    }
}

template <class T>
void Queue<T>::pushBack(const T &data)
{
    Node *newNode = new Node(data);

    if (isEmpty())
    {
        head = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
    m_size++;
}

template <class T>
void Queue<T>::popFront()
{
    if (isEmpty())
    {
        throw EmptyQueue();
    }

    Node *temp = head;
    head = head->next;
    delete temp;
    m_size--;
    if (isEmpty())
    {
        rear = nullptr;
    }
}

template <class T>
T &Queue<T>::front()
{
    if (isEmpty())
    {
        throw EmptyQueue();
    }
    return head->data;
}

template <class T>
const T &Queue<T>::front() const
{
    if (isEmpty())
    {
        throw EmptyQueue();
    }
    return head->data;
}

template <class T>
bool Queue<T>::isEmpty() const
{
    return m_size == 0;
}

template <class T>
int Queue<T>::size() const
{
    return m_size;
}

template <class T, class Func>
Queue<T> filter(const Queue<T> &q, Func test)
{
    Queue<T> filterQ;
    try
    {
        for (typename Queue<T>::ConstIterator it = q.begin(); it != q.end(); ++it)
        {
            if (test(*it))
            {
                filterQ.pushBack(*it);
            }
        }
    }
    catch (const std::bad_alloc &e)
    {
        while (!filterQ.isEmpty())
        {
            filterQ.popFront();
        }
        throw;
    }
    return filterQ;
}

template <class T, class Func>
void transform(Queue<T> &filterQ, Func calc)
{
    for (typename Queue<T>::Iterator it = filterQ.begin(); it != filterQ.end(); ++it)
    {
        *it = calc(*it);
    }
}

template <class T, class Func>
T reduce(const Queue<T> &q, T val, Func calc)
{
    T result = val;

    for (typename Queue<T>::ConstIterator it = q.begin(); it != q.end(); ++it)
    {
        result = calc(result, *it);
    }
    return result;
}

template <class T>
class Queue<T>::Iterator
{
    Node *current;

    Iterator(Node *current) : current(current) {}

    friend class Queue<T>;

public:
    class InvalidOperation
    {
    };
    Iterator(const Iterator &s) = default;

    Iterator &operator=(const Iterator &s) = default;

    ~Iterator() = default;

    T &operator*() const;

    Iterator &operator++();

    bool operator==(const Iterator &it) const;

    bool operator!=(const Iterator &it) const;
};

template <class T>
T &Queue<T>::Iterator::operator*() const
{
    if (current == nullptr)
    {
        throw InvalidOperation();
    }
    return current->data;
}

template <class T>
typename Queue<T>::Iterator &Queue<T>::Iterator::operator++()
{
    if (current == nullptr)
    {
        throw InvalidOperation();
    }
    current = current->next;
    return *this;
}

template <class T>
bool Queue<T>::Iterator::operator==(const Iterator &it) const
{
    return current == it.current;
}

template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator &it) const
{
    return !(*this == it);
}

template <class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
    return Iterator(head);
}

template <class T>
typename Queue<T>::Iterator Queue<T>::end()
{
    return Iterator(nullptr);
}

template <class T>
class Queue<T>::ConstIterator
{
private:
    Node *current;

    ConstIterator(Node *current) : current(current) {}

    friend class Queue<T>;

public:
    class InvalidOperation
    {
    };
    ConstIterator(const ConstIterator &s) = default;

    ConstIterator &operator=(const ConstIterator &s) = default;

    ~ConstIterator() = default;

    const T &operator*() const;

    ConstIterator &operator++();

    bool operator==(const ConstIterator &it) const;

    bool operator!=(const ConstIterator &it) const;
};

template <class T>
const T &Queue<T>::ConstIterator::operator*() const
{
    if (current == nullptr)
    {
        throw InvalidOperation();
    }
    return current->data;
}

template <class T>
typename Queue<T>::ConstIterator &Queue<T>::ConstIterator::operator++()
{
    if (current == nullptr)
    {
        throw InvalidOperation();
    }
    current = current->next;
    return *this;
}

template <class T>
bool Queue<T>::ConstIterator::operator==(const ConstIterator &it) const
{
    return current == it.current;
}

template <class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator &it) const
{
    return !(*this == it);
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    return ConstIterator(head);
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
    return ConstIterator(nullptr);
}