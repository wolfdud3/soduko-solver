//
//  List.h
//  SudokuProblem
//
//  Created by wolfdud3 on 19/03/2020.
//

#ifndef List_h
#define List_h

#include <iostream>
#include <exception>


#endif /* List_h */

template <typename T> struct Node
{
    T data;
    Node* next;
};

template <typename T> struct List
{
    unsigned int size = 0;
    Node<T>* head = nullptr;

    List<T>() {}

    bool is_empty()
    {
        return head == nullptr;
    }

    int get_size()
    {
        return size;
    }

    Node<T>* get_head()
    {
        return head;
    }

    Node<T>* find(T searchData)
    {
        for (Node<T>* tmp = head; tmp->next != nullptr; tmp = tmp->next)
        {
            if (tmp->data == searchData) return tmp;
        }
        return nullptr;
    }

    bool exists(T search_data)
    {
        return find(search_data) != nullptr;
    }

    Node<T>* access(unsigned int k)
    {
        if (k < size)
        {
            Node<T>* tmp = head;
            for (unsigned int i = 0; i < k; i++, tmp = tmp->next);
            return tmp;
        }
        return nullptr;
    }

    void insert_back(T new_data)
    {
        Node<T>* new_node = new Node<T>();
        new_node->data = new_data;
        new_node->next = nullptr;
        if (is_empty())
        {
            head = new_node;
        }
        else
        {
            Node<T>* back = access(size - 1);
            back->next = new_node;
        }
        size++;
    }

    void delete_back()
    {
        delete_node(size - 1);
    }

    void insert_sorted(T new_data)
    {
        Node<T>* prev_node = head;
        Node<T>* next_node = head->next;
        Node<T>* new_node = new Node<T>();
        if (new_data < prev_node->data)
        {
            insert_front(new_data);
        }
        else
        {
            while ((next_node != nullptr) && (next_node->data < new_data))
            {
                prev_node = prev_node->next;
                next_node = next_node->next;
            }

            new_node->data = new_data;
            new_node->next = next_node;
            prev_node->next = new_node;
            size++;
        }
    }

    T get_top()
    {
        if (!is_empty())
        {
            return head->data;
        }
        else
        {
            throw;
        }
    }

    void insert_front(T new_data)
    {
        Node<T>* new_node = new Node<T>();
        new_node->data = new_data;
        new_node->next = head;
        head = new_node;
        size++;
    }

    void delete_front()
    {
        delete_node(0);
    }

    void append_list(List new_list)
    {
        access(size - 1)->next = new_list.head;
        size += new_list.size;
    }

    List<T>* sublist(unsigned int start, unsigned int end)
    {
        if (end < size && end > start)
        {
            List<T>* new_list = new List<T>();
            Node<T>* tmp = head;
            for (unsigned int i = 0; i < start; i++)
            {
                tmp = tmp->next;
            }
            
            for (unsigned int i = start; i < end; i++)
            {
                new_list->insert_back(tmp->data);
                tmp = tmp->next;
            }
            return new_list;
        }
        else
        {
            throw;
        }
    }

    void delete_node(unsigned int index)
    {
        if (index < size && index >= 0)
        {
            Node<T>* tmp;
            Node<T>* next_node;
            if (size == 1)
            {
                tmp = head;
                head = nullptr;
                delete tmp;
            }
            else if (index == 0)
            {
                tmp = head;
                head = tmp->next;
                delete tmp;
            }
            else
            {
                tmp = access(index - 1);
                next_node = access(index + 1);
                tmp->next = tmp->next->next;
                delete tmp->next;
                if (index == size - 1)
                {
                    next_node->next = nullptr;
                }
                else
                {
                    next_node->next = next_node;
                }
            }
            size--;
        }
        /*
        else
        {
            throw;
        }
         */
        
    }

    friend std::ostream &operator<<(std::ostream &out, const List<T> l)
    {
        Node<T>* tmp = l.head;
        for (unsigned int i = 0; i < l.size; i++)
        {
            out << tmp->data << ' ';
            tmp = tmp->next;
        }
        return out;
    }
};
