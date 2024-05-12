#include "header/message.h"
#include "header/user.h"
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>


// Функция для установки прав доступа к файлу только на чтение
void setFileReadPermissions(const string& fileName) {
    // Устанавливаем права доступа к файлу, разрешая только чтение для владельца
    chmod(fileName.c_str(), S_IRUSR);
}

// Функция для установки прав доступа к файлу на чтение и запись
void setFileReadWritePermissions(const string& fileName) {
    // Устанавливаем права доступа к файлу, разрешая чтение и запись для владельца
    chmod(fileName.c_str(), S_IRUSR | S_IWUSR);
}




// Функция для чтения пользователей из файла
vector<User> readUsersFromFile(const string& fileName) {
    // Устанавливаем права доступа только на чтение
    setFileReadPermissions(fileName);
    
    vector<User> users;
    ifstream file(fileName);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string name, login, password;
        if (getline(iss, name, ';') && getline(iss, login, ';') && getline(iss, password, ';')) {
            users.push_back({name, login, password});
        }
    }
    return users;
}

// Функция чтения сообщений из файла
vector<Message> readMessagesFromFile(const string& fileName)
{
    // Устанавливаем права доступа только на чтение
    setFileReadPermissions(fileName);

    vector<Message> messages;
    ifstream file(fileName);
    string line;
    while(getline(file,line))
    {
        string text, reciever, sender;
        istringstream iss(line);
        if(getline(iss,text,';') && getline(iss,reciever,';') && getline(iss,sender,';'))
        {
            messages.push_back({text,reciever,sender});
        }
    }
    return messages;
} 


// Функция записи пользователей в файл с установкой прав доступа
void writeUsersToFile(const std::string& fileName, const std::vector<std::string>& userData) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла для записи: " << fileName << std::endl;
        return;
    }
    
    for (const std::string& user : userData) {
        file << user << std::endl;
    }
    
    file.close();
    
    // Установка прав доступа к файлу для чтения
    chmod(fileName.c_str(), S_IRUSR | S_IWUSR);
}

// Функция записи сообщений в файл с установкой прав доступа
void writeMessagesToFile(const std::string& fileName, const std::vector<std::string>& messageData) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла для записи: " << fileName << std::endl;
        return;
    }
    
    for (const std::string& message : messageData) {
        file << message << std::endl;
    }
    
    file.close();
    
    // Установка прав доступа к файлу для чтения
    chmod(fileName.c_str(), S_IRUSR | S_IWUSR);
}


// Функция для вывода сообщений для заданного пользователя
void printMessagesForUser(const string& login, const vector<Message>& messages)
{
    cout << "Сообщения для пользователя с логином '" << login << "':" << endl;

    for( const auto& message : messages)
    {
        if(message._sender == login || message._receiver == login)
        {
            cout << "Отправитель: " << message._sender << ", Получатель: " << message._receiver << ", Текст: " << message._text << endl;
        }
    }
}

int main()
{
    // Создаем файл для пользователей
    // ofstream usersFile("users.txt");
    // if(!usersFile)
    // {
    //     cerr << "Не удалось создать файл для пользователей" << endl;
    //     return 1;
    // }
    


    // Данные пользователей и сообщений
    std::vector<std::string> userData = {"Иван;ivan;123456", "Мария;maria;abcdef", "Петр;petr;qwerty"};
    std::vector<std::string> messageData = {"Привет!;ivan;maria", "Как дела?;maria;petr", "Все хорошо!;maria;ivan"};

    // Запись пользователей и сообщений в файлы
    writeUsersToFile("users.txt", userData);
    writeMessagesToFile("messages.txt", messageData);


    // Создаем файл для сообщений
    // ofstream messagesFile("messages.txt");
    // if (!messagesFile) {
    //     cerr << "Не удалось создать файл для сообщений!" << endl;
    //     return 1; // Возвращаем ошибку
    // }
    



    // Считываем пользователей и сообщения из файлов
    vector<User> users = readUsersFromFile("users.txt");
    vector<Message> messages = readMessagesFromFile("messages.txt");
    // Выводим сообщения для заданного пользователя
    printMessagesForUser("ivan", messages);


    
    return 0;
}