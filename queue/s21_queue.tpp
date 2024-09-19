using namespace s21;

template <class T, class Container>
queue<T, Container>::queue() : container() {} // Конструктор по умолчанию

template <class T, class Container>
queue<T, Container>::queue(std::initializer_list<value_type> const
                               &items) // Конструктор списка инициализаторов
    : container(items) {}

template <class T, class Container>
queue<T, Container>::queue(const queue &other)
    : container(other.container) {} // Конструктор копирования

template <class T, class Container>
queue<T, Container>::queue(queue &&other)
    : container(std::move(other.container)) {} // Конструктор перемещения

template <class T, class Container>
void queue<T, Container>::swap(queue &other) noexcept { // Метод обмена
  container.swap(other.container);
}

template <class T, class Container>
queue<T, Container> &queue<T, Container>::operator=(
    const queue &other) { // Оператор присваивания копирования
  if (this != &other) {
    container = other.container;
  }
  return *this;
}

template <class T, class Container>
queue<T, Container> &queue<T, Container>::operator=(
    queue &&other) noexcept { // Оператор присваивания перемещения
  if (this != &other) {
    container = std::move(other.container);
  }
  return *this;
}

template <class T, class Container>
typename queue<T, Container>::const_reference
queue<T, Container>::front() // Метод получения верхнего элемента
    const {
  if (container.empty()) {
    throw std::out_of_range("Stack is empty");
  }
  return container.front(); // Должен возвращать верхний элемент стека
}

template <class T, class Container>
typename queue<T, Container>::const_reference
queue<T, Container>::back() // Метод получения нижнего элемента
    const {
  return container.back();
}

template <class T, class Container>
void queue<T, Container>::push(
    const_reference value) { // Метод добавления элемента
  container.push_back(value);
}

template <class T, class Container>
void queue<T, Container>::pop() { // Метод удаления элемента
  if (container.empty()) {
    throw std::out_of_range("Stack is empty");
  }
  return container.pop_front();
}

template <class T, class Container>
bool queue<T, Container>::empty() const { // Метод проверки на пустоту
  return container.empty();
}

template <class T, class Container>
typename queue<T, Container>::size_type
queue<T, Container>::size() const { // Метод получения размера стека
  return container.size();
}

template <class T, class Container>
T &queue<T, Container>::operator[](
    const int index) { // Оператор доступа по индексу
  if (index < 0 ||
      static_cast<s21::deque<int>::size_type>(index) >=
          container.size()) { // Проверка на выход за пределы массива
    throw std::out_of_range("Index out of range");
  }
  return container[index]; // Возвращаем элемент данных по индексу
}

template <class T, class Container>
template <class... Args>
void queue<T, Container>::insert_many_back(
    Args &&...args) { // Метод добавления нескольких элементов в конец очереди
  (container.push_back(std::forward<Args>(args)), ...);
}