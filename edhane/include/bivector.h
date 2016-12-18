#ifndef EDHANE_BIVECTOR_H
#define EDHANE_BIVECTOR_H

template <typename T>
class Bivector {
public:
    Bivector();
    Bivector(int, T);
    virtual ~Bivector();

    int size();
    bool is_empty();
    void clear();
    T& operator[] (const int);
    void set(int, const T&);

    void insert(int, const T&);
    void remove(int);
    void push_front(const T&);
    void push_back(const T&);
    T& pop_front();
    T& pop_back();
private:
    T* elements;
    int capacity;
    int first_index;
    int end_index;

    void expand_capacity_front();
    void expand_capacity_back();
};

template <typename T>
Bivector::Bivector() {
    elements = NULL;
    first_index = end_index = capacity = 0;
}

template <typename T>
Bivector::Bivector(int initial_capacity, T copy_this) {
    first_index = 0;
    capacity = end_index = initial_capacity;
    elements = new T[capacity];
    for (int i = 0; i < capacity; i++) {
        elements[i] = copy_this;
    }
}

template <typename T>
Bivector::~Bivector() {
    if (elements != NULL) { delete[] elements; }
}


template <typename T>
int Bivector::size() { return end_index-first_index; }

template <typename T>
bool Bivector::is_empty() { return (end_index <= first_index); }

template <typename T>
void Bivector::clear() {
    if (elements != NULL) { delete[] elements; }
    first_index = end_index = capacity = 0;
    elements = NULL;
}

template <typename T>
T& Bivector::operator[](const int index) {
    // TODO error handling
    return elements[index];
}

template <typename T>
void Bivector::set(int index, const T& value) {
    // TODO error handling
    elements[index] = value;
}


template <typename T>
void Bivector::insert(int index, const T& value) {
    // TODO error handling
    int mi = (first_index+end_index)/2;
    if (index >= mi) {
        if (end_index == capacity) { expand_capacity_back(); }
        for (int i = end_index; i > index; i--) {
            elements[i] = elements[i-1];
        }
    } else {
        if (index < mi && first_index == 0) { expand_capacity_front(); }
        for (int i = first_index-1; i < index; i++) {
            elements[i] = elements[i-1];
        }
    }
    elements[index] = value;
}

template <typename T>
void Bivector::remove(int index) {
    // TODO error handling
    int mi = (first_index+end_index)/2;
    if (index >= mi) {
        for (int i = index; i < end_index-1; i++) {
            elements[i] = elements[i+1];
        }
        end_index--;
    } else {
        for (int i = index; i > first_index; i--) {
            elements[i] = elements[i-1];
        }
        first_index++;
    }
}

template <typename T>
void Bivector::push_front(const T& value) {
    insert(first_index-1, value);
}

template <typename T>
void Bivector::push_back(const T& value) {
    insert(end_index, value);
}


template <typename T>
T& Bivector::pop_front() {
    // TODO error handling
    T r = elements[first_index];
    elements[first_index++] = NULL;
    return r;
}

template <typename T>
T& Bivector::pop_back() {
    // TODO error handling
    T r = elements[end_index--];
    elements[end_index] = NULL;
    return r;
}


template <typename T>
void Bivector::expand_capacity_front() {
    int mi = ((first_index+end_index)/2);
    capacity += max(1, mi);
    T* nelements = new T[capacity];
    for (int i = first_index; i < end_index; i++) {
        nelements[i+mi] = elements[i];
    }
    if (elements != NULL) delete[] elements;
    elements = nelements;
}

template <typename T>
void Bivector::expand_capacity_back() {
    int mi = ((first_index+end_index)/2);
    capacity += max(1, capacity-mi);
    T* nelements = new T[capacity];
    for (int i = first_index; i < end_index; i++) {
        nelements[i] = elements[i];
    }
    if (elements != NULL) delete[] elements;
    elements = nelements;
}

#endif // EDHANE_BIVECTOR_H
