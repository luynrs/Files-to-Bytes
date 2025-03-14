# Files-to-Bytes

[🇬🇧 English](README.md) | [🇷🇺 Русский](README.RU.md)

---

![FILES-to-bytres](https://github.com/user-attachments/assets/fac37f14-3472-4039-b7d0-7aaa0c711278)

---

Онлайн версия (с ограничениями) - https://luynar.space/files-to-bytes

---

## 🇷🇺 Русская версия

Files-to-Bytes — это консольная утилита, которая позволяет конвертировать файлы в массивы байтов (HEX или DECIMAL) и сохранять их в виде заголовочных файлов C++ (.h). Программа автоматически создаёт директорию `outputs` и сохраняет файлы в неё. И, логично, что позволяет использовать сторонние файлы без надобности нахождения в одной и той же директории с проектом.

### Возможности
- Поддержка двух режимов вывода: **HEX** и **DECIMAL**.
- Автоматическое создание заголовочного файла с массивом байтов и его размером.
- Поддержка настройки разбиения строк для удобного отображения.
- Автоматическое создание файла настроек `settings.ini`.
- Управление через командную строку или drag-and-drop файлов на исполняемый файл.

### Установка и использование

#### 1. Запуск
- **Перетащите файл** на исполняемый `.exe`, чтобы автоматически обработать его.
- **Или запустите через консоль**:
  ```sh
  files-to-bytes.exe <путь_к_файлу>
  ```

#### 2. Настройки
При первом запуске создаётся файл `settings.ini` с параметрами:
```ini
Mode=HEX       # Режим вывода (HEX или DECIMAL)
LineBreaks=1   # Разбиение строк (1 - включено, 0 - выключено)
```
Вы можете изменить эти настройки вручную или через интерфейс консоли:
- Введите `hex` или `dec`, чтобы переключить режим.
- Введите `line` или `noline`, чтобы включить/выключить разбиение строк.

#### 3. Выходные файлы
Результат работы сохраняется в папке `outputs`, например:
```
outputs/
 ├── example.h
```
Пример содержимого файла `example.h`:
```cpp
#ifndef FILE_EXAMPLE_H
#define FILE_EXAMPLE_H

unsigned char example_data[] = {0x4D, 0x5A, 0x90, 0x00, ...};
unsigned int example_size = 1234;

#endif
```

> Название_Файла - название входного файла формируется без расширения (example.exe > example)
Названия переменных формируются следующим образом:
```
Название_Файла_data - Массив байтов
Название_Файла_size - Длина файла
```
Эти данные нужны для использования в коде.

### Использование в коде
Чтобы восстановить исходный файл из сгенерированного `.h` файла:
```cpp
#include <fstream>
#include "example.h"

int main() {
    std::ofstream outFile("restored_example.bin", std::ios::binary); // тута вместо .bin поставьте тот тип файла, в котором вы его сохраняли
    outFile.write(reinterpret_cast<const char*>(example_data), example_size);
    outFile.close();
    return 0;
}
```
Этот код сохранит массив байтов в `restored_example.bin`.

### Лицензия
Проект распространяется под лицензией **Apache License 2.0**.
