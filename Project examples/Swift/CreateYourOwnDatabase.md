# PostgreSQL на своей машине 

В данном гайде вы узнаете, как установить PSQL сервер на свою машину.   

> Инструкция для обладателей MacOS, так как VirtualBox у вас не встанет. А зачем использовать виртуальный Linux, если можно работать напрямую.   

> Если Вы используете Linux, то явно знаете, как все установить и без гайдов. Но вот [ссылка](https://www.postgresql.org/download/linux/ubuntu/)

## Установка PostgreSQL сервера

Предварительно у Вас должен быть установлен менеджер пакетов [**brew**](https://brew.sh/index_ru).   

Для установки сервера PostgreSQL необходимо открыть терминал и ввести команду:  

```bash
brew install postgresql
```

После установки необходимо запустить сервер командой:   

```bash
brew services start postgresql@14
```

Готово!  

Остановить сервер:  

```bash
brew services stop postgresql@14
```

Перезагрузить сервер:  

```bash
brew services restart postgresql@14
```



## Создание пользователя и базы данных

Запустите команду `psql` в терминале для входа в интерактивный режим:
```bash
psql -U postgres
```
Строка должна измениться на postgres=#, что означает успешный вход под пользователем postgres.

> ***postgres*** может не работать, тогда попробуйте имя текущего пользователя устройства

1. Создайте нового пользователя с помощью команды `CREATE USER`. Замените 'your_username' и 'your_password' на желаемое имя пользователя и пароль соответственно:
```sql
CREATE USER your_username WITH PASSWORD 'your_password';

CREATE USER admin WITH PASSWORD '123456';
```

2. Создайте базу данных для этого пользователя с помощью команды `CREATE DATABASE`. Замените 'your_database_name' на желаемое имя базы данных:
```sql
CREATE DATABASE your_database_name;

CREATE DATABASE blackfox;
```

3. Дайте новому пользователю права доступа к базе данных с помощью команды `GRANT`:

```sql
GRANT ALL PRIVILEGES ON DATABASE your_database_name TO your_username;

GRANT ALL PRIVILEGES ON DATABASE blackfox TO admin;
```
Выход из интерактивной командной строки psql: `\q`

4. Заполним базу данных используя готовые скрипты

```bash
psql -U your_username -d your_database_name -f path/to/your_script.sql
```

Теперь для проверки можно сделать какой нибудь селект

Если вы получили свои данные, значит все работает!   

> Не забывайте ставить **;** в конце команд!

### Вопросы и проблемы

Проблемы сюда:  

![issues](../../../Tech/images/issue.png)  

Вопросы сюда:
[<img src="../../../Tech/images/tg-icon.svg" height='50' align="center">](https://t.me/KeoFoxy)
