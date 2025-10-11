<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/swift/swift-original.svg" height='80' align="right"/>

# Демо проектное задание на Swift

Демонстрационный проект по работе с **PostgreSQL**.    

Проект представляет из себя простой backend сервис, который предоставляет несколько API, написан на Swift и Vapor.   

***Stack:***  

* **Swift 5.10**  
* **Vapor**
* **Fluent**  
* **Docker**

Также вам необходим PSQL сервер и база данных на нем. Как это сделать вы можете прочитать [здесь](CreateYourOwnDatabase.md).  

##### Docker

Либо запустить проект используя [**Docker**](https://www.docker.com/products/docker-desktop/)    
     
```sh
docker-compose build
docker-compose up -d
docker-compose run migrate
```

> [!IMPORTANT]  
> Для локального запуска не забудьте заполнить `.env` файл! Достаточно удалить расширение **.example** из шаблона `.env.example`
> 

##### Тесты

Тесты запускаются локально, для этого необходима база данных со всеми миграциями. БД можно поднять в докере или локально.    

```sh
docker-compose up -d db

swift test
```

#### Клонировать проект

```bash
cd ../..
git submodule update --init
```

#### API

| Method   | URL                                      | Description                              |
| -------- | ---------------------------------------- | ---------------------------------------- |
| `GET`    | `/animes`                             | Receive all anime.                      |
| `GET`   | `/animes/{id}`                             | Get anime by id.                       |
| `POST`    | `/animes`                          | Create an anime.                       |
| `PUT`  | `/animes/{id}`                          | Update existing anime by id.                 |
| `DELETE`   | `/animes/{id}`                 | Delete anime by id.                 |

##### Characters

| Method   | URL                                      | Description                              |
| -------- | ---------------------------------------- | ---------------------------------------- |
| `GET`    | `/characters`                             | Receive all characters.                      |
| `GET`   | `/characters/{id}`                             | Get character by id.                       |
| `POST`    | `/characters`                          | Create character.                       |
| `PUT`  | `/characters/{id}`                          | Update existing character by id.                 |
| `DELETE`   | `/characters/{id}`                 | Delete character by id.                 |


#### Структура данных


##### Anime
```swift
id: Optional<UUID>
titleEn: String
titleJp: String
description: Optional<String>
releaseDate: Date
rating: Double
episodeCount: Int
type: AnimeType
characters: [UUID]
genres: Optional<[String]>
imageUrl: Optional<String>
```

##### Character

```swift
id: Optional<UUID>
name: String
description: Optional<String>
animeId: [UUID]
imageUrl: Optional<String>
```

---

### Вопросы и проблемы

Проблемы сюда:  

![issues](../../../Tech/images/issue.png)  

Вопросы и предложения сюда:
[<img src="../../../Tech/images/tg-icon.svg" height='50' align="center">](https://t.me/KeoFoxy)