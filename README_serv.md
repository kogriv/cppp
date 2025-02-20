В данном репозитории реализована следующая схема обмена данными через разделяемую память:

В main.cpp запускаются два потока:
// Поток 1 - запуск сервера для именованных каналов
std::thread t1(thread1);

// Поток 2 - чтение из разделяемой памяти и обновление broadcast строки
std::thread t2(thread2);

Copy

Apply

named_pipes\named_pipes\main.cpp
В потоке thread2 происходит:
Создание объекта разделяемой памяти SharedMemory
Циклическое чтение данных из разделяемой памяти
Обновление глобальной переменной pipe_broadcast_string значением из памяти:
void thread2() {
    SharedMemory SM(name, n, 1, 2);
    while (true) {
        SM.read_data(A, str);
        server.pipe_broadcast_string = std::to_string(A[0]);
        Sleep(1000);
    }
}

Copy

Apply

named_pipes\named_pipes\main.cpp
Сервер именованных каналов в pipes.cpp использует обновленное значение pipe_broadcast_string для отправки всем подключенным клиентам:
std::string str = *broadcast_string_ptr;
_tcscpy_s(pchReply, str.size() + 1, CA2T(str.c_str()));
WriteFile(hPipe, pchReply, cbReplyBytes, &cbWritten, NULL);

Copy

Apply

named_pipes\named_pipes\pipes.cpp
Таким образом реализована схема, где:

Данные записываются в разделяемую память
Сервер читает эти данные
Все подключенные клиенты получают обновленные данные через именованные каналы
Это позволяет эффективно распространять данные из разделяемой памяти множеству клиентов.