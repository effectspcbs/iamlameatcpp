#include <iostream>

template <typename T, size_t S>
class CircBuff {
  public:
    CircBuff() = default;

    void putItem(T t_item) {
      m_buffer[m_head] = t_item;

      if (isFull()) {
        m_tail = (m_tail + 1) % m_maxSize;
      }

      m_head = (m_head + 1) % m_maxSize;
      m_full = (m_head == m_tail);
    }

    void putItems(const T* t_items, size_t t_len) {
      if (t_len < size() - m_head) {
        copy(&m_buffer[m_head], t_items, t_len);

        if (isFull()) {
          m_tail = (m_tail + t_len) % m_maxSize;
        }

        m_head = (m_head + t_len) % m_maxSize;
        m_full = (m_head == m_tail);
      }
      else {
      }
    }

    T getItem() {
      T item = m_buffer[m_tail];
      m_full = false;
      m_tail = (m_tail + 1) % m_maxSize;

      return item;
    }

    bool isEmpty() const {
      return (!m_full && (m_head == m_tail));
    }

    bool isFull() const {
      return m_full;
    }

    size_t capacity() const {
      return m_maxSize;
    }

    size_t size() const {
      size_t size = m_maxSize;

      if (!isFull()) {
        if (m_head >= m_tail) {
          size = m_head - m_tail;
        }
        else {
          size = m_maxSize + m_head - m_tail;
        }
      }

      return size;
    }

  private:
    T m_buffer[S];

    size_t m_maxSize = S;
    size_t m_head = 0;
    size_t m_tail = 0;
    bool m_full = false;

    void copy(T* t_dest, const T* t_src, size_t t_len) {
      while (t_len--) {
        *t_dest++ = *t_src++;
      }
    }
};

void copy(uint8_t* t_src, uint8_t* t_dest, size_t t_len) {
  while (t_len--) {
    *t_dest++ = *t_src++;
  }
}

int main() {
  uint8_t array1[10] = {101, 102, 103, 104, 105, 106, 107, 108, 109, 110};
  uint8_t array2[10] = {111, 112, 113, 114, 115, 116, 117, 118, 119, 120};

  uint8_t* p1 = array1;
  uint8_t* p2 = array2;

  size_t arrayLen = 10;

  std::cout << "Array1 : ";
  for (uint8_t i = 0; i < arrayLen; i++) {
    std::cout << (int) *(p1 + i) << ", ";
  }
  std::cout << std::endl;

  std::cout << "Array2 : ";
  for (uint8_t i = 0; i < arrayLen; i++) {
    std::cout << (int) *(p2 + i) << ", ";
  }
  std::cout << std::endl;

  copy(array1, &array2[4], 2);
  copy(p2 + 1, p1, 1);

  std::cout << "Array1 : ";
  for (uint8_t i = 0; i < arrayLen; i++) {
    std::cout << (int) *(p1 + i) << ", ";
  }
  std::cout << std::endl;

  std::cout << "Array2 : ";
  for (uint8_t i = 0; i < arrayLen; i++) {
    std::cout << (int) *(p2 + i) << ", ";
  }
  std::cout << std::endl;

  size_t bufferLen = 20;
  CircBuff<uint8_t, 20> buffer;

  std::cout << "Buffer size : " << buffer.size() << std::endl;
  for (auto i : array1) {
    buffer.putItem(i);
  }

  buffer.putItems(&array2[4], 2);

  std::cout << "Buffer size : " << buffer.size() << std::endl;
  std::cout << "Buffer : ";
  for (uint8_t i = 0; i < 2; i++) {
    std::cout << (int) buffer.getItem() << ", ";
  }
  std::cout << std::endl;

  std::cout << "Buffer size : " << buffer.size() << std::endl;
  for (auto i : array2) {
    buffer.putItem(i);
  }

  return 0;
}