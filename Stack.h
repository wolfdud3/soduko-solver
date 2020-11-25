//
//  Stack.h
//  SudokuProblem
//
//  Created by wolfdud3 on 19/03/2020.
//

#ifndef Stack_h
#define Stack_h

#include "List.h"


#endif /* Stack_h */


template <typename T> struct Stack
{
    List<T> list;

    bool is_empty()
    {
        return list.is_empty();
    }

    void push(T newData)
    {
        list.insert_front(newData);
    }

    void pop()
    {
        list.delete_front();
    }

    T top()
    {
        return list.get_top();
    }

    bool exists(T search_data)
    {
        return list.exists(search_data);
    }

    friend std::ostream &operator<<(std::ostream &out, const Stack<T> s)
    {
        Node<T>* tmp = s.list.head;
        for (unsigned int i = 0; i < s.list.size; i++)
        {
            out << tmp->data << ' ';
            tmp = tmp->next;
        }
        return out;
    }
};
